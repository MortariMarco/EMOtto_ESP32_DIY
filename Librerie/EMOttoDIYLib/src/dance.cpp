#include "dance.h"
#include "EMOtto.h"
#include "DFRobotDFPlayerMini.h"

// Ottieni le istanze globali definite altrove
extern Otto Otto;                  // o il nome corretto della tua istanza
extern DFRobotDFPlayerMini myDFPlayer;
DanceStep danceStep = STEP_NONE;
unsigned long danceStepStartTime = 0;

// Flag per indicare se la musica principale è terminata
bool musicFinished = false;
bool musicStarted = false;

void startDance() {
  Serial.println(">> Inizio dance Smooth Criminal");
  danceStep = STEP_PLAY_INTRO;
  danceStepStartTime = millis();
  musicFinished = false;
    musicStarted = false;
  myDFPlayer.play(10);  // intro musicale Balliamo Dai
}

void updateDance() {
  unsigned long now = millis();

  // Dopo 3 secondi parte la musica principale
  if (danceStep == STEP_PLAY_INTRO && now >= danceStepStartTime + 3000) {
    myDFPlayer.play(4);  // Traccia principale
    musicStarted = true;
    danceStepStartTime = now;
    danceStep = STEP_SHAKE_LEG;
  }

  // Controlla se la musica è terminata leggendo il tipo di evento
  if (musicStarted && myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    if (type == DFPlayerPlayFinished && value == 4) {
      Serial.println(">> Musica finita!");
      musicFinished = true;
      stopDance();
      return;
    }
  }

  // Se la musica è finita, non eseguire altri passi
  if (musicFinished) return;

  switch (danceStep) {
    case STEP_NONE:
      break;

    case STEP_SHAKE_LEG:
      if (now >= danceStepStartTime) {
        Otto.shakeLeg(1, 2000, -1);
        danceStepStartTime = now + 2000;
        danceStep = STEP_MOONWALK_LEFT;
      }
      break;

   case STEP_MOONWALK_LEFT:
      if (now >= danceStepStartTime) {
        Otto.moonwalker(2, 1000, 25, 1); // LEFT
        danceStepStartTime = now + 1000;
        danceStep = STEP_MOONWALK_RIGHT;
      }
      break;

    case STEP_MOONWALK_RIGHT:
      if (now >= danceStepStartTime) {
        Otto.moonwalker(2, 1000, 25, -1); // RIGHT
        danceStepStartTime = now + 1000;
        danceStep = STEP_CRUSAITO;
      }
      break;

    case STEP_CRUSAITO:
      if (now >= danceStepStartTime) {
        Otto.crusaito(2, 1000, 20, 1);
        danceStepStartTime = now + 1000;
        danceStep = STEP_SECOND_SHAKE_LEG;
      }
      break;

    case STEP_SECOND_SHAKE_LEG:
      if (now >= danceStepStartTime) {
        Otto.shakeLeg(1, 1500, 1);
        danceStepStartTime = now + 1500;
        danceStep = STEP_SWING;
      }
      break;

    case STEP_SWING:
      if (now >= danceStepStartTime) {
        Otto.swing(2, 1000, 20);
        danceStepStartTime = now + 1000;
        danceStep = STEP_FINAL_WALK;
      }
      break;

    case STEP_FINAL_WALK:
      if (now >= danceStepStartTime) {
        Otto.moonwalker(3, 1000, 25, 1);
        danceStepStartTime = now + 1000;
        danceStep = STEP_FINISHED;
      }
      break;

    case STEP_FINISHED:
      if (now >= danceStepStartTime) {
        Otto.home();
        Serial.println(">> Danza Smooth Criminal terminata.");
        danceStep =  STEP_SHAKE_LEG;
      }
      break;
  }
}

void stopDance() {
  danceStep = STEP_NONE;
  Otto.home();
  if (myDFPlayer.available()) {
    myDFPlayer.stop();
  }
  musicStarted = false;
  musicFinished = true;
  Serial.println(">> Uscita manuale dalla danza.");
}