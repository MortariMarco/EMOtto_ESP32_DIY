#ifndef DANCE_H
#define DANCE_H

#include <Arduino.h>

enum DanceStep {
  STEP_NONE,
  STEP_PLAY_INTRO,
  STEP_SHAKE_LEG,
  STEP_MOONWALK_LEFT,
  STEP_MOONWALK_RIGHT,
  STEP_CRUSAITO,
  STEP_SECOND_SHAKE_LEG,
  STEP_SWING,
  STEP_FINAL_WALK,
  STEP_FINISHED
};

extern DanceStep danceStep;
extern unsigned long danceStepStartTime;

void startDance();
void updateDance();
void stopDance();
#endif
