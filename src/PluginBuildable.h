#ifndef PLUGIN_BUILDABLE_H
#define PLUGIN_BUILDABLE_H

#include <istream>
#include "PluginBase.h"

class PluginBuildable : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	static const int MAX_NUMBER_OF_HOUSES;

	PluginBuildable( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void OnPlayerLand( MonopolyGame & game, Player & player );
	virtual void PrintInfo() const;

	inline void SetNumberOfHouses( int numberOfHouses );
	inline int GetNumberOfHouses() const;
	inline void AddHouses( int numberOfHouses );

private:
	PluginBuildable();

	int mNumberOfHouses;
};

void PluginBuildable::SetNumberOfHouses( int numberOfHouses )
{
	mNumberOfHouses = numberOfHouses;
	if( mNumberOfHouses < 0 )
	{
		mNumberOfHouses = 0;
	}
	else if( mNumberOfHouses > MAX_NUMBER_OF_HOUSES )
	{
		mNumberOfHouses = MAX_NUMBER_OF_HOUSES;
	}

}

int PluginBuildable::GetNumberOfHouses() const
{
	return mNumberOfHouses;
}

void PluginBuildable::AddHouses( int numberOfHouses )
{
	SetNumberOfHouses( mNumberOfHouses + numberOfHouses );
}

#endif // PLUGIN_BUILDABLE_H
