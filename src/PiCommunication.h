#pragma once

#include <Arduino.h>
#include <Print.h>

class PiCommunication {
 public:
  enum Color : uint8_t { NONE, RED, YELLOW, GREEN };

  explicit PiCommunication(Print &output);
  void sendReset();
  void sendGameStart();
  void sendEvaluation(Color color);

 private:
  void sendStatus(const __FlashStringHelper *event);
  Print &output_;
};
