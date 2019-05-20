#include "MonopolyGame.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "Utils.h"
#include "BoardSquare.h"
#include "PluginOwnable.h"
#include "PluginBuildable.h"

const int MonopolyGame::NUMBER_OF_SIDES_PER_DIE = 6;
const int MonopolyGame::NUMBER_OF_DICE = 2;
const int MonopolyGame::AMOUNT_FOR_PASSING_GO = 200;

MonopolyGame::MonopolyGame( int numberOfPlayers, int startingMoneyPerPlayer, int numberOfTurnsCap ) :
	mkNumberOfTurnsCap( numberOfTurnsCap ),
	mDiceRoller( NUMBER_OF_SIDES_PER_DIE, NUMBER_OF_DICE ),
	mCurrentPlayerIndex( 0 ),
	mTotalNumberOfTurns( 0 )
{
	mPlayerList.reserve( numberOfPlayers );
	const std::string PLAYER_NAME_PREFIX( "Player " );
	for( int i = 0; i < numberOfPlayers; i+=1 )
	{
		std::stringstream playerName;
		playerName << PLAYER_NAME_PREFIX << i + 1;
		Player aPlayer( playerName.str(), startingMoneyPerPlayer );
		mPlayerList.push_back(aPlayer);

		mPlayerSquarePositionList.push_back(0);
	}

	LoadBoard();

	// Assign the properties to players
	const BoardSquareList::iterator kBoardSquareListEnd = mBoardSquareList.end();
	for( BoardSquareList::iterator itr = mBoardSquareList.begin(); itr != kBoardSquareListEnd; ++itr )
	{
		// Can it be owned?
		PluginOwnable *pOwnable = static_cast<PluginOwnable*>( (*itr)->GetPlugin(PluginOwnable::msPluginName) );
		if( pOwnable != NULL )
		{
			int playerOwnerIndex = rand() % static_cast<int> (mPlayerList.size());
			pOwnable->SetOwner( &mPlayerList[playerOwnerIndex] );
		}

		// Randomly build the number of houses per property
		PluginBuildable * pBuildable = static_cast<PluginBuildable*>( (*itr)->GetPlugin(PluginBuildable::msPluginName) );
		if( pBuildable != NULL )
		{
			int numberOfHouses = rand() % (PluginBuildable::MAX_NUMBER_OF_HOUSES + 1);
			pBuildable->SetNumberOfHouses( numberOfHouses );
		}

		(*itr)->PrintInfo();
	}

	std::cout << "\n";
}

MonopolyGame::~MonopolyGame()
{
	const BoardSquareList::iterator kBoardSquareListEnd = mBoardSquareList.end();
	for( BoardSquareList::iterator itr = mBoardSquareList.begin(); itr != kBoardSquareListEnd; ++itr )
	{
		delete *itr;
	}
}

bool MonopolyGame::HasEnded() const
{
	if( mTotalNumberOfTurns >= mkNumberOfTurnsCap )
	{
		return true;
	}

	int numberOfPlayersLeft = 0;
	PlayerList::const_iterator kPlayerListEnd = mPlayerList.end();
	for( PlayerList::const_iterator itr = mPlayerList.begin(); itr != kPlayerListEnd; ++itr )
	{
		if( !itr->HasLost() )
		{
			numberOfPlayersLeft += 1;
		}
	}

	return numberOfPlayersLeft <= 1;
}

void MonopolyGame::Update()
{
	std::cout << "== TURN " << mTotalNumberOfTurns + 1 << " ==\n";
	int diceValue = mDiceRoller.Roll();
	std::cout << "Rolls a " << diceValue;
	if( mDiceRoller.AreAllValuesTheSame() )
	{
		std::cout << " which was a double " << diceValue / 2 << "!";
	}
	std::cout << "\n\n";

	int newBoardPosition = mPlayerSquarePositionList[mCurrentPlayerIndex] + diceValue;
	// Wrap round the board if need be
	if( newBoardPosition >= static_cast<int>(mBoardSquareList.size()) )
	{
		std::cout << mPlayerList[mCurrentPlayerIndex].GetName() << " has passed Go! Collects " << AMOUNT_FOR_PASSING_GO << "\n";
		mPlayerList[mCurrentPlayerIndex].RecieveMoney( AMOUNT_FOR_PASSING_GO );
		newBoardPosition = newBoardPosition % static_cast<int>(mBoardSquareList.size());
	}

	mPlayerSquarePositionList[mCurrentPlayerIndex] = newBoardPosition;
	mBoardSquareList[newBoardPosition]->OnPlayerLand( *this, mPlayerList[mCurrentPlayerIndex] );

	// Print the statuses of all the players
	std::cout << "\n";
	const int kSizeOfPlayerList = static_cast<int>(mPlayerList.size());
	for( int i = 0; i < kSizeOfPlayerList; i+=1 )
	{
		mPlayerList[i].PrintStatus();
		std::cout << "\n";
	}

	mTotalNumberOfTurns += 1;
	MoveToNextPlayer();
}

void MonopolyGame::PrintGameStatus() const
{
	// Vector to hold the indexes of players that have the highest
	//  amount of cash to handle a possiblity of a draw
	std::vector<int> indexesOfWinningPlayersList;
	indexesOfWinningPlayersList.reserve( mPlayerList.size() );

	indexesOfWinningPlayersList.push_back(0);

	const int kSizeOfPlayerList = static_cast<int>(mPlayerList.size());
	for( int i = 1; i < kSizeOfPlayerList; i+=1  )
	{
		const Player &currentPlayer = mPlayerList[i];
		if( !indexesOfWinningPlayersList.empty() )
		{
			// Since all the players in the winning list have the same amount,
			//  just compare with the first one in the list
			Player::EMoneyComparisonResult playerMoneyComparsionResult = currentPlayer.CompareMoneyTo( mPlayerList[indexesOfWinningPlayersList[0]] );

			switch( playerMoneyComparsionResult )
			{
				case Player::MONEY_COMPARISON_SAME:
				{
					indexesOfWinningPlayersList.push_back(i);
				} break;

				case Player::MONEY_COMPARISON_MORE:
				{
					indexesOfWinningPlayersList.clear();
					indexesOfWinningPlayersList.push_back(i);
				} break;

				default: break;
			}
		}
	}

	std::cout << "== GAME STATUS ==\nThe following players have the most money:\n";
	const int kSizeOfWinningPlayersList = static_cast<int>(indexesOfWinningPlayersList.size());
	for( int i = 0; i < kSizeOfWinningPlayersList; i+=1 )
	{
		std::cout << "- " << mPlayerList[indexesOfWinningPlayersList[i]].GetName() << "\n";
	}
}

void MonopolyGame::MovePlayerBack( Player &player, int numberOfSpaces )
{
	// Find the player index
	for( int i = 0; i < static_cast<int>(mPlayerList.size()); i += 1 )
	{
		if( player.GetName() == mPlayerList[i].GetName() )
		{
			int newBoardPosition = mPlayerSquarePositionList[i] - numberOfSpaces;

			// Wrap round the board
			if( newBoardPosition < 0 )
			{
				newBoardPosition += static_cast<int>(mBoardSquareList.size());
			}

			mPlayerSquarePositionList[i] = newBoardPosition;
			mBoardSquareList[newBoardPosition]->OnPlayerLand( *this, player );
			break;
		}
	}
}

void MonopolyGame::MoveToNextPlayer()
{
	// Cycle to the next player in the list that hasn't lost yet
	int nextPlayerIndex = mCurrentPlayerIndex + 1;
	do
	{
		if( nextPlayerIndex >= static_cast<int>(mPlayerList.size()) )
		{
			nextPlayerIndex = 0;
		}

		if( !mPlayerList[nextPlayerIndex].HasLost() )
		{
			mCurrentPlayerIndex = nextPlayerIndex;
			return;
		}

		nextPlayerIndex += 1;
	} while( nextPlayerIndex != mCurrentPlayerIndex );
}

void MonopolyGame::LoadBoard()
{
	std::ifstream boardData( "BoardData.txt" );
	std::string line;
	while( std::getline(boardData, line) )
	{
		TrimLeadingWhiteSpace( line );
		if( "BoardSquare" == line )
		{
			BoardSquare * pNewSquare = new BoardSquare( boardData );
			mBoardSquareList.push_back( pNewSquare );
		}
	}
}
