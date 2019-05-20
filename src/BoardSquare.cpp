#include "BoardSquare.h"

#include <string>
#include <algorithm>
#include <iostream>

#include "MonopolyGame.h"
#include "Player.h"

#include "PluginRentable.h"
#include "PluginOwnable.h"
#include "PluginBuildable.h"
#include "PluginChance.h"
#include "PluginCommunityChest.h"
#include "PluginSet.h"
#include "PluginTax.h"
#include "PluginStation.h"

#include "Utils.h"

BoardSquare::BoardSquare()
{

}

BoardSquare::BoardSquare( std::istream & dataStream )
{
	Init(dataStream);
}

void BoardSquare::Init( std::istream & dataStream )
{
	std::string line;
	// Check for the opening brace
	if( std::getline(dataStream, line) )
	{
		TrimLeadingWhiteSpace( line );
		if( "{" == line )
		{
			// Parse the contents and check for the ending brace
			while( std::getline(dataStream, line) )
			{
				TrimLeadingWhiteSpace( line );
				if( "}" != line )
				{
					CreatePlugin( line, dataStream );
				}
				else
				{
					break;
				}
			}
		}
	}
}

BoardSquare::~BoardSquare()
{
	const PluginMap::iterator kPluginMapEnd = mPluginMap.end();
	for( PluginMap::iterator itr = mPluginMap.begin(); itr != kPluginMapEnd; ++itr )
	{
		if( itr->second != NULL )
		{
			delete itr->second;
		}
	}
}

void BoardSquare::OnPlayerLand( MonopolyGame & game, Player & player )
{
	std::cout << player.GetName() << " has landed on " << mName << "\n";
	const PluginMap::iterator kPluginMapEnd = mPluginMap.end();
	for( PluginMap::iterator itr = mPluginMap.begin(); itr != kPluginMapEnd; ++itr )
	{
		if( itr->second != NULL )
		{
			itr->second->OnPlayerLand( game, player );
		}
	}
}

PluginBase * BoardSquare::GetPlugin( const std::string & pluginName )
{
	PluginMap::iterator itr = mPluginMap.find( pluginName );
	if( itr != mPluginMap.end() )
	{
		return itr->second;
	}

	return NULL;
}

const PluginBase * BoardSquare::GetPlugin( const std::string & pluginName ) const
{
	PluginMap::const_iterator itr = mPluginMap.find( pluginName );
	if( itr != mPluginMap.end() )
	{
		return itr->second;
	}

	return NULL;
}

void BoardSquare::PrintInfo() const
{
	std::cout << "Square Name: " << mName << "\n";
	PluginMap::const_iterator kPluginMapEnd = mPluginMap.end();
	for( PluginMap::const_iterator itr = mPluginMap.begin(); itr != kPluginMapEnd; ++itr )
	{
		if( itr->second != NULL )
		{
			itr->second->PrintInfo();
		}
	}
	std::cout << "\n";
}

void BoardSquare::CreatePlugin( const std::string &pluginName, std::istream & dataStream )
{
	// Special marco to generate the code needed to build each plugin
#define PLUGIN_PARSE_ENTRY(_pluginClassType) \
	else if( _pluginClassType::msPluginName == pluginName ) \
	{ \
		PluginMap::iterator itr = mPluginMap.find( pluginName ); \
		if( itr == mPluginMap.end() ) \
		{ \
			_pluginClassType * pPlugin = new _pluginClassType( this, dataStream ); \
			mPluginMap.insert( make_pair( _pluginClassType::msPluginName, pPlugin ) ); \
		} \
	}

	// Create the plugins based on the name
	if( pluginName == "Name" )
	{
		ReadKeyValueAsString( dataStream, mName );
	}
	PLUGIN_PARSE_ENTRY( PluginRentable )
	PLUGIN_PARSE_ENTRY( PluginOwnable )
	PLUGIN_PARSE_ENTRY( PluginBuildable )
	PLUGIN_PARSE_ENTRY( PluginChance )
	PLUGIN_PARSE_ENTRY( PluginCommunityChest )
	PLUGIN_PARSE_ENTRY( PluginSet )
	PLUGIN_PARSE_ENTRY( PluginTax )
	PLUGIN_PARSE_ENTRY( PluginStation )
	// If there is no match, then just parse till we reach the last brace for
	//  this plugin
	else
	{
		int numberOfOpenScopes = 0;
		std::string line;
		while( std::getline(dataStream, line) )
		{
			TrimLeadingWhiteSpace( line );
			if( "{" == line )
			{
				numberOfOpenScopes += 1;
			}
			else if( "}" == line )
			{
				numberOfOpenScopes -= 1;
				if( numberOfOpenScopes <= 0 )
				{
					break;
				}
			}
		}
	}

#undef PLUGIN_PARSE_ENTRY
}
