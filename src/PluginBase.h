#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <string>

class MonopolyGame;
class Player;
class BoardSquare;

class PluginBase
{
public:	
	PluginBase( BoardSquare * pParentSquare );
	virtual ~PluginBase() {}
	
	virtual void OnPlayerLand( MonopolyGame & game, Player & player ) {(void)game; (void)player;}
	virtual void PrintInfo() const {}
	
	inline BoardSquare * GetParentSquare();
	inline const BoardSquare * GetParentSquare() const;
	
protected:
	PluginBase();
	BoardSquare * mpParentSquare;
};

BoardSquare * PluginBase::GetParentSquare()
{
	return mpParentSquare;
}

const BoardSquare * PluginBase::GetParentSquare() const
{
	return mpParentSquare;
}

// Helper marcos to construct the metadata
#define DECLARE_PLUGIN_META_DATA static const std::string msPluginName;
#define BUILD_PLUGIN_META_DATA(_className, _pluginName) const std::string _className::msPluginName = #_pluginName

#endif // PLUGIN_BASE_H

