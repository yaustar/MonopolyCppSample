#include "PluginChance.h"

#include <iostream>
#include "Utils.h"
#include "Player.h"

BUILD_PLUGIN_META_DATA(PluginChance, Chance);

const int PluginChance::CHANCE_PENALTY_COST = 50;

PluginChance::PluginChance( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare)
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

void PluginChance::OnPlayerLand( MonopolyGame & game, Player & player )
{
	(void)game;
	std::cout << player.GetName() << " must pay " << CHANCE_PENALTY_COST << "\n";
	player.PayMoney( CHANCE_PENALTY_COST );
}
