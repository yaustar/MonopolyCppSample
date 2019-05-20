#include "PluginCommunityChest.h"

#include <iostream>
#include "Utils.h"
#include "MonopolyGame.h"

BUILD_PLUGIN_META_DATA(PluginCommunityChest, CommunityChest);

const int PluginCommunityChest::SPACES_TO_MOVE_BACK_BY = 3;

PluginCommunityChest::PluginCommunityChest( BoardSquare * pParentSquare, std::istream & dataStream ) :
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

void PluginCommunityChest::OnPlayerLand( MonopolyGame & game, Player & player )
{
	std::cout << player.GetName() << " moves back three spaces\n";
	game.MovePlayerBack( player, SPACES_TO_MOVE_BACK_BY );
}
