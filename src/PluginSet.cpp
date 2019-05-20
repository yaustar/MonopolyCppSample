#include "PluginSet.h"

#include <iostream>
#include "Utils.h"
#include "PropertySetManager.h"

BUILD_PLUGIN_META_DATA(PluginSet, Set);

PluginSet::PluginSet( BoardSquare * pParentSquare, std::istream & dataStream ) :
	PluginBase(pParentSquare),
	mSetId(0)
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
					int setId = 0;
					ReadKeyValueAsInt( dataStream, setId );
					if( "SetId" == line )
					{
						mSetId = setId;
					}
				}

			}
		}
	}

	gPropertySetManager.AddPropertyToSet( this );
}

PluginSet::~PluginSet()
{
	gPropertySetManager.RemovePropertyFromSet( this );
}

void PluginSet::PrintInfo() const
{
	std::cout << "Part of set " << mSetId << "\n";
}
