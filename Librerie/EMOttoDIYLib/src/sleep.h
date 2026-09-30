#ifndef SLEEP_H
#define SLEEP_H

#include <Arduino.h>
#include <EMOtto.h>
#include "expressions.h"  
#include "modes.h"
#include <DFRobotDFPlayerMini.h> 

// === Stati della modalità sleep ===
enum SleepState {
  SLEEP_START,
  SLEEP_BLINK,
  SLEEP_FACE,
  SLEEP_MOVE,
  SLEEP_BREATH_OUT,
  SLEEP_BREATH_IN,
  SLEEP_ZZZ,
  SLEEP_DONE
};

// === Variabili per gestione sleep ===
extern bool isSleeping;
extern bool pendingExpression;
extern unsigned long sleepTimer;
extern unsigned long lastActivityTime;
extern int zCount;
extern int breathRadius;
extern SleepState sleepState;
extern unsigned long sleepTimeout;
extern bool touch1WasPressed; 
extern bool touch2WasPressed; 
extern ExpressionType expression;
extern ExpressionType lastExpression;
extern DFRobotDFPlayerMini myDFPlayer;

// === Funzioni principali ===
void enterSleepMode();
void wakeUp();
void updateSleepingAnimation();

#endif // SLEEP_H
