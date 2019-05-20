#include "PluginRentable.h"

#include <iostream>
#include "Utils.h"
#include "PluginOwnable.h"
#include "Player.h"
#include "BoardSquare.h"
#include "PluginBuildable.h"
#include "PropertySetManager.h"
#include "PluginSet.h"

BUILD_PLUGIN_META_DATA(PluginRentable, Rentable);

PluginRentable::PluginRentable( BoardSquare * pParentSquare, std::istream & dataStream ) :
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

					if( "RentSiteOnly" == line )
					{
						mRentBracketValues[RENT_SITE_ONLY] = rentBracketValue;
					}
					else if( "RentOneHouse" == line )
					{
						mRentBracketValues[RENT_ONE_HOUSE] = rentBracketValue;
					}
					else if( "RentTwoHouses" == line )
					{
						mRentBracketValues[RENT_TWO_HOUSES] = rentBracketValue;
					}
					else if( "RentThreeHouses" == line )
					{
						mRentBracketValues[RENT_THREE_HOUSES] = rentBracketValue;
					}
					else if( "RentFourHouses" == line )
					{
						mRentBracketValues[RENT_FOUR_HOUSES] = rentBracketValue;
					}
					else if( "RentHotel" == line )
					{
						mRentBracketValues[RENT_HOTEL] = rentBracketValue;
					}
				}
			}
		}
	}
}

void PluginRentable::OnPlayerLand( MonopolyGame & game, Player & player )
{
	(void)game;

	// Check if this square has an owner, if so, the player that landed
	//  pays the correct rent to them
	PluginOwnable * pOwnable = static_cast<PluginOwnable*>(mpParentSquare->GetPlugin(PluginOwnable::msPluginName) );
	if( pOwnable != NULL && pOwnable->GetOwner() != NULL && pOwnable->GetOwner() != &player )
	{
		ERentBrackets rentBracket = RENT_SITE_ONLY;

		// Check if there are any buildings
		PluginBuildable * pBuildable = static_cast<PluginBuildable*>(mpParentSquare->GetPlugin(PluginBuildable::msPluginName) );
		if( pBuildable != NULL )
		{
			int numberOfHousesOnProperty = pBuildable->GetNumberOfHouses();
			if( numberOfHousesOnProperty < TOTAL_NUM_RENT_BRACKETS )
			{
				pBuildable->PrintInfo();
				rentBracket = static_cast<ERentBrackets>(numberOfHousesOnProperty);
			}
		}

		int rentAmount = mRentBracketValues[rentBracket];

		// If the owner owns an entire set, then double the base rater
		if( RENT_SITE_ONLY == rentBracket )
		{
			PluginSet * pSet = static_cast<PluginSet*>(mpParentSquare->GetPlugin(PluginSet::msPluginName));
			if( pSet != NULL )
			{
				if( gPropertySetManager.DoesPlayerOwnEntireSet( *(pOwnable->GetOwner()), *pSet ) )
				{
					std::cout << pOwnable->GetOwner()->GetName() << " owns the entire set: " << pSet->GetSetId() << "\n";
					rentAmount *= 2;
				}
			}
		}

		std::cout << player.GetName() << " is paying " << rentAmount << " rent to "
			<< pOwnable->GetOwner()->GetName() << "\n";
		player.PayTo( *(pOwnable->GetOwner()), rentAmount );
	}
}
