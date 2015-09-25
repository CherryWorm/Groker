#include "grokerWrapper.h"

// C version:

int calc (Player *me, Player *enemy)
{
	return 5;
}

GROKER_MAIN(calc)

// C++ version:

/*
class Ai : public GrokerAi
{
public:
	explicit Ai (Wrapper *w) : GrokerAi(w) {}
	
	int calc (Player *me, Player *enemy)
	{
		return 5;
	}
};

GROKER_MAIN(Ai)
*/
