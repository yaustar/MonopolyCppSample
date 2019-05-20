#include "PluginBuildable.h"

#include <iostream>
#include "Utils.h"
#include "Player.h"

BUILD_PLUGIN_META_DATA(PluginBuildable, Buildable);

const int PluginBuildable::MAX_NUMBER_OF_HOUSES = 5;

PluginBuildable::PluginBuildable( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare),
	mNumberOfHouses(0)
{
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
			}
		}
	}
}

void PluginBuildable::OnPlayerLand( MonopolyGame & game, Player & player )
{
	(void)game;
	(void)player;
}

void PluginBuildable::PrintInfo() const
{
	if( mNumberOfHouses == MAX_NUMBER_OF_HOUSES )
	{
		std::cout << "Hotel built: 1\n";
	}
	else
	{
		std::cout << "Houses built: " << mNumberOfHouses << "\n";
	}
}
