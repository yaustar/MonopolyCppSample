#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

class DiceRoller
{
public:
	DiceRoller( int numberOfSidesPerDie, int numberOfDice );
	int Roll();
	inline bool AreAllValuesTheSame() const;
	
private:
	DiceRoller();
	const int mkNumberOfSidePerDie;
	const int mkNumberOfDice;
	int mLastRollValue;
	bool mDiceValuesTheSame;
};

inline bool DiceRoller::AreAllValuesTheSame() const
{
	return mDiceValuesTheSame;
}

#endif //DICE_ROLLER_H

