/// ---- EMOtto_ESP32_30pin + shield ver 2.0 ----- //
// ---- by Marco Mortari ---- //
// ---- ver 2.0 08/07/2025---- //
// ----  By Daddy for Francesco's Birthday 9 years---- //
// ---- Library EMOttoDIYLib 1.0.0 (OttoDIYLib 13.0.0.modificata)  ---- //
//--
//---------------------------------------------------------
// ---- Component  ---- //
// ---- 4 Servo SG90  180 Degrees ---- //
// ----  Round Display  GC9A01  ---- //
// ----  Passive Buzzer  ---- //
// ----  Touch Capacitive TTP223 * 2 ---- //
// ----  6 pin switch  ---- //
// ----  UBEC 5V 3A  ---- //
// ----  Battery 7.4V  ---- //
// ----  Sensor VL53L0X  ---- //
// ----  DFPlayer Mini  ---- //


//-- First step: Make sure the pins for servos are in the right position 
/*               -------- 
                |  (  )  |
                |--------|
 RIGHT LEG 26   |        | LEFT LEG 25
                 -------- 
                ||      ||
RIGHT FOOT 14 |---      ---| LEFT FOOT 27  
*/

// ----  GC9A01A LIBRERIA TFT_SPI SETUP200 CS=5 DC=17 RST= 16 SCLK=18 SDA(MOSI)=23 COMMENT BL=22---- //

// --- .ino
#include <EMOtto.h>
Otto Otto;  // This is Otto!
#include <TFT_eSPI.h>
#include <SPI.h>
#include "expressions.h"
#include "modes.h"
#include "sleep.h"
#include "draw_utils.h"
#include "colors.h"
#include "BluetoothCommands.h"
#include "BluetoothSerial.h"
#include <Adafruit_VL53L0X.h>
#include <DFRobotDFPlayerMini.h>
#include <modes.h>
#include "dance.h"
#include "dance2.h"
#include "dance3.h"
#include "dance4.h"

HardwareSerial mySerial(2);  // Serial2
BluetoothSerial SerialBT;
TFT_eSPI tft = TFT_eSPI(); // Usa impostazioni da User_Setup.h
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
DFRobotDFPlayerMini myDFPlayer;

#define LeftLeg 25
#define RightLeg 26
#define LeftFoot 27
#define RightFoot 14
#define Buzzer 13
#define TOUCH_PIN_1 12  // Primo touch: cicla le emozioni
#define TOUCH_PIN_2 33  // Secondo touch: cambia modalità
// VL53L0X SCL=22
// VL53L0X SDA=21
//DFPlayer Mini su Serial2
// GPIO 32 (RX)
// GPIO 4 (TX)
//--- canzoni mp3 
// ─── DF-Player ────────────────────────────────────────────────────────────────
#define DF_BUSY_PIN     34          // indica che mp3 non e finito
bool  wasPlaying = false;           // stato precedente del BUSY (LOW = suona)
inline bool isPlaying() {           // helper: true quando il DFPlayer riproduce
return digitalRead(DF_BUSY_PIN) == LOW;
}

// --- STATO TOUCH --- //
bool touch1WasPressed = false;  // stato touch nel ciclo precedente TOUCH 1
bool touch2WasPressed = false;  // stato touch nel ciclo precedente TOUCH 2

// === PROTOTIPI delle funzioni ===
void drawExpression(int type);
void animateBlink();
void performExpression(int type);
void drawDance();
void dfPlay(uint16_t n) {         
  myDFPlayer.play(n);
}
// --- modalita operative --- //
const int totalModes = MODE_TOTAL;
ModeType currentMode = MODE_EMOTIONS;  // inizializza a modalità emotions
// Stato precedente dei touch
bool lastTouch1Pressed = false;
bool lastTouch2Pressed = false;
static unsigned long touchStartTime = 0;
static unsigned long lastTouch2Time = 0;
static unsigned long lastTouch1Time = 0;
const unsigned long debounceDelay = 150;  
// --- espressioni
ExpressionType expression = EXP_NORMAL;
const int totalExpressions = EXP_TOTAL - 1; 
ExpressionType lastExpression = EXP_NORMAL;
//---- pupille
int pupilOffsetX = 0;
int pupilOffsetY = 0;
//---palpebre---//
unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 4000;  // ogni quanti ms far partire un blink spontaneo
bool isBlinking = false;
int blinkStep = 0;
// ---- ADDORMENTAMENTO  ----//
unsigned long sleepTimeout = 90000;  // 90 secondi DOPO QUANTO SI ADDORMENTA
unsigned long lastActivityTime = 0;
bool isSleeping = false;
SleepState sleepState = SLEEP_START;
unsigned long sleepTimer = 0;
int breathRadius = 8;
int zCount = 0;
//----lacrime ----//
// Variabili per animazione lacrime con esplosione
int tearY = 122;
int tearStartY = 122;
int tearEndY = 160;
unsigned long lastTearTime = 0;
int tearSpeed = 50;
bool tearJustStarted = true;
bool tearVisible = true;
bool tearExploding = false;
int explosionStep = 0;
int maxExplosionSteps = 4;
// --lacrimuccia
bool yawnRunning = false;     // indica se l’animazione sbadiglio è in corso
unsigned long yawnStartTime = 0;
int yawnPhase = 0;            // fasi dell’animazione sbadiglio
bool yawnTearActive = false;
int yawnTearY = 0;
unsigned long lastYawnTearUpdate = 0;
// -- battiti cuore --//
// Impostazioni animazione battito cuore
unsigned long lastHeartbeatTime = 0;
int heartbeatIndex = 0;
int heartbeatSizes[] = { 12, 16, 14, 13, 12 };      // battito veloce poi lento
int heartbeatDelays[] = { 50, 80, 120, 150, 200 };  // ritmi variabili
int numHeartbeatFrames = sizeof(heartbeatSizes) / sizeof(int);
bool isInLove = false;           // controlla se animare
// --- bluetooth --- ///
bool wasConnected = false;
bool lastBluetoothState = false;
static bool wasSleepingConnected = false;
// --- DANCE background ---
static uint32_t lastDanceBgTime = 0;
const uint32_t danceBgInterval = 300;   // ms cambio colore
// --- cantando
unsigned long lastFootMoveTime = 0;
bool footDown = false;
unsigned long footInterval = 600;  // battito ogni 600 ms (~100 BPM)
int currentSong = -1;
bool songStarted = false;
int lastSongPlayed = -1;
int MP3_MIN = 31;
int MP3_MAX = 34;
bool singerIntroDone = false;
unsigned long singerIntroStart = 0;
enum SingerState { INTRO_29, BASE_30, MAIN_SONG };
SingerState singerState = INTRO_29;
extern ModeType       currentMode;
extern ExpressionType lastExpression;
ModeType lastPrintedMode = static_cast<ModeType>(-1);
// balli
extern bool dance2Active ;
extern bool musicFinished ;
extern bool musicStarted ;
extern bool dance3Active ;
extern bool music3Finished ;
extern bool music3Started ;
extern bool dance4Active ;
extern bool music4Finished ;
extern bool music4Started ;
// --- Volume dfplayer 
int currentVolume = 25;
// velocita iniziale
int walkSpeed = 1000;

void setup() {
  Serial.begin(115200);  
  tft.init();
  tft.setRotation(2);
   performExpression(EXP_NORMAL);   // volto iniziale 
  lastExpression = EXP_NORMAL;
 // --- CANTANTE
 //initMusicalNotes();
  // Inizializza I2C sui pin specifici
  Wire.begin(21, 22);  // SDA = 21, SCL = 22
  if (!lox.begin()) {
    Serial.println("VL53L0X non trovato!");
    while (1);
  }
  Serial.println("VL53L0X pronto");
  randomSeed(micros());
  lastActivityTime = millis();
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
  Otto.sing(S_connection);
  // --- Bluetooth  ----//
  SerialBT.begin("EMOtto");
  Serial.println("Bluetooth avviato. Ora puoi accoppiare!");
  // ----- DFPlayer Mini ---- //
  // Avvia Serial2 su GPIO 32 (RX), GPIO 4 (TX)
  mySerial.begin(9600, SERIAL_8N1, 32, 4);
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println(" DFPlayer non trovato! Disabilitato.");
  } else {
    Serial.println("✅ DFPlayer inizializzato correttamente.");
    myDFPlayer.volume(currentVolume);
    delay(500);  // piccolo delay per sicurezza
      myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    myDFPlayer.play(1);
  }
  pinMode(TOUCH_PIN_1, INPUT_PULLDOWN);
  touch1WasPressed = digitalRead(TOUCH_PIN_1) == HIGH;
  pinMode(TOUCH_PIN_2, INPUT);
  touch2WasPressed = digitalRead(TOUCH_PIN_2) == HIGH;
  pinMode(DF_BUSY_PIN, INPUT_PULLUP);   // BUSY: HIGH = fermo, LOW = suona
  forceHome();
  // velocita iniziale
   walkSpeed = 1000;
   // Stati bluetooth
//    SerialBT.print("SPD:");
// SerialBT.println(walkSpeed);

// SerialBT.print("VOL:");
// SerialBT.println(currentVolume);

}

void loop() {
  unsigned long now = millis();
  bool touch1Pressed = digitalRead(TOUCH_PIN_1) == HIGH;
  bool touch2Pressed = digitalRead(TOUCH_PIN_2) == HIGH;
  // --- SLEEP MODE ---
  if (isSleeping) {
    updateSleepingAnimation();
    if ((touch1Pressed || touch2Pressed) && !touch1WasPressed && !touch2WasPressed) {
      touchStartTime = now;
    }
    if (!(touch1Pressed || touch2Pressed) && (touch1WasPressed || touch2WasPressed)) {
      wakeUp();
    }
    //  Risveglio tramite connessione Bluetooth
    if (SerialBT.connected()) {
      wakeUp();
    }
   touch1WasPressed = touch1Pressed;
   touch2WasPressed = touch2Pressed;
     return;
  }
  // --- ENTRA IN SLEEP SE INATTIVO ma solo se è in modalita emotions---
  if (!isSleeping
      && (now - lastActivityTime > sleepTimeout)
      && currentMode != MODE_AVOID
      && currentMode != MODE_FOLLOW
      && currentMode != MODE_DANCE
      && currentMode != MODE_SINGER
      && !SerialBT.hasClient()) {
    Serial.println(">> Condizione SLEEP soddisfatta");
    enterSleepMode();
    return;
  }
  // --- GESTIONE TOUCH 1: cambio espressione solo in modalità emozioni ---
  if (touch1Pressed && !touch1WasPressed && !isBlinking && currentMode == MODE_EMOTIONS && (now - lastTouch1Time > debounceDelay)) {
    lastTouch1Time = now;
    ExpressionType next = static_cast<ExpressionType>((expression + 1) % (totalExpressions + 1));
    Otto.sing(S_buttonPushed);
    performExpression(next);      // disegna + audio + movimento
    lastExpression   = next;
    lastActivityTime = now;
  }
  // --- GESTIONE TOUCH 2: cambio modalità ---
  if (touch2Pressed && !touch2WasPressed && (now - lastTouch2Time > debounceDelay)) {
    lastTouch2Time = now;
   if (currentMode == MODE_SINGER) {          // stop “d’emergenza”
    Serial.println(F(">> TOUCH2: esco da SINGER"));
    exitSingerMode(); 
    return;                                   // fine loop, niente altro da fare
  }
   if (currentMode == MODE_DANCE) {
        Serial.println(">> TOUCH2 premuto: fermo musica e movimenti (da DANCE)");
        myDFPlayer.stop();
        Otto.home();
        stopDance();
        songStarted = false;
        // 🔁 PASSA ALLA MODALITÀ SINGER
        currentMode = MODE_SINGER;
        lastExpression = EXP_NONE;
        Serial.println("Passo a modalità SINGER");
        return;
    }
    // Modalità normali: scorre ciclicamente
  /* --- ciclo modalità (EMOTIONS→…→SINGER→EMOTIONS) --- */
 currentMode = static_cast<ModeType>((currentMode + 1) % MODE_TOTAL);
    Serial.print(F(">> Cambio modalità: "));
    Serial.println(currentMode);
    // aggiorna stampa modalità subito dopo il cambio (opzionale)
    lastPrintedMode = static_cast<ModeType>(-1); // forza ristampa
   return;
}
  // --- STAMPA MODALITÀ SOLO SE CAMBIATA ---
  if (currentMode != lastPrintedMode) {
    switch (currentMode) {
      case MODE_AVOID: Serial.println("AVOID"); break;
      case MODE_FOLLOW: Serial.println("FOLLOW"); break;
      case MODE_DANCE: Serial.println("DANCE"); break;
      case MODE_SINGER: Serial.println("SINGER"); break;
      case MODE_EMOTIONS: Serial.println("EMOTIONS"); break;
    }
    lastPrintedMode = currentMode;
  }
  //  lastActivityTime = now;
  // Aggiorna stato precedente TOCCHI
  touch1WasPressed = touch1Pressed;
  touch2WasPressed = touch2Pressed;
  // --- verifica accoppiamento bluetooth ---///
  bool currentlyConnected = SerialBT.hasClient();
  if (currentlyConnected && !wasConnected) {
    // Appena connesso
    Serial.println("✅ Bluetooth connesso!");
    showBluetoothOn(expression);  // Mostra icona on alla connessione
    myDFPlayer.play(13); //modalita bluetooth attivata 
  } else if (!currentlyConnected && wasConnected) {
    showBluetoothOff(expression);  // Mostra icona off alla connessione
    Serial.println("❌ Bluetooth disconnesso!");
 //   myDFPlayer.play(13); //modalita bluetooth disattivata 
  }
  wasConnected = currentlyConnected;

  // --- GESTIONE MODALITÀ ---
    switch (currentMode) {
    case MODE_AVOID:
      if (lastExpression != EXP_AVOID) {
        performExpression(EXP_AVOID);
        lastExpression = EXP_AVOID;
      }
      handleAvoidMode();
      break;
    case MODE_FOLLOW:
      if (lastExpression != EXP_FOLLOW && !isBlinking) {
        performExpression(EXP_FOLLOW);
        lastExpression = EXP_FOLLOW;
      }
      handleFollowMode();
      break;
    case MODE_DANCE:
      if (currentMode != MODE_DANCE) break;  // Protezione extra
       if (lastExpression != EXP_DANCE && !isBlinking) {
        updateDance();      // gestisce passi
        performExpression(EXP_DANCE);   // Avvia danza
        lastExpression = EXP_DANCE;
 }
        updateDance();      // ballo attivo
        handleDanceMode();
        break; 
     case MODE_SINGER: {
   /* ── Primo ingresso ── */
       if (lastExpression != EXP_SINGER && !isBlinking) {
        performExpression(EXP_SINGER);      // faccina cantante
        lastExpression = EXP_SINGER;
        singerState = INTRO_29;
        startSingerFoot();                  // tuoi passi di ballo
        dfPlay(29);                         // intro vocale
  }
         drawSingingMouth();
         updateSingerFoot();
  /* ── Avanzamento stati con BUSY ── */
  switch (singerState) {
    case INTRO_29:
      if (!isPlaying() && wasPlaying) {     // 29 terminata
        dfPlay(30);                         // base musicale
        singerState = BASE_30;
      }
        break;

    case BASE_30:
      if (!isPlaying() && wasPlaying) {     // 30 terminata
        playRandomSong();                   // tua routine
        singerState = MAIN_SONG;
      }
      break;

    case MAIN_SONG:
      if (!isPlaying() && wasPlaying) {     // brano finito
        exitSingerMode();
      }
      break;
  }
  /* ── Salva stato BUSY per il prossimo loop ── */
  wasPlaying = isPlaying();
  break;
}
     case MODE_EMOTIONS:
       if (expression != lastExpression && !isBlinking) {
        performExpression(expression);
        lastExpression = expression;
  }
    break;
     default:
    break;
    }
   // --- ANIMAZIONE BLINK ---
  if (!isBlinking && (now - lastBlinkTime > blinkInterval)) {
    isBlinking = true;
    blinkStep = 0;
  }
  if (isBlinking) {
    animateBlink();
  }
  if ((expression == EXP_LOVE || expression == EXP_FOLLOW)   // ❤ anche in follow
    && !isBlinking
    && !isSleeping) {
    updateHeartEyes();
  }
  // --- ANIMAZIONE LACRIME ---
  if (expression == EXP_SAD && !isBlinking && !isSleeping) {
    updateTears();
  }
  // --- LACRIMUCCIA POST-SBADIGLIO ---
// Chiamare updateYawnAnimation() ogni ciclo
updateYawnAnimation();
// Chiamare updateYawnTear() per animazione lacrima
updateYawnTear();
// --- Sfondo cangiante mentre balla ---
if (expression == EXP_DANCE && millis() - lastDanceBgTime > danceBgInterval && !isBlinking) {
  tft.fillScreen(nextPastelColor());
    drawDance();
  lastDanceBgTime = millis();
}
 // --- riceve comandi bluetooth --- //
  handleBluetoothCommands(SerialBT, expression, currentMode, lastActivityTime);
  updateWalking();
 // richiamo balli
if (dance2Active) {
  updateDance2();
  updateMusic2Status();
}
  if (danceStep != STEP_NONE && !musicFinished) {
    updateDance();
  }
if (dance3Active) {
  updateDance3();
  updateMusic3Status();
}
if (dance4Active) {
  updateDance4();
  updateMusic4Status();
}

}
// --- Fine Loop --- //
// *******************  FUNZIONI DI SUPPORTO  ******************* //
void forceHome() {
  Otto.attachServos();
  int homes[4] = { 90, 90, 90, 90 };
  Otto._moveServos(500, homes);  // Muove forzatamente, bypassa Otto.home()
  delay(700);
  Otto.detachServos();
  Otto.setRestState(true);  // Mantieni coerenza col flag
}

void handleAvoidMode() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4) {
    int distanza = measure.RangeMilliMeter;
    Serial.print("AVOID - Distanza: ");
    Serial.println(distanza);
  if (distanza < 150) {
    drawExpression(EXP_ANGRY);
      Otto.walk(2, 1000, -1);  // BACKWARD x2
      Otto.turn(3, 1000, 1);   // LEFT x3
    }
    Otto.walk(1, 1000, 1);  // FORWARD x1
  }
}

void handleFollowMode() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4) {
    int distanza = measure.RangeMilliMeter;
    Serial.print("FOLLOW - Distanza: ");
    Serial.println(distanza);
  if (distanza > 180 && distanza < 600) {
      Otto.walk(1, 1000, 1);  // cammina avanti
    } else {
      //     Otto.stop();
      drawExpression(EXP_NORMAL);
    }
  }
}

void handleDanceMode() {
  // sfondo cangiante
  if (millis() - lastDanceBgTime > danceBgInterval && !isBlinking) {
        tft.fillScreen(nextPastelColor()); // sfondo nuovo
    drawDance();   
    lastDanceBgTime = millis();
  }
}
