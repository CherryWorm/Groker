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

#define GROKER_CALLBACK(name) int (* name ) (Player*, Player*)

char* grokerMainLoop (Wrapper *w, GROKER_CALLBACK(callback));

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

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
	
protected:
	void crash (const char *reason) { __c_crash(w, reason); }
	void surrender () { __c_surrender(w); }
	
private:
	Wrapper *w;
};

#define GROKER_MAIN(clazzname) \
	clazzname *__ai = 0; \
	\
	int __callback (Player *me, Player *enemy) \
	{ \
		return __ai->calc(me, enemy); \
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
	int main (int argc, char **argv) \
	{ \
		Wrapper *w = globalInit(argc, argv); \
		grokerMainLoop(w, callback ); \
		globalCleanup(&w); \
		return 0; \
	}

#endif

#endif
