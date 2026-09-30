#ifndef SerialCommand_h
#define SerialCommand_h

#include <Arduino.h>

#if !defined(ESP32)
#include <SoftwareSerial.h>
#endif

class SerialCommand {
  public:
    SerialCommand();
    void setSerial(Stream &port);
    void readSerial();
  private:
    Stream* serial;
};

#endif
