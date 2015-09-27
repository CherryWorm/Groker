// C Version

#include "grokerWrapper.h"

/// Diese Methode wird jede Runde aufgerufen. Player ist ein struct mit den beiden int-Werten letzterEinsatz und
/// gewonneneChips. Der return-Wert ist der Einsatz der KI. Zur Ausgabe stehen die folgenden Funktionen zur
/// Verfügung:
///  - append (out, "text"): Gibt "text" aus
///  - appendi(out, 123456): Gibt 123465 aus
///  - appendd(out, 123.45): Gibt 123.45 aus
int calc (Player *me, Player *enemy, OutputBuffer *out)
{
	return 5;
}

GROKER_MAIN(calc)
