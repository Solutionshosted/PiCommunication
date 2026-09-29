# PiCommunication

Eigene Arduino-Bibliothek für die UART-Nachrichten zur Raspberry-Pi-Bridge.
Sie liegt direkt im Sketch und benötigt keine zusätzliche Installation.

```cpp
#include "src/PiCommunication/src/PiCommunication.h"

PiCommunication piCommunication(Serial);

void setup() {
  Serial.begin(115200);
  piCommunication.sendReset();
}
```

Das Paket verwendet eine Arduino-`Print`-Ausgabe. Die Anwendung initialisiert
den seriellen Port und entscheidet, wann ein Ereignis gesendet wird.
Die Konstruktion erzeugt keine Ausgabe; es gibt keine regelmäßigen Meldungen.

| Aufruf | Nachricht |
|---|---|
| `sendReset()` | `<STATUS\|EVENT=RESET>` |
| `sendGameStart()` | `<STATUS\|EVENT=GAME_START>` |
| `sendEvaluation(PiCommunication::RED)` | `<EVALUATION\|AMPEL=red\|SOLVED=0>` |
| `sendEvaluation(PiCommunication::YELLOW)` | `<EVALUATION\|AMPEL=yellow\|SOLVED=0>` |
| `sendEvaluation(PiCommunication::GREEN)` | `<EVALUATION\|AMPEL=green\|SOLVED=1>` |
| `sendEvaluation(PiCommunication::NONE)` | Keine Ausgabe. |

Jede Nachricht endet wie bisher mit `\r\n`. Der Lösungsstatus wird aus der
Farbe abgeleitet. Im Spiel wird `sendEvaluation()` ausschließlich nach der
Auswahl von „BEWERTEN“ aufgerufen. Ein erneutes ausdrückliches Bewerten erzeugt
wieder ein UART-Ereignis; unveränderte MQTT-Werte filtert weiterhin die Go-Bridge.

Das Paket berechnet keine Bewertung und enthält weder MQTT-Verbindung noch
Diagnoseausgaben. Die Go-Bridge und ihr Nachrichtenformat bleiben unverändert.

Tests: [PIN- und Kommunikationstests](../../../tests/auth_communication/README.md).

Zum Wiederverwenden den gesamten Ordner `PiCommunication` in den Arduino-
Bibliotheksordner kopieren und `#include <PiCommunication.h>` verwenden.
