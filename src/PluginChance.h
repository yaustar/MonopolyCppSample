#ifndef PLUGIN_CHANCE_H
#define PLUGIN_CHANCE_H

#include <istream>
#include "PluginBase.h"

class PluginChance : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	PluginChance( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );

private:
	PluginChance();

	static const int CHANCE_PENALTY_COST;
};

#endif // PLUGIN_CHANCE_H
