#include <EMOtto.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <TFT_eSPI.h>
#include "draw_utils.h"
#include "colors.h"
#include "expressions.h" 
#include "BluetoothCommands.h"
#include "modes.h"
#include "sleep.h"
#include <DFRobotDFPlayerMini.h>
#include "dance.h"
#include "dance2.h"
#include "dance3.h"
#include "dance4.h"

extern Otto Otto;
// dichiarazioni per camminare continuamente
bool walkingForward = false;
bool walkingBackward = false;
bool turningLeft = false;
bool turningRight = false;
//int walkSpeed = 1000;  // Durata di un passo in ms (minore = più veloce)



// Esterni definiti nel main sketch
extern void performExpression(ExpressionType type);
extern void drawExpression(ExpressionType expression);
extern void forceHome();
extern DFRobotDFPlayerMini myDFPlayer;
extern int currentVolume;
extern int walkSpeed;

void updateWalking() {
  if (walkingForward) {
    Otto.walk(1, walkSpeed, 1);
  }
  if (walkingBackward) {
    Otto.walk(1, walkSpeed, -1);
  }
  if (turningLeft) {
    Otto.turn(1, walkSpeed, -1);
  }
  if (turningRight) {
    Otto.turn(1, walkSpeed, 1);
  }
}

void handleBluetoothCommands(BluetoothSerial &SerialBT, ExpressionType &expression, ModeType &currentMode, unsigned long &lastActivityTime) {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    if (cmd == '\n' || cmd == '\r') return;
    if (cmd >= '0' && cmd <= '9') return; // ignoriamo numeri da soli
    Serial.println("=== Comando Bluetooth Ricevuto ===");
    Serial.print("[BT] Carattere: ");
    Serial.print(cmd);
    Serial.print(" | ASCII: ");
    Serial.println((int)cmd);

    switch (cmd) {
      // Espressioni
      case 'N': expression = EXP_NORMAL; Serial.println("[ESP] Set: NORMAL"); break;
      case 'A': expression = EXP_ANGRY; Serial.println("[ESP] Set: ANGRY"); break;
      case 'L': expression = EXP_LOVE;  Serial.println("[ESP] Set: LOVE"); break;
      case 'S': expression = EXP_SAD;   Serial.println("[ESP] Set: SAD"); break;
      case 'g': expression = EXP_DISGUST;   Serial.println("[ESP] Set: DISGUST"); break;
      case 'e': expression = EXP_EMBARRASSED;   Serial.println("[ESP] Set: EMBARRASSED"); break;
      case 'b': expression = EXP_BORED,   Serial.println("[ESP] Set: BORED"); break;
      case 'a': expression = EXP_ANXIOUS,   Serial.println("[ESP] Set: ANXIOUS"); break;
      case 'u': expression = EXP_SURPRISED,   Serial.println("[ESP] Set: SURPRISED"); break;
      case 'n': expression = EXP_NOSTALGIC,   Serial.println("[ESP] Set: NOSTALGIC"); break;

      // Modalità
      case 'F': currentMode = MODE_FOLLOW;    Serial.println("[MODE] Set: FOLLOW"); break;
      case 'V': currentMode = MODE_AVOID;     Serial.println("[MODE] Set: AVOID"); break;
      case 'E': currentMode = MODE_EMOTIONS;  Serial.println("[MODE] Set: EMOTIONS"); break;
     // case 'd': currentMode = MODE_DANCE;     Serial.println("[MODE] Set: DANCE"); break;
      case 'G': currentMode = MODE_SINGER;    Serial.println("[MODE] Set: SINGER"); break;
      // Attiva sleep
      case 'Z': if (!isSleeping) { Serial.println("[MODE] Set: SLEEP"); enterSleepMode(); return; } break;
      case 'w': if (isSleeping) {  Serial.println("[MODE] Set: Wake Up"); wakeUp();} break;
      // Movimenti
    
  case 'W': walkingForward = true; break;
  case 'i': walkingBackward = true; break;
  case 's': turningLeft = true; break;
  case 'D': turningRight = true; break;

  case 'X':  // STOP generale
    walkingForward = false;
    walkingBackward = false;
    turningLeft = false;
    turningRight = false;
    Otto.home();  // Ferma tutto
    break;
      // Regolazione velocità
case '+':
  if (walkSpeed > 200) walkSpeed -= 100;
  Serial.print("[SPD] Aumentata: "); Serial.println(walkSpeed);
  SerialBT.print("SPD:");
   SerialBT.println(walkSpeed); // invia subito
  break;

case '-':
  if (walkSpeed < 2000) walkSpeed += 100;
  Serial.print("[SPD] Diminuita: "); Serial.println(walkSpeed);
  SerialBT.print("SPD:"); 
  SerialBT.println(walkSpeed); // invia subito
  break;
        case 'B': { // B velocita gestita da cursore
        String speedStr = SerialBT.readStringUntil('\n');  // es: "1200"
        int newSpeed = speedStr.toInt();
        if (newSpeed >= 200 && newSpeed <= 2000) {
          walkSpeed = newSpeed;
          Serial.print("[SPD] Velocità impostata da cursore: ");
          Serial.println(walkSpeed);
          SerialBT.print("SPD:");
          SerialBT.println(walkSpeed);
        } else {
          Serial.println("[SPD] Valore non valido");
        }
        break;
      }
// canzoni
case '|': myDFPlayer.play(31); Serial.println("[AUDIO] Suona canzone 1"); break;
case '!': myDFPlayer.play(32); Serial.println("[AUDIO] Suona canzone 2"); break;
case '"': myDFPlayer.play(33); Serial.println("[AUDIO] Suona canzone 3"); break;
case '$': myDFPlayer.play(34); Serial.println("[AUDIO] Suona canzone 3"); break; 
case '^': myDFPlayer.stop();   Serial.println("[AUDIO] Stop musica");     break; 
case ',': startDance();        SerialBT.println("Dance 1: "); break;

case '.': startDance2();       SerialBT.println("Dance 2: "); break;
case '_': startDance3();       SerialBT.println("Dance 3: "); break;
case '*': startDance4();       SerialBT.println("Dance 4: "); break;



      case 'H': Serial.println("[MOV] Home Pose"); forceHome(); break;
// Volume
case 'U':
  if (currentVolume < 30) currentVolume++;
  myDFPlayer.volume(currentVolume);
  Serial.print("[AUDIO] Volume su: "); Serial.println(currentVolume);
  SerialBT.print("VOL:");  SerialBT.println(currentVolume);
  break;

case 'J':
  if (currentVolume > 0) currentVolume--;
  myDFPlayer.volume(currentVolume);
  Serial.print("[AUDIO] Volume giù: "); Serial.println(currentVolume);
  SerialBT.print("VOL:");  SerialBT.println(currentVolume);
  break;
      case 'v': {
        String volStr = SerialBT.readStringUntil('\n'); // es: "25"
        int newVol = volStr.toInt();
        if (newVol >= 0 && newVol <= 30) {
          currentVolume = newVol;
          myDFPlayer.volume(currentVolume);
          Serial.print("[AUDIO] Volume impostato da cursore: "); Serial.println(currentVolume);
          SerialBT.print("VOL:"); SerialBT.println(currentVolume);
        } else {
          Serial.println("[AUDIO] Volume ricevuto non valido.");
        }
        break;
      }
//Mixer
case '?': myDFPlayer.EQ(DFPLAYER_EQ_NORMAL); Serial.println("[MIXER] EQUALIZZATORE = NORMAL"); break;
case '=': myDFPlayer.EQ(DFPLAYER_EQ_POP); Serial.println("[MIXER] EQUALIZZATORE = POP"); break;
case ')': myDFPlayer.EQ(DFPLAYER_EQ_ROCK); Serial.println("[MIXER] EQUALIZZATORE = ROCK"); break;
case '(': myDFPlayer.EQ(DFPLAYER_EQ_JAZZ); Serial.println("[MIXER] EQUALIZZATORE = JAZZ"); break;
case '/': myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC); Serial.println("[MIXER] EQUALIZZATORE = CLASSIC"); break;
case '&': myDFPlayer.EQ(DFPLAYER_EQ_BASS); Serial.println("[MIXER] EQUALIZZATORE = BASS"); break;



      default:

        Serial.println("[BT] Comando sconosciuto.");
        break;

         updateDance(); updateDance2(); 
        // updateDance3(); updateDance4();
    }

    // Se è un'espressione, la eseguiamo
    if (cmd == 'N' || cmd == 'A' || cmd == 'L' || cmd == 'S' || cmd == 'g'|| cmd == 'e'|| cmd == 'b'|| cmd == 'a'|| cmd == 'u'|| cmd == 'n') {
      Serial.println("[ESP] Eseguo performExpression() e drawExpression()");
      performExpression(expression);
      drawExpression(expression);
     lastExpression = expression; // 🔧 Previene doppia esecuzione nel loop()
    }

    lastActivityTime = millis();
    Serial.println("=== Fine comando Bluetooth ===\n");
  }
}

