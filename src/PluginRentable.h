#ifndef PLUGIN_RENTABLE_H
#define PLUGIN_RENTABLE_H

#include <istream>
#include "PluginBase.h"

class PluginRentable : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	enum ERentBrackets
	{
		RENT_SITE_ONLY,
		RENT_ONE_HOUSE,
		RENT_TWO_HOUSES,
		RENT_THREE_HOUSES,
		RENT_FOUR_HOUSES,
		RENT_HOTEL,
		TOTAL_NUM_RENT_BRACKETS
	};

	PluginRentable( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );

private:
	PluginRentable();

	int mRentBracketValues[TOTAL_NUM_RENT_BRACKETS];
};

#endif // PLUGIN_RENTABLE_H
