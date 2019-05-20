#include "PluginTax.h"

#include <iostream>
#include "Utils.h"
#include "Player.h"

BUILD_PLUGIN_META_DATA(PluginTax, Tax);

PluginTax::PluginTax( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare),
	mAmount(0)
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
				else
				{
					int amount = 0;
					ReadKeyValueAsInt( dataStream, amount );
					if( "Amount" == line )
					{
						mAmount = amount;
					}
				}

			}
		}
	}
}
void PluginTax::OnPlayerLand( MonopolyGame & game, Player & player )
{
	(void)game;

	std::cout << player.GetName() << " pays " << mAmount << "\n";
	player.PayMoney(mAmount);
}

void PluginTax::PrintInfo() const
{
	std::cout << "Tax Amount: " << mAmount << "\n";
}
