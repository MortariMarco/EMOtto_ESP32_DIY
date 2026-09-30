#ifndef BLUETOOTH_COMMANDS_H
#define BLUETOOTH_COMMANDS_H

#include "EMOtto.h"
#include <BluetoothSerial.h>
#include "expressions.h"  // DEVE venire prima di usarlo
#include "modes.h"
#include "sleep.h"
#include "draw_utils.h"

extern void updateWalking();
extern bool walkingForward;
extern bool walkingBackward;
extern bool turningLeft;
extern bool turningRight;

// Enum già definiti nel main
enum ExpressionType;
 enum ModeType;

// Dichiarazione funzione
void handleBluetoothCommands(BluetoothSerial &SerialBT, ExpressionType &expression, ModeType &currentMode, unsigned long &lastActivityTime);

#endif
