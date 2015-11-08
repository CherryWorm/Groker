/*
 * grokerWrapper.h
 *
 * Copyright (C) 2015 Pixelgaffer
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or any later
 * version.
 *
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See version 2 and version 3 of the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GROKER_WRAPPER_H
#define GROKER_WRAPPER_H

#include "wrapper.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Diese Klasse speichert die für die KI sichtbaren Daten einer KI. Dies ist der Einsatz der KI der letzten Runde
 * sowie die Anzahl der von dieser KI gewonnenen Chips.
 */
struct _player
{
	/** Der Einsatz der KI in der letzten Runde. */
	int letzterEinsatz;
	/** Die Anzahl der Chips, die die KI gewonnen hat. */
	int gewonneneChips;
};
typedef struct _player Player;
typedef struct _player Spieler; // für die die lieber deutsch proggen

/**
 * Diese Methode parst den String `s` zu einem pointer auf eine `Player`-Struktur.
 */
Player* parsePlayer (char *s);

/**
 * Diese Klasse repräsentiert das Ergebnis einer Runde. Dabei wird die Anzahl der Chips, die die KI setzt, und die
 * Ausgabe der KI gespeichert.
 */
struct _result
{
	int chips;
	const char *output;
};
typedef struct _result Result;

#define GROKER_CALLBACK(name) Result* (* name ) (Player*, Player*)

/**
 * Dies ist die MainLoop von Grooker. Sie wartet auf Daten vom Server, leitet diese an die eigentliche KI weiter, und
 * sendet diese Daten zurück.
 */
char* grokerMainLoop (Wrapper *w, GROKER_CALLBACK(callback));

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <sstream>

extern "C"
{
	void __c_crash (Wrapper *w, const char *reason) { crash(w, reason); }
	void __c_surrender (Wrapper *w) { surrender(w); }
}

/**
 * Dies ist die Mutter-Klasse von jeder Groker-KI. Sie muss im Konstuktor genau ein Argument, `Wrapper*`,
 * entgegennehmen, und an diese Klasse weitergeben. Zudem muss die pure virtual Methode `calc` überschrieben
 * werden. Diese Methode wird jede Runde aufgerufen. Zudem enthält diese Klasse eine Methode names `out`, die
 * ein `std::stringstream` zurückgibt, an das die KI ihre Ausgabe schicken kann. <b>Alles, was die KI an
 * `std::cout` sendet, geht verloren!!!</b>. Der Name dieser Klasse gehört als Argument an das `GROKER_MAIN`
 * Makro.
 */
class GrokerAi
{
public:
	explicit GrokerAi (Wrapper *wrapper)
		: w(wrapper)
	{
		if (!w)
			fprintf(stderr, "Warning: Wrapper is null!\n");
	}
	
	/**
	 * Wird jede Runde aufgerufen. Gibt die Anzahl der Chips, die die KI einsetzt, zurück.
	 * @param me Die eigene KI.
	 * @param enemy Die gegnerische KI.
	 * @return Die Anzahl an Chips, die die KI setzen will.
	 */
	virtual int calc (Player *me, Player *enemy) = 0;
	
	/**
	 * Gibt den Inhalt des aktuellen Output Buffers zurück und leert diesen.
	 */
	const char* readOutput ()
	{
		const char *outbuf = _out.str().data();
		_out.str("");
		return outbuf;
	}
	
protected:
	/**
	 * Lässt die KI mit Angabe eines Grundes abstürtzen.
	 * @param reason Der Grund, aus dem die KI abstürtzt.
	 */
	void crash (const char *reason) { __c_crash(w, reason); }
	/**
	 * Lässt die KI ohne Angabe eines Grundes aufgeben.
	 */
	void surrender () { __c_surrender(w); }
	
	/**
	 * Gibt ein `std::stringstream` zurück, an das die KI ihre Ausgaben schicken kann.
	 */
	std::stringstream& out () { return _out; }
	
private:
	Wrapper *w;
	std::stringstream _out;
};

#define GROKER_MAIN(clazzname) \
	clazzname *__ai = 0; \
	\
	Result* __callback (Player *me, Player *enemy) \
	{ \
		Result *r = (Result*) malloc(sizeof(Result)); \
		r->chips = __ai->calc(me, enemy); \
		r->output = __ai->readOutput(); \
		return r; \
	} \
	\
	int main (int argc, char **argv) \
	{ \
		Wrapper *w = globalInit(argc, argv); \
		__ai = new clazzname (w); \
		grokerMainLoop(w, __callback); \
		globalCleanup(&w); \
		delete __ai; \
		return 0; \
	}

#else

#include "output.h"

#define GROKER_MAIN(callback) \
	Result* __callback (Player *me, Player *enemy) \
	{ \
		Result *r = malloc(sizeof(Result)); \
		OutputBuffer *out = createBuffer(); \
		r->chips = callback(me, enemy, out); \
		r->output = readBuffer(out, OB_RETURN_COPY); \
		destroyBuffer(out); \
		return r; \
	} \
	\
	int main (int argc, char **argv) \
	{ \
		Wrapper *w = globalInit(argc, argv); \
		grokerMainLoop(w, __callback); \
		globalCleanup(&w); \
		return 0; \
	}

#endif

#endif
