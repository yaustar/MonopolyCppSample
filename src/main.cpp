#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MonopolyGame.h"

int main () 
{
	std::srand( static_cast<unsigned int>(time(0)) );
	
	static const int NUMBER_OF_PLAYERS = 2;
	static const int STARTING_CASH_PER_PLAYER = 1500;
	static const int NUMBER_OF_TURNS_CAP = 50;
	
    MonopolyGame monopolyGame( NUMBER_OF_PLAYERS, STARTING_CASH_PER_PLAYER, NUMBER_OF_TURNS_CAP );
	while( !monopolyGame.HasEnded() )
	{
		monopolyGame.Update();
	}
	
	monopolyGame.PrintGameStatus();
}
