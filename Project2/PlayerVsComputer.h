#include "Checkers.h"

class CheckersPvsC : public Checkers // Player checkers description
{
	Pos CurChecker;
	bool AlreadyAttack = false;
	int Winner = 0;
	int Player;

public:
	CheckersPvsC(int player) 
	{
		Player = player;
		Mirror = (player == 1);
	}
	bool Click(Pos Click);
	int GetPlayer() 
	{ 
		return Player; 
	}
	int GetWinner() 
	{ 
		return Winner; 
	}
};


