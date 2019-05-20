#ifndef MONOPOLY_GAME_H
#define MONOPOLY_GAME_H

#include <vector>
#include "DiceRoller.h"
#include "Player.h"

class BoardSquare;

class MonopolyGame
{
public:
	MonopolyGame( int numberOfPlayers, int startingMoneyPerPlayer, int numberOfTurnsCap );
	~MonopolyGame();
	
	bool HasEnded() const;
	void Update();
	void PrintGameStatus() const;
	
	void MovePlayerBack( Player &player, int numberOfSpaces );
	
private:
	static const int NUMBER_OF_SIDES_PER_DIE;
	static const int NUMBER_OF_DICE;
	static const int AMOUNT_FOR_PASSING_GO;
	
	typedef std::vector<Player> PlayerList;
	typedef std::vector<BoardSquare *> BoardSquareList;
	typedef std::vector<int> PlayerSquarePositionList;
	
	MonopolyGame();
	
	const int mkNumberOfTurnsCap;
	
	PlayerList mPlayerList;
	PlayerSquarePositionList mPlayerSquarePositionList;
	BoardSquareList mBoardSquareList;
	DiceRoller mDiceRoller;
	
	int mCurrentPlayerIndex; 
	int mTotalNumberOfTurns;
	
	void MoveToNextPlayer();
	void LoadBoard();
};

#endif // MONOPOLY_GAME_H

