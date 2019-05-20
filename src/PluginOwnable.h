#ifndef PLUGIN_OWNABLE_H
#define PLUGIN_OWNABLE_H

#include <istream>
#include "PluginBase.h"

class BoardSquare;
class Player;

class PluginOwnable : public PluginBase
{
public:
	DECLARE_PLUGIN_META_DATA;

	PluginOwnable( BoardSquare * pParentSquare, std::istream & dataStream );

	virtual void PrintInfo() const;

	inline Player* GetOwner();
	inline const Player* GetOwner() const;
	inline void SetOwner( Player *pNewOwner );

private:
	PluginOwnable();
	Player *mpOwner;
};

Player* PluginOwnable::GetOwner()
{
	return mpOwner;
}

const Player* PluginOwnable::GetOwner() const
{
	return mpOwner;
}

void PluginOwnable::SetOwner( Player *pNewOwner )
{
	mpOwner = pNewOwner;
}

#endif // PLUGIN_OWNABLE_H
