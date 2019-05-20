#ifndef PLUGIN_TAX_H
#define PLUGIN_TAX_H

#include <istream>
#include "PluginBase.h"

class PluginTax : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	PluginTax( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );
	virtual void PrintInfo() const;

	inline int GetAmount() const;

private:
	PluginTax();

	int mAmount;
};

#endif // PLUGIN_TAX_H
