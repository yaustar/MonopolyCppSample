#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
public:
	Player( const std::string &name, int startingMoney );

	enum EMoneyComparisonResult
	{
		MONEY_COMPARISON_SAME,
		MONEY_COMPARISON_MORE,
		MONEY_COMPARISON_LESS
	};

	bool HasLost() const;
	void PrintStatus() const;
	inline const std::string & GetName() const;
	EMoneyComparisonResult CompareMoneyTo( const Player &compareToPlayer ) const;

	void PayTo( Player &recipentPlayer, int amount );
	void RecieveMoney( int amount );
	void PayMoney( int amount );

private:
	Player();
	std::string mName;
	int mMoneyInBank;
};

const std::string & Player::GetName() const
{
	return mName;
}

#endif // PLAYER_H
