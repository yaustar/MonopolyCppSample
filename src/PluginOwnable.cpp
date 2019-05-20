#include "PluginOwnable.h"

#include <iostream>
#include "Utils.h"
#include "Player.h"

BUILD_PLUGIN_META_DATA(PluginOwnable, Ownable);

PluginOwnable::PluginOwnable( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare),
	mpOwner(NULL)
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

void PluginOwnable::PrintInfo() const
{
	if( mpOwner != NULL )
	{
		std::cout << "Owned by " << mpOwner->GetName() << "\n";
	}
}
