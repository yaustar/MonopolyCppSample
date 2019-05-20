#ifndef PLUGIN_COMMUNITY_CHEST_H
#define PLUGIN_COMMUNITY_CHEST_H

#include <istream>
#include "PluginBase.h"

class PluginCommunityChest : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	PluginCommunityChest( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );

private:
	PluginCommunityChest();

	static const int SPACES_TO_MOVE_BACK_BY;
};

#endif // PLUGIN_COMMUNITY_CHEST_H
