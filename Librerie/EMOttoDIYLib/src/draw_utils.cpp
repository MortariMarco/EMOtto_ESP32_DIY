//* draw_utils.cpp
#include <Adafruit_GFX.h>
#include <TFT_eSPI.h>
#include <EMOtto.h>
#include "draw_utils.h"
#include "colors.h"
#include "expressions.h" 
#include "modes.h"
#include <DFRobotDFPlayerMini.h>

extern Otto Otto;
extern int pupilOffsetX;
extern int pupilOffsetY;
extern ExpressionType expression;
extern int blinkStep;
extern bool isBlinking;
extern unsigned long lastBlinkTime;
extern int blinkStep;
extern bool tearJustStarted;
extern int tearY;
extern  int tearStartY;
extern  int tearEndY;
extern unsigned long lastTearTime;
extern  int tearSpeed; 
extern bool tearVisible;
extern bool tearExploding;
extern int explosionStep;
extern  int maxExplosionSteps;
extern unsigned long lastHeartbeatTime;
extern int heartbeatIndex;
extern int heartbeatSizes[];
extern int heartbeatDelays[];
extern  int numHeartbeatFrames;
extern bool isInLove;  
//lacrimuccia
extern bool yawnRunning;     // indica se l’animazione sbadiglio è in corso
extern unsigned long yawnStartTime;
extern int yawnPhase;            // fasi dell’animazione sbadiglio
extern bool yawnTearActive;
extern int yawnTearY;
extern unsigned long lastYawnTearUpdate;
// cantando
extern unsigned long lastFootMoveTime;
extern bool footDown;
extern unsigned long footInterval;  
extern int currentSong;
extern bool songStarted;
extern int MP3_MIN;
extern int MP3_MAX;
extern DFRobotDFPlayerMini myDFPlayer;
extern int lastSongPlayed;
extern ModeType currentMode;
extern ExpressionType lastExpression;

// === Occhi ===
// === Occhi con movimento asincrono e riflessi realistici ===
void drawEyes() {
  int eyeRadius   = 20;
  int pupilRadius = 8;
  int eyeLX = 80;
  int eyeRX = 160;
  int eyeY  = 100;

  // Offset casuali separati per ogni pupilla
  int offsetLX = random(-2, 3);
  int offsetLY = random(-2, 3);
  int offsetRX = random(-2, 3);
  int offsetRY = random(-2, 3);

  // Contorno occhi (nero)
  tft.fillCircle(eyeLX, eyeY, eyeRadius + 2, TFT_BLACK);
  tft.fillCircle(eyeRX, eyeY, eyeRadius + 2, TFT_BLACK);

  // Sclera (bianco)
  tft.fillCircle(eyeLX, eyeY, eyeRadius, TFT_WHITE);
  tft.fillCircle(eyeRX, eyeY, eyeRadius, TFT_WHITE);

  // Posizioni delle pupille
  int pupilLX = eyeLX + offsetLX;
  int pupilLY = eyeY + offsetLY;
  int pupilRX = eyeRX + offsetRX;
  int pupilRY = eyeY + offsetRY;

  // Pupille (nero)
  tft.fillCircle(pupilLX, pupilLY, pupilRadius, TFT_BLACK);
  tft.fillCircle(pupilRX, pupilRY, pupilRadius, TFT_BLACK);

  // Riflessi coerenti con il movimento della pupilla
  tft.fillCircle(pupilLX - 3, pupilLY - 3, 2, TFT_WHITE);
  tft.fillCircle(pupilRX - 3, pupilRY - 3, 2, TFT_WHITE);
}


// --- PALPEBRE ---///
void drawBlinkFrame(int height) {
  // Altezza massima palpebra (copre tutta l'area occhi)
  if (height > 60) height = 60;

  // Ridisegna sfondo volto (opzionale, solo se serve pulire)
  // tft.fillCircle(120, 120, 120, GC9A01A_BLACK); 

  // Ridisegna occhi base (puoi adattare secondo il tuo stile)
  tft.fillCircle(90, 120, 25, TFT_WHITE);   // occhio sinistro
  tft.fillCircle(150, 120, 25, TFT_WHITE);  // occhio destro

  // Pupille fisse
  tft.fillCircle(90, 120, 8, TFT_BLACK);
  tft.fillCircle(150, 120, 8, TFT_BLACK);

  // Disegna palpebre (rettangoli neri che scendono)
  tft.fillRect(65, 95, 50, height, TFT_BLACK);  // palpebra sinistra
  tft.fillRect(125, 95, 50, height, TFT_BLACK); // palpebra destra
}

void drawEyelids(int height) {
  int eyeLX = 80;
  int eyeRX = 160;
  int eyeY  = 100;
  int eyeRadius = 20;

  // Colore "pelle" in base all'espressione
uint16_t skinColor = getSkinColor(expression);

  // Palpebre superiori (rettangoli)
  tft.fillRect(eyeLX - 20, eyeY - eyeRadius, 40, height, skinColor); // SX
  tft.fillRect(eyeRX - 20, eyeY - eyeRadius, 40, height, skinColor); // DX

  // Linea inferiore della palpebra (contorno nero)
  tft.drawLine(eyeLX - 20, eyeY - eyeRadius + height, eyeLX + 20, eyeY - eyeRadius + height, TFT_BLACK);
  tft.drawLine(eyeRX - 20, eyeY - eyeRadius + height, eyeRX + 20, eyeY - eyeRadius + height, TFT_BLACK);
}

void animateBlink() {
  static unsigned long blinkFrameTime = 0;
  unsigned long now = millis();
  if (now - blinkFrameTime < 100) return; // nuovo frame ogni 100 ms
  blinkFrameTime = now;

  switch (blinkStep) {
    case 0:
      drawEyelids(60);  // palpebra a metà chiusa
      break;
    case 1:
      drawEyelids(100); // occhi completamente chiusi
      break;
    case 2:
      drawEyelids(60);  // riapertura parziale
      break;
    case 3:
      drawExpression(expression); // ridisegna espressione base
      isBlinking = false;
      lastBlinkTime = millis();
      break;
  }
  blinkStep++;
}
// --- occhi disgusto
void drawEyesDisgust() {
  drawEyes();          // occhi standard
  drawEyelids(20);     // palpebre a ~ metà
}
//  occhi annoiato
void drawEyesBored() {
  drawEyes();        // occhi standard
  drawEyelids(15);   // palpebra abbassata
}
// occhi ansia
void drawEyesAnxious() {
  int eyeRadius   = 20;
  int pupilRadius = 6;  // Pupille più piccole → ansia
  int eyeLX = 80;
  int eyeRX = 160;
  int eyeY  = 100;

  pupilOffsetX = random(-4, 5);  // Più movimento → panico
  pupilOffsetY = random(-4, 5);

  tft.fillCircle(eyeLX, eyeY, eyeRadius + 3, TFT_BLACK);   // occhio più marcato
  tft.fillCircle(eyeRX, eyeY, eyeRadius + 3, TFT_BLACK);

  tft.fillCircle(eyeLX, eyeY, eyeRadius, TFT_WHITE);
  tft.fillCircle(eyeRX, eyeY, eyeRadius, TFT_WHITE);

  tft.fillCircle(eyeLX + pupilOffsetX, eyeY + pupilOffsetY, pupilRadius, TFT_BLACK);
  tft.fillCircle(eyeRX + pupilOffsetX, eyeY + pupilOffsetY, pupilRadius, TFT_BLACK);

  tft.fillCircle(eyeLX - 5, eyeY - 5, 2, TFT_WHITE);
  tft.fillCircle(eyeRX - 5, eyeY - 5, 2, TFT_WHITE);
}

// -- occhi nostalgia 
void drawEyesNostalgic() {
  int eyeRadius   = 20;
  int pupilRadius = 7;
  int eyeLX = 80;
  int eyeRX = 160;
  int eyeY  = 100;

  // Sguardo leggermente verso l'alto (sognante)
  pupilOffsetX = 0;
  pupilOffsetY = -3;

  tft.fillCircle(eyeLX, eyeY, eyeRadius + 2, TFT_BLACK); // contorno
  tft.fillCircle(eyeRX, eyeY, eyeRadius + 2, TFT_BLACK);

  tft.fillCircle(eyeLX, eyeY, eyeRadius, TFT_WHITE);     // sclera
  tft.fillCircle(eyeRX, eyeY, eyeRadius, TFT_WHITE);

  tft.fillCircle(eyeLX + pupilOffsetX, eyeY + pupilOffsetY, pupilRadius, TFT_BLACK);  // pupille
  tft.fillCircle(eyeRX + pupilOffsetX, eyeY + pupilOffsetY, pupilRadius, TFT_BLACK);

  tft.fillCircle(eyeLX - 5, eyeY - 5, 2, TFT_WHITE);     // riflessi
  tft.fillCircle(eyeRX - 5, eyeY - 5, 2, TFT_WHITE);
}

// === Bocca ===
//--- bocca sorriso ---//
void drawSmile() {
  for (int i = 0; i <= 180; i += 2) {
    float rad = radians(i);
    int x = 120 + 25 * cos(rad);
    int y = 160 + 10 * sin(rad);
    tft.fillCircle(x, y, 1, TFT_BLACK); // bocca spessa
  }
}
// --- bocca dritta ---//
void drawStraightMouth() {
  tft.fillRect(100, 157, 40, 6, TFT_BLACK);
}
// --- bocca Sad ---//
void drawSadMouth() {
  for (int i = 180; i <= 360; i += 2) {
    float rad = radians(i);
    int x = 120 + 25 * cos(rad);
    int y = 160 + 10 * sin(rad);
    tft.fillCircle(x, y, 1, TFT_BLACK);
  }
}
// --- bocca O ---//
void drawOMouth() {
  tft.fillCircle(120, 160, 10, TFT_BLACK);
  tft.fillCircle(120, 160, 6, TFT_WHITE);
}
// --- bocca sorriso aperta
void drawMouthOpenSmile() {
    tft.fillCircle(120, 160, 10, TFT_BLACK);
  tft.fillCircle(120, 160, 6, TFT_WHITE);
}
// --- bocca disgusto
void drawDisgustMouth() {
  // cinque segmenti alternati ↑↓
  const int startX = 95;
  const int yBase  = 160;
  const int segW   = 10;
  const int segH   = 6;
  for (int i = 0; i < 5; i++) {
    int y = yBase + ((i % 2 == 0) ? -segH : 0);
    tft.fillRect(startX + i * segW, y, segW, 2, TFT_BLACK);
  }
 //piccola lingua centrale (facoltativa, effetto “bleah”)
 //  tft.fillRect(118, yBase + 4, 4, 6, TFT_MAGENTA);
}
// --- bocca imbarazzato
void drawEmbarrassedMouth() {
  // Bocca tipo sorriso nervoso (piccolo, ovale)
  tft.fillEllipse(120, 160, 8, 4, TFT_BLACK);
}

// --- bocca annoiato
void drawBoredMouth() {
  for (int i = 180; i <= 360; i += 2) {
    float rad = radians(i);
    int x = 120 + 15 * cos(rad);
    int y = 160 + 5 * sin(rad);
    tft.fillCircle(x, y, 1, TFT_BLACK);
  }
}
// -- Bocca ansiosa
void drawWavyMouth(int cx, int cy, int width, int amplitude) {
  int segments = 6;
  int segWidth = width / segments;
  for (int i = 0; i < segments; i++) {
    int x0 = cx - width / 2 + i * segWidth;
    int x1 = x0 + segWidth;
    int y0 = cy + ((i % 2 == 0) ? -amplitude : amplitude);
    int y1 = cy + (((i + 1) % 2 == 0) ? -amplitude : amplitude);
    tft.drawLine(x0, y0, x1, y1, TFT_BLACK);
  }
}
// --- bocca nostalgia
void drawMouthNostalgic() {
  int startX = 95;
  int endX = 145;
  int centerY = 175;

  for (int x = startX; x <= endX; x += 1) {
    float t = (float)(x - startX) / (endX - startX);  // da 0 a 1
    // curva poco arcuata verso il basso, forma simile a parentesi rovesciata
    int y = centerY + (int)(4 * sin(t * PI));  // ampiezza 4 pixel, morbida
    tft.fillCircle(x, y, 1, TFT_BLACK);
  }
}


// --- Guance ---//
void drawBlush() {
  tft.fillCircle(50, 130, 4, TFT_RED);
  tft.fillCircle(190, 130, 4, TFT_RED);
}
// --- Sopraciglia ---//
void drawBrowsNormal() {
  int thickness = 2;      // spessore sopracciglia
  int heightOffset = 0;  // spostamento verso l'alto

  for (int i = 0; i < thickness; i++) {
    int offset = i;
    // sopracciglio sinistro
    tft.drawLine(60, 70 + heightOffset + offset, 100, 70 + heightOffset + offset, TFT_BLACK);
    // sopracciglio destro
    tft.drawLine(140, 70 + heightOffset + offset, 180, 70 + heightOffset + offset, TFT_BLACK);
  }
}

// // --- Sopraciglia Arrabbiato ---//
void drawBrowsAngry() {
  int shiftY = 3; // quanti pixel spostare in alto

  // sopracciglia sinistra spesse
  for (int offset = 0; offset < 4; offset++) {
    tft.drawLine(60, 70 - shiftY + offset, 100, 80 - shiftY + offset, TFT_BLACK);
  }
  // sopracciglia destra spesse
  for (int offset = 0; offset < 4; offset++) {
    tft.drawLine(140, 80 - shiftY + offset, 180, 70 - shiftY + offset, TFT_BLACK);
  }
}

// --- Sopraciglia Sorpreso ---//
void drawBrowsSurprised() {
  int thickness = 2;     // spessore sopracciglia
  int heightOffset = -3; // spostamento verso l'alto

  for (int i = 0; i < thickness; i++) {
    int offset = i;
    // sopracciglio sinistro
    tft.drawLine(60, 60 + heightOffset + offset, 100, 60 + heightOffset + offset, TFT_BLACK);
    // sopracciglio destro
    tft.drawLine(140, 60 + heightOffset + offset, 180, 60 + heightOffset + offset, TFT_BLACK);
  }
}
// --- Sopraciglia Sad ---//
void drawBrowsSad() {
  int shiftY = 3; // pixel da spostare in alto

  for (int offset = 0; offset < 2; offset++) {
    // sopracciglia sinistra spesse (2 linee parallele)
    tft.drawLine(60, 80 - shiftY + offset, 100, 70 - shiftY + offset, TFT_BLACK);
    // sopracciglia destra spesse (2 linee parallele)
    tft.drawLine(140, 70 - shiftY + offset, 180, 80 - shiftY + offset, TFT_BLACK);
  }
}
// --- sopraciglia disgusto
void drawBrowsDisgust() {
  int thickness = 2;     // spessore sopracciglio
  int heightOffset = -3; // spostamento verso l’alto

  // sopracciglio sinistro (inclinato in su verso l’esterno)
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(55, 75 + heightOffset + offset,  95, 65 + heightOffset + offset, TFT_BLACK);
  }

  // sopracciglio destro (inclinato in giù verso l’esterno)
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(145, 65 + heightOffset + offset, 185, 75 + heightOffset + offset, TFT_BLACK);
  }
}
// -- sopracciglia imbarazzate
void drawBrowsEmbarrassed() {
  int thickness = 2;     // spessore sopracciglio
  int heightOffset = -3; // spostamento verso l’alto

  // sopracciglio sinistro
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(60, 75 + heightOffset + offset, 100, 65 + heightOffset + offset, TFT_BLACK);
  }

  // sopracciglio destro
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(140, 65 + heightOffset + offset, 180, 75 + heightOffset + offset, TFT_BLACK);
  }
}
// --- sopracciglia Annoiato 
void drawBrowsBored() {
  int shiftY = 3;  // pixel da spostare in alto
  int thickness = 2; // spessore

  for (int offset = 0; offset < thickness; offset++) {
    tft.drawLine(60, 75 - shiftY + offset, 100, 78 - shiftY + offset, TFT_BLACK);
    tft.drawLine(140, 78 - shiftY + offset, 180, 75 - shiftY + offset, TFT_BLACK);
  }
}
 // --- sopraccigli ansiose
void drawBrowsAnxious() {
  int thickness = 2;    // spessore sopracciglio (2 linee parallele)
  int heightOffset = -3; // spostamento verso l’alto

  int x1 = 80;  // centro sinistro
  int x2 = 160; // centro destro
  int y = 60 + heightOffset;
  int length = 20;

  // Sopracciglio sinistro (due linee parallele)
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(x1 - length, y + 3 + offset, x1, y - 3 + offset, TFT_BLACK);
    tft.drawLine(x1 + length, y + 3 + offset, x1, y - 3 + offset, TFT_BLACK);
  }

  // Sopracciglio destro (due linee parallele)
  for (int i = 0; i < thickness; i++) {
    int offset = i;
    tft.drawLine(x2 - length, y - 3 + offset, x2, y + 3 + offset, TFT_BLACK);
    tft.drawLine(x2 + length, y - 3 + offset, x2, y + 3 + offset, TFT_BLACK);
  }
}
// -- sopraciglia nostalgia
void drawBrowsNostalgic() {
  int thickness = 2;       // spessore sopracciglia
  int heightOffset = 0;   // spostamento verso l'alto

  for (int i = 0; i < thickness; i++) {
    int offset = i;
    // sopracciglio sinistro (inclina verso il basso)
    tft.drawLine(60, 75 + heightOffset + offset, 80, 70 + heightOffset + offset, TFT_BLACK);
    // sopracciglio destro (inclina verso il basso)
    tft.drawLine(160, 70 + heightOffset + offset, 180, 75 + heightOffset + offset, TFT_BLACK);
  }
}

// --- SOPRACIGLIA CANTO
void drawEyebrowsRaised() {
  int browLength = 40;
  int browHeight = 8;
  int leftX = 60;
  int rightX = 160;
  int browY = 70;

  // Sopracciglia sinistra: linea arcuata verso l’alto
  tft.drawLine(leftX, browY + browHeight, leftX + browLength / 2, browY - browHeight, TFT_BLACK);
  tft.drawLine(leftX + browLength / 2, browY - browHeight, leftX + browLength, browY + browHeight, TFT_BLACK);

  // Sopracciglia destra: linea arcuata verso l’alto
  tft.drawLine(rightX, browY + browHeight, rightX + browLength / 2, browY - browHeight, TFT_BLACK);
  tft.drawLine(rightX + browLength / 2, browY - browHeight, rightX + browLength, browY + browHeight, TFT_BLACK);
}

// === Lacrime ===
void drawTears() {
  for (int i = 0; i < 2; i++) {
    int x = (i == 0) ? 70 : 170;
    for (int j = 0; j < 3; j++) {
      tft.fillCircle(x, 115 + j * 10, 3, TFT_CYAN);
    }
  }
}

// --- animazione Lacrime ---//
void updateTears() {
  unsigned long now = millis();
  
  if (tearJustStarted) {
    // Mostra il primo frame visivo
    tft.fillCircle(80, tearY, 4, TFT_AZZURRO_CHIARO );
    tft.fillCircle(160, tearY, 4, TFT_AZZURRO_CHIARO );
    tearJustStarted = false;
    return;
  }
  if (tearExploding) {
    // Animazione esplosione
    drawExplosion(80, tearY);
    drawExplosion(160, tearY);
    explosionStep++;
    if (explosionStep > maxExplosionSteps) {
      tearExploding = false;
      tearVisible = true;
      tearY = tearStartY;
      // Pulisce area
      tft.fillCircle(80, tearEndY, 8, TFT_BLUE);
      tft.fillCircle(160, tearEndY, 8, TFT_BLUE);
    }
    delay(30);
    return;
  }

  if (now - lastTearTime >= tearSpeed) {
    lastTearTime = now;

    // Cancella precedente
    tft.fillCircle(80, tearY, 4, TFT_BLUE);
    tft.fillCircle(160, tearY, 4, TFT_BLUE);

    if (tearVisible) {
      tearY += 3;
      if (tearY >= tearEndY) {
        tearVisible = false;
        tearExploding = true;
        explosionStep = 0;
      }
    }

    if (tearVisible) {
      tft.fillCircle(80, tearY, 4, TFT_AZZURRO_CHIARO );  // AZZURRO
      tft.fillCircle(160, tearY, 4, TFT_AZZURRO_CHIARO );
    }
  }
}

void drawExplosion(int x, int y) {
  // Cancella centro
  tft.fillCircle(x, y, 8, TFT_BLUE );

  // Disegna gocce esplose
  int r = 2;
  tft.fillCircle(x - 5, y - 2, r, TFT_TURCHESE);
  tft.fillCircle(x + 5, y - 2, r, TFT_TURCHESE);
  tft.fillCircle(x - 3, y + 3, r, TFT_TURCHESE);
  tft.fillCircle(x + 3, y + 3, r, TFT_TURCHESE);
}

// --- Occhi a cuore ---//
void updateHeartEyes() {
  unsigned long currentTime = millis();
  if (currentTime - lastHeartbeatTime >= heartbeatDelays[heartbeatIndex]) {
    lastHeartbeatTime = currentTime;

    // Cancella occhi
    tft.fillCircle(80, 100, 20, TFT_ARANCIONE);
    tft.fillCircle(160, 100, 20, TFT_ARANCIONE);

    // Disegna nuovo frame cuore
    int r = heartbeatSizes[heartbeatIndex];
    drawHeart(80, 100, r);
    drawHeart(160, 100, r);

    heartbeatIndex = (heartbeatIndex + 1) % numHeartbeatFrames;
  }
}

// Funzione disegno cuore
void drawHeart(int x, int y, int r) {
  tft.fillCircle(x - r / 2, y - r / 2, r / 2, TFT_RED);
  tft.fillCircle(x + r / 2, y - r / 2, r / 2, TFT_RED);
  tft.fillTriangle(
    x - r, y - r / 2,
    x + r, y - r / 2,
    x,     y + r,
    TFT_RED
  );
}

// --- SIMBOLO BLUETOOTH ----//

// Disegna un punto rotante (effetto radar)
void drawRotatingDot(int cx, int cy, int radius, float angleDeg, uint16_t color) {
  float angleRad = angleDeg * 0.0174533;
  int x = cx + radius * cos(angleRad);
  int y = cy + radius * sin(angleRad);
  tft.fillCircle(x, y, 3, color);
}

void drawBluetoothRuneLogo(int cx, int cy, uint16_t color) {
  // Linea verticale centrale (spessore 3)
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx + i, cy - 24, cx + i, cy + 24, color);
  }

  // --- Runa H: la X spezzata, spessore 3 ---

  // Linea diagonale alto-sinistra -> centro
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx - 10, cy - 16 + i, cx + i, cy + i, color);
  }
  // Linea diagonale centro -> alto-destra
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx + i, cy + i, cx + 16, cy - 16 + i, color);
  }

  // Linea diagonale basso-sinistra -> centro
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx - 10, cy + 16 + i, cx + i, cy + i, color);
  }
  // Linea diagonale centro -> basso-destra
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx + i, cy + i, cx + 16, cy + 16 + i, color);
  }

  // --- Runa B: due triangoli attaccati alla verticale, spessore 3 ---

  // Triangolo superiore (linee)
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx + i, cy - 24, cx + 12 + i, cy - 12, color);
    tft.drawLine(cx + 12 + i, cy - 12, cx + i, cy - 8 + i, color);
  }

  // Triangolo inferiore (linee)
  for (int i = -1; i <= 1; i++) {
    tft.drawLine(cx + i, cy + 24, cx + 12 + i, cy + 12, color);
    tft.drawLine(cx + 12 + i, cy + 12, cx + i, cy + 8 + i, color);
  }
}
// Splash: Bluetooth ON
void showBluetoothOn(ExpressionType expression) {
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;

  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(centerX, centerY, 45, TFT_BLUE);

  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Bluetooth ON", centerX, centerY + 55, 2);

  // Animazione radar
  for (int i = 0; i < 2; i++) {
    for (int angle = 0; angle < 360; angle += 30) {
      tft.fillCircle(centerX, centerY, 45, TFT_BLUE);
      drawBluetoothRuneLogo(centerX, centerY, TFT_WHITE);
      drawRotatingDot(centerX, centerY, 55, angle, TFT_WHITE);
      delay(100);
    }
  }

  // Lampeggio simbolo
  for (int i = 0; i < 3; i++) {
    drawBluetoothRuneLogo(centerX, centerY, TFT_WHITE);
    delay(300);
    drawBluetoothRuneLogo(centerX, centerY, TFT_BLUE);  // "cancella"
    delay(200);
  }

  // Fisso finale
  drawBluetoothRuneLogo(centerX, centerY, TFT_WHITE);
  delay(1000);

  drawExpression(expression);
}

// Splash: Bluetooth OFF / Disconnesso
void showBluetoothOff(ExpressionType expression) {
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;

  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(centerX, centerY, 45, TFT_DARKGREY);  // Sfondo spento

  tft.setTextColor(TFT_RED);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Bluetooth OFF", centerX, centerY + 55, 2);

  // Simbolo Bluetooth spento (grigio)
  drawBluetoothRuneLogo(centerX, centerY, TFT_LIGHTGREY);

  // X rossa sopra
  tft.drawLine(centerX - 20, centerY - 20, centerX + 20, centerY + 20, TFT_RED);
  tft.drawLine(centerX + 20, centerY - 20, centerX - 20, centerY + 20, TFT_RED);

  delay(2000);

  drawExpression(expression);
}

// lacrimuccia
void animateTearDrop() {
  int x = 80;  // sotto occhio sinistro
  int y = 115;

  tft.fillCircle(x, y, 4, TFT_CYAN);         // corpo lacrima
  tft.fillCircle(x, y - 3, 2, TFT_AZZURRO_CHIARO);  // punto luce
}
void startYawnAnimation() {
  if (!yawnRunning) {
    yawnRunning = true;
    yawnStartTime = millis();
    yawnPhase = 0;
  }
}

void updateYawnAnimation() {
  if (!yawnRunning) return;

  unsigned long now = millis();
  switch (yawnPhase) {
    case 0:
      // fase 1: occhi semi-chiusi + bocca O (durata 400 ms)
      drawEyelids(40);
      drawOMouth();
      if (now - yawnStartTime > 400) {
        yawnPhase++;
        yawnStartTime = now;
      }
      break;

    case 1:
      // fase 2: bocca più aperta (durata 500 ms)
      tft.fillCircle(120, 160, 14, TFT_BLACK);
      tft.fillCircle(120, 160, 9, TFT_WHITE);
      if (now - yawnStartTime > 500) {
        yawnPhase++;
        yawnStartTime = now;
      }
      break;

    case 2:
      // fase 3: occhi più chiusi + bocca normale (durata 400 ms)
      drawEyelids(60);
      drawOMouth();
      if (now - yawnStartTime > 400) {
        yawnPhase++;
        yawnStartTime = now;
      }
      break;

    case 3:
      // fase 4: bocca chiusa bored (durata 300 ms)
      drawBoredMouth();
      if (now - yawnStartTime > 300) {
        yawnPhase++;
        yawnStartTime = now;
        startYawnTear();  // parte animazione lacrima
      }
      break;

    case 4:
      // animazione lacrima continua (gestita da updateYawnTear() nel loop)
      // qui solo attendiamo fine animazione lacrima
      if (!yawnTearActive) {
        yawnRunning = false;
        drawExpression(EXP_BORED);
      }
      break;
  }
}

// Avvia l'animazione lacrima sbadiglio
void startYawnTear() {
  yawnTearActive = true;
  yawnTearY = 115;  // posizione iniziale sotto occhio sinistro
  lastYawnTearUpdate = millis();
}

// Aggiorna animazione lacrima sbadiglio, da chiamare nel loop
void updateYawnTear() {
  if (!yawnTearActive) return;

  unsigned long now = millis();
  if (now - lastYawnTearUpdate < 50) return;  // aggiorna ogni 50 ms
  lastYawnTearUpdate = now;

  // Cancella lacrima precedente (usa colore sfondo volto)
  tft.fillCircle(80, yawnTearY, 5, TFT_GIALLO_CHIARO);

  // Sposta lacrima verso il basso
  yawnTearY += 2;

  // Disegna lacrima nuova posizione
  tft.fillCircle(80, yawnTearY, 4, TFT_CYAN);
  tft.fillCircle(80, yawnTearY - 3, 2, TFT_AZZURRO_CHIARO);

  // Se lacrima scende troppo, termina animazione
  if (yawnTearY >= 150) {
    yawnTearActive = false;
  }
}

// --- CANTANTE

void drawSingingMouth() {
  updateSingingMouth();  // solo animazione bocca
}


void updateSingingMouth() {
    // Cancella l’area bocca con il colore della pelle
  tft.fillRect(100, 148, 40, 25, getSkinColor(EXP_SINGER));  // rettangolo sopra la bocca
  int phase = (millis() / 200) % 3;
  switch (phase) {
    case 0: drawMouthOpen(); break;
    case 1: drawMouthMedium(); break;
    case 2: drawMouthClosed(); break;
  }
}

// Bocche diverse
void drawMouthOpen() {
  tft.fillEllipse(120, 160, 20, 12, TFT_RED);
}
void drawMouthMedium() {
  tft.fillEllipse(120, 160, 15, 8, TFT_RED);
}
void drawMouthClosed() {
  tft.drawLine(105, 160, 135, 160, TFT_BLACK);
}
// --- cantando
void startSingerFoot() {
  lastFootMoveTime = millis();
  footDown = false;
}
void updateSingerFoot() {
  unsigned long now = millis();

  if (now - lastFootMoveTime > footInterval) {
    lastFootMoveTime = now;
    footDown = !footDown;

    if (footDown) {
      Otto.swing(1, 300, 10);  // piccolo movimento: ampiezza 10°, durata 300ms
    }
  }
}
void playRandomSong() {

  int newSong;

  do {
    newSong = random(MP3_MIN, MP3_MAX + 1);
  } while (newSong == lastSongPlayed);

  lastSongPlayed = newSong;
  currentSong = newSong;

  myDFPlayer.play(currentSong);
  songStarted = true;
}
void exitSingerMode() {
  myDFPlayer.stop();
  Otto.home();
  songStarted    = false;
  currentMode    = MODE_EMOTIONS;
  lastExpression = EXP_NORMAL;
}
