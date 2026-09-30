#include "SerialCommand.h"

SerialCommand::SerialCommand() {}

void SerialCommand::setSerial(Stream &port) {
  this->serial = &port;
}

void SerialCommand::readSerial() {
  if (serial && serial->available()) {
    char c = serial->read();
    // qui puoi aggiungere parsing comandi
  }
}
