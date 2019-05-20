#include "PluginStation.h"

#include <iostream>
#include "Utils.h"
#include "PluginOwnable.h"
#include "Player.h"
#include "BoardSquare.h"
#include "PropertySetManager.h"
#include "PluginSet.h"

BUILD_PLUGIN_META_DATA(PluginStation, Station);

PluginStation::PluginStation( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare)
{
	for( int i = 0; i < TOTAL_NUM_RENT_BRACKETS; i+=1 )
	{
		mRentBracketValues[i] = 0;
	}

	std::string line;
	if( std::getline(dataStream, line) )
	{
		TrimLeadingWhiteSpace( line );
		if( "{" == line )
		{
			while( std::getline(dataStream, line) )
			{
				TrimLeadingWhiteSpace( line );
				if( "}" == line )
				{
					break;
				}
				else
				{
					int rentBracketValue = 0;
					ReadKeyValueAsInt( dataStream, rentBracketValue );

					if( "RentOneStation" == line )
					{
						mRentBracketValues[RENT_ONE_STATION] = rentBracketValue;
					}
					else if( "RentTwoStations" == line )
					{
						mRentBracketValues[RENT_TWO_STATIONS] = rentBracketValue;
					}
					else if( "RentThreeStations" == line )
					{
						mRentBracketValues[RENT_THREE_STATIONS] = rentBracketValue;
					}
					else if( "RentFourStations" == line )
					{
						mRentBracketValues[RENT_FOUR_STATIONS] = rentBracketValue;
					}
				}
			}
		}
	}
}

void PluginStation::OnPlayerLand( MonopolyGame & game, Player & player )
{
	(void)game;

	// Check if this square has an owner, if so, the player that landed
	//  pays the correct rent to them
	PluginOwnable * pOwnable = static_cast<PluginOwnable*>(mpParentSquare->GetPlugin(PluginOwnable::msPluginName) );
	if( pOwnable != NULL && pOwnable->GetOwner() != NULL && pOwnable->GetOwner() != &player )
	{
		ERentBrackets rentBracket = RENT_ONE_STATION;
		PluginSet * pSet = static_cast<PluginSet*>(mpParentSquare->GetPlugin(PluginSet::msPluginName));
		if( pSet != NULL )
		{
			int numberOwned = gPropertySetManager.GetNumberOfPlayerOwnedInSet( *(pOwnable->GetOwner()), *pSet );
			if( numberOwned < 0 )
			{
				numberOwned = 1;
			}
			else if( numberOwned >= TOTAL_NUM_RENT_BRACKETS )
			{
				numberOwned = TOTAL_NUM_RENT_BRACKETS - 1;
			}

			rentBracket = static_cast<ERentBrackets>(numberOwned-1);
			std::cout << pOwnable->GetOwner()->GetName() << " owns " << numberOwned << " Stations\n";
		}

		std::cout << player.GetName() << " is paying " << mRentBracketValues[rentBracket] << " rent to "
			<< pOwnable->GetOwner()->GetName() << "\n";
		player.PayTo( *(pOwnable->GetOwner()), mRentBracketValues[rentBracket] );
	}
}
