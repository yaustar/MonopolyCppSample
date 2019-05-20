#include "PropertySetManager.h"

#include <algorithm>
#include "PluginSet.h"
#include "Player.h"
#include "PluginOwnable.h"
#include "BoardSquare.h"

PropertySetManager gPropertySetManager;

PropertySetManager::PropertySetManager()
{
}

void PropertySetManager::AddPropertyToSet( PluginSet * pPluginSet )
{
	SetMap::iterator itr = mSetMap.find( pPluginSet->GetSetId() );
	if( itr != mSetMap.end() )
	{
		// If the set already exists, then just add to the end of the vector
		itr->second.push_back( pPluginSet );
	}
	else
	{
		// Else create a new entry in the map
		SetList newSetList;
		newSetList.push_back( pPluginSet );
		mSetMap.insert( make_pair( pPluginSet->GetSetId(), newSetList ) );
	}
}

void PropertySetManager::RemovePropertyFromSet( PluginSet * pPluginSet )
{
	SetMap::iterator mapItr = mSetMap.find( pPluginSet->GetSetId() );
	if( mapItr != mSetMap.end() )
	{
		SetList::iterator pluginSetItr = std::find( mapItr->second.begin(), mapItr->second.end(), pPluginSet );
		if( pluginSetItr != mapItr->second.end() )
		{
			SetList::iterator lastPluginSetItr = (mapItr->second.end())-1;
			std::swap( pluginSetItr, lastPluginSetItr );
			mapItr->second.pop_back();
		}
	}
}

bool PropertySetManager::DoesPlayerOwnEntireSet( const Player & player, const PluginSet &set ) const
{
	SetMap::const_iterator mapItr = mSetMap.find( set.GetSetId() );
	if( mapItr != mSetMap.end() )
	{
		if( !mapItr->second.empty() )
		{
			SetList::const_iterator kSetListEnd = mapItr->second.end();
			for( SetList::const_iterator pluginSetItr = mapItr->second.begin(); pluginSetItr != mapItr->second.end(); ++pluginSetItr )
			{
				const PluginOwnable * pOwnable = static_cast<const PluginOwnable*>((*pluginSetItr)->GetParentSquare()->GetPlugin(PluginOwnable::msPluginName) );
				if( pOwnable != NULL )
				{
					if( &player != pOwnable->GetOwner() )
					{
						return false;
					}
				}
			}
			
			return true;
		}
	}
	
	return false;
}

int PropertySetManager::GetNumberOfPlayerOwnedInSet( const Player & player, const PluginSet &set ) const
{
	int numberOwned = 0;
	SetMap::const_iterator mapItr = mSetMap.find( set.GetSetId() );
	if( mapItr != mSetMap.end() )
	{
		if( !mapItr->second.empty() )
		{
			SetList::const_iterator kSetListEnd = mapItr->second.end();
			for( SetList::const_iterator pluginSetItr = mapItr->second.begin(); pluginSetItr != mapItr->second.end(); ++pluginSetItr )
			{
				const PluginOwnable * pOwnable = static_cast<const PluginOwnable*>((*pluginSetItr)->GetParentSquare()->GetPlugin(PluginOwnable::msPluginName) );
				if( pOwnable != NULL )
				{
					if( &player == pOwnable->GetOwner() )
					{
						numberOwned += 1;
					}
				}
			}
		}
	}
	
	return numberOwned;
}
