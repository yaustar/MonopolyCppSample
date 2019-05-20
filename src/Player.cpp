#include "Player.h"
#include <iostream>

Player::Player( const std::string &name, int startingMoney ) :
	mName( name ),
	mMoneyInBank( startingMoney )
{
}

bool Player::HasLost() const
{
	return (mMoneyInBank < 0);
}

void Player::PrintStatus() const
{
	std::cout << "Player name: " << mName << "\nMoney: " << mMoneyInBank << "\n";
}

Player::EMoneyComparisonResult Player::CompareMoneyTo( const Player &compareToPlayer ) const
{
	if( mMoneyInBank < compareToPlayer.mMoneyInBank )
	{
		return MONEY_COMPARISON_LESS;
	}
	else if( mMoneyInBank > compareToPlayer.mMoneyInBank )
	{
		return MONEY_COMPARISON_MORE;
	}

	return MONEY_COMPARISON_SAME;
}

void Player::PayTo( Player &recipentPlayer, int amount )
{
	mMoneyInBank -= amount;
	recipentPlayer.RecieveMoney( amount );
}

void Player::RecieveMoney( int amount )
{
	mMoneyInBank += amount;
}

void Player::PayMoney( int amount )
{
	mMoneyInBank -= amount;
}
