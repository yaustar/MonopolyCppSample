#ifndef PLUGIN_STATION_H
#define PLUGIN_STATION_H

#include <istream>
#include "PluginBase.h"

class PluginStation : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	enum ERentBrackets
	{
		RENT_ONE_STATION,
		RENT_TWO_STATIONS,
		RENT_THREE_STATIONS,
		RENT_FOUR_STATIONS,
		TOTAL_NUM_RENT_BRACKETS
	};

	PluginStation( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );

private:
	PluginStation();

	int mRentBracketValues[TOTAL_NUM_RENT_BRACKETS];
};

#endif // PLUGIN_STATION_H
