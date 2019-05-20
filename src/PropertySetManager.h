#ifndef PROPERTY_SET_MANAGER_H
#define PROPERTY_SET_MANAGER_H

#include <vector>
#include <map>

class PluginSet;
class Player;

class PropertySetManager
{
public:
	PropertySetManager();
	
	void AddPropertyToSet( PluginSet * pPluginSet );
	void RemovePropertyFromSet( PluginSet * pPluginSet );
	
	bool DoesPlayerOwnEntireSet( const Player & player, const PluginSet &set ) const;
	int GetNumberOfPlayerOwnedInSet( const Player & player, const PluginSet &set ) const;
	
private:
	typedef std::vector<PluginSet*> SetList;
	typedef std::map<int, SetList> SetMap;
	
	SetMap mSetMap;
};

extern PropertySetManager gPropertySetManager;

#endif // PROPERTY_SET_MANAGER_H

