#ifndef GROKER_WRAPPER_H
#define GROKER_WRAPPER_H

#include "wrapper.h"

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

#define GROKER_MAIN(callback) \
	Result* __callback (Player *me, Player *enemy) \
	{ \
		Result *r = malloc(sizeof(Result)); \
		r->chips = callback(me, enemy); \
		r->output = "-- not implemented --"; \
		return r; \
	} \
	\
	int main (int argc, char **argv) \
	{ \
		Wrapper *w = globalInit(argc, argv); \
		grokerMainLoop(w, callback ); \
		globalCleanup(&w); \
		return 0; \
	}

#endif

#endif
