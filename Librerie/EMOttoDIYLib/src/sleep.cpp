#include <Arduino.h>
#include <TFT_eSPI.h>      // per tft
#include <EMOtto.h>
#include "sleep.h"
#include "expressions.h"   // per drawExpression
#include "draw_utils.h"          // per drawBlinkFrame()
#include "colors.h"  
#include "modes.h"

extern Otto Otto;

// === Funzione: entra in modalità sleep ===
void enterSleepMode() {
  Serial.println(">> Entrata modalità SLEEP");
  isSleeping = true;
 // pendingExpression = false;
    myDFPlayer.volume(30);
    myDFPlayer.play(2);
    delay(3000);
    myDFPlayer.volume(25);
    myDFPlayer.loop(3);
    sleepState = SLEEP_START;
    sleepTimer = millis();
    zCount = 0;

  forceHome(); // Reset posizione
}

void wakeUp() {
  Serial.println(">> WAKE UP!");
  isSleeping = false;
   //myDFPlayer.stop();
   myDFPlayer.play(6);
 drawExpression(EXP_NORMAL); // torna a espressione normale
  expression = EXP_NORMAL;
  lastExpression = EXP_NORMAL;
 // pendingExpression = true;
  lastActivityTime = millis();
  touch1WasPressed = true;  // <-- IMPORTANTE: ignora subito il primo tocco dopo il risveglio
  touch2WasPressed = true;
}

void updateSleepingAnimation() {
  unsigned long now = millis();

  switch (sleepState) {

    case SLEEP_START:
    forceHome();  
      Serial.println(">> Modalità SLEEP attivata");
      tft.fillScreen(TFT_BLACK);
      sleepTimer = now;
      sleepState = SLEEP_BLINK;
      break;

    case SLEEP_BLINK:
      if (now - sleepTimer >= 100) {
        static int blinkHeight = 0;
        drawBlinkFrame(blinkHeight);
        blinkHeight += 10;
        sleepTimer = now;
        if (blinkHeight > 60) {
          blinkHeight = 0;
          delay(200); // Occhi chiusi
          sleepState = SLEEP_FACE;
        }
      }
      break;

    case SLEEP_FACE:
      // Mostra occhi chiusi curvi
      tft.fillScreen(TFT_BLACK);

      for (int i = 0; i < 5; i++) {
        tft.drawLine(75 + i, 115 + i, 105 - i, 115 + i, TFT_ARANCIONE);
        tft.drawLine(135 + i, 115 + i, 165 - i, 115 + i, TFT_ARANCIONE);
      }
      sleepTimer = now;
      sleepState = SLEEP_MOVE;
      break;

    case SLEEP_MOVE:
  //Otto.playGesture(OttoSleeping);  // Movimento addormentamento
  //delay(1500);                     // tempo per concludere gesto
  sleepTimer = now;
  breathRadius = 8;
  sleepState = SLEEP_BREATH_OUT;  // continua con la respirazione
  break;

    case SLEEP_BREATH_OUT:
      if (now - sleepTimer >= 150) {
        tft.fillCircle(120, 160, breathRadius - 1, TFT_BLACK);
        tft.fillCircle(120, 160, breathRadius, TFT_MAGENTA);
        breathRadius++;
        sleepTimer = now;
        if (breathRadius > 14) {
          sleepTimer = now + 800; // pausa espirazione
          sleepState = SLEEP_BREATH_IN;
        }
      }
      break;

    case SLEEP_BREATH_IN:
      if (now - sleepTimer >= 150) {
        tft.fillCircle(120, 160, breathRadius + 1, TFT_BLACK);
        tft.fillCircle(120, 160, breathRadius, TFT_MAGENTA);
        breathRadius--;
        sleepTimer = now;
        if (breathRadius < 8) {
          sleepTimer = now + 1000; // pausa inspirazione
          sleepState = SLEEP_ZZZ;
        }
      }
      break;

    case SLEEP_ZZZ:
      if (now - sleepTimer >= 150) {
        // Cancella zona Z
        tft.fillRect(120, 0, 120, 80, TFT_BLACK);

        for (int i = 0; i < 3; i++) {
          tft.setTextColor(TFT_BLUE, TFT_BLACK);
          tft.setTextSize(i + 1);
          int x = 170 - i * 15;
          int y = 30 - i * 15 + 10;
          tft.setCursor(x, y);
          tft.print("Z");
          delay(250);  // breve pausa tra le Z
        }

        delay(600); // Pausa Z
        for (int i = 0; i < 3; i++) {
          tft.setTextColor(TFT_BLACK);
          tft.setTextSize(i + 1);
          int x = 170 - i * 15;
          int y = 30 - i * 15 + 10;
          tft.setCursor(x, y);
          tft.print("Z");
          delay(150);
        }

        tft.setTextSize(1);
        zCount++;
        sleepTimer = now;
        sleepState = SLEEP_BREATH_OUT; // loop continuo respirazione + Z
      }
      break;
    default:
      break;
  }
}
