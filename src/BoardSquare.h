#ifndef BOARD_SQUARE_H
#define BOARD_SQUARE_H

#include <map>
#include <istream>
#include <string>

class MonopolyGame;
class Player;
class PluginBase;

class BoardSquare
{
public:
	BoardSquare();
	BoardSquare( std::istream & dataStream );
	~BoardSquare();

	void Init( std::istream & dataStream );
	void OnPlayerLand( MonopolyGame & game, Player & player );
	PluginBase * GetPlugin( const std::string & pluginName );
	const PluginBase * GetPlugin( const std::string & pluginName ) const;

	void PrintInfo() const;
	inline const std::string & GetName() const;

private:
	typedef std::map<std::string, PluginBase*> PluginMap;

	BoardSquare( const BoardSquare& );
	void CreatePlugin( const std::string &pluginName, std::istream & dataStream );

	PluginMap mPluginMap;
	std::string mName;
};

const std::string & BoardSquare::GetName() const
{
	return mName;
}

#endif // BOARD_SQUARE_H
