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

struct _player
{
	int letzterEinsatz;
	int gewonneneChips;
};
typedef struct _player Player;
typedef struct _player Spieler; // für die die lieber deutsch proggen

Player* parsePlayer (char *s);

struct _result
{
	int chips;
	const char *output;
};
typedef struct _result Result;

#define GROKER_CALLBACK(name) Result* (* name ) (Player*, Player*)

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

class GrokerAi
{
public:
	explicit GrokerAi (Wrapper *wrapper)
		: w(wrapper)
	{
		if (!w)
			fprintf(stderr, "Warning: Wrapper is null!\n");
	}
	
	virtual int calc (Player *me, Player *enemy) = 0;
	
	const char* readOutput ()
	{
		const char *outbuf = _out.str().data();
		_out = std::stringstream();
		return outbuf;
	}
	
protected:
	void crash (const char *reason) { __c_crash(w, reason); }
	void surrender () { __c_surrender(w); }
	
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
