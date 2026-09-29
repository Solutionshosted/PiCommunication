#include "PiCommunication.h"

// PiCommunication()
// Stores the output used for bridge messages without sending anything during construction.
PiCommunication::PiCommunication(Print &output) : output_(output) {}

// sendStatus()
// Writes one status event using the existing Raspberry Pi bridge protocol.
void PiCommunication::sendStatus(const __FlashStringHelper *event) {
  output_.print(F("<STATUS|EVENT="));
  output_.print(event);
  output_.println(F(">"));
}

// sendReset()
// Reports a reset so the bridge waits for the next game's first evaluation.
void PiCommunication::sendReset() {
  sendStatus(F("RESET"));
}

// sendGameStart()
// Reports the start of a game without publishing an evaluation.
void PiCommunication::sendGameStart() {
  sendStatus(F("GAME_START"));
}

// sendEvaluation()
// Sends one explicit evaluation with a solved flag derived from its color; NONE sends nothing.
void PiCommunication::sendEvaluation(Color color) {
  if (color == NONE) return;
  output_.print(F("<EVALUATION|AMPEL="));
  if (color == GREEN) output_.print(F("green"));
  else if (color == YELLOW) output_.print(F("yellow"));
  else output_.print(F("red"));
  output_.print(F("|SOLVED="));
  output_.print(color == GREEN ? 1 : 0);
  output_.println(F(">"));
}
