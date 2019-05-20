#include "DiceRoller.h"
#include <cstdlib>

DiceRoller::DiceRoller( int numberOfSidesPerDie, int numberOfDice ) :
	mkNumberOfSidePerDie( numberOfSidesPerDie ),
	mkNumberOfDice( numberOfDice ),
	mLastRollValue(0),
	mDiceValuesTheSame( false )
{
}

int DiceRoller::Roll()
{
	int totalDiceValue = 0;
	int lastDieValue = 0;
	
	mDiceValuesTheSame = true;
	for( int i = 0; i < mkNumberOfDice; i+=1 )
	{
		int randDieValue = (std::rand() % mkNumberOfSidePerDie) + 1;
		
		if( randDieValue != lastDieValue )
		{			
			// If this is the first die, then don't set the flag for 
			//  checking if all values on the dice are the same
			if( 0 != lastDieValue )
			{
				mDiceValuesTheSame = false;
			}
			
			lastDieValue = randDieValue;
		}
		
		totalDiceValue += randDieValue;
	}
	
	mLastRollValue = totalDiceValue;
	return totalDiceValue;
}

