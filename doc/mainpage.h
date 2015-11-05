#ifndef MAINPAGE_H
#define MAINPAGE_H

/** @mainpage
 *
 * Groker ist eine KI-Aufgabe des 34. BwInf Runde 1. Dabei setzen die KIs immer gleichzeitig eine bestimmte Anzahl an
 * Chips. Wenn sich die Gebote der beiden KIs nicht mehr als 5 Chips unterscheiden, dürfen beide KIs ihren Einsatz
 * behalten. Ansonsten darf nur die KI mit dem geringeren Einsatz ihre Chips behalten. Eine KI gewinnt, wenn sie mehr
 * als 100 Chips mehr als der Gegner hat.
 * [Offizielle Aufgabenstellung](http://www.bundeswettbewerb-informatik.de/fileadmin/templates/bwinf/aufgaben/bwinf34/34_Aufgaben.pdf)
 *
 * Die Implementation einer KI ist in verschiedenen Programmiersprachen möglich. Generell sind die sogenannten
 * Simple Player, die eine minimale KI sind, gut dokumentiert. Hier sind ein paar nützliche Doku-Links und Hinweise für
 * verschiedenen Programmiersprachen (Go wird soweit ich weiß von doxygen nicht unterstützt):
 *
 * C++
 * ---
 *  - GrokerAi
 *  - _player
 *
 * Um eine KI in C++ zu schreiben, muss die Klasse GrokerAi erweitert werden und mithilfe des Makros
 *
 *     GROKER_MAIN(ClassName)
 *
 * eine main-Methode erstellt werden.
 *
 * C
 * ---
 * Um eine KI in C zu schreiben muss eine Funktion
 *
 *     int xxx (Player *me, Player *enemy, OutputBuffer *out)
 *
 * implementiert werden und mithilfe des Makros
 *
 *     GROKER_MAIN(xxx)
 *
 * eine main-Methode erstellt werden, die die KI startet.
 *
 * Java
 * ---
 *  - org.pixelgaffer.turnierserver.groker.ai.GrokerAi
 *
 * Um eine KI in Java zu schreiben, muss die Klasse org.pixelgaffer.turnierserver.groker.ai.GrokerAi erweitert
 * werden und in der main-Methode muss eine neue Instanz davon mit den Argumenten der main-Methode erstellt und die start()-Methode aufgerufen werden.
 *
 * Python
 * ---
 *  - ai.AI
 *  - ai.AI#einsatz
 *  - ai.AI#process
 *
 * Um eine KI in Python zu schreiben, muss die Klasse AI erstellt werden.
 * Diese muss die Methode einsatz-Methode implementiert werden, und sollte die process-Methode implementiert werden
 */

#endif
