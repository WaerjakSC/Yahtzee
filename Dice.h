//
// Created by Waerjak on 27/10/2017.
//

#ifndef YAHTZY_DICE_H
#define YAHTZY_DICE_H

class PlayInfo;
class Dice
{
private:
	int m_dValue[5]{ 0, 0, 0, 0, 0 }; // All dice are worth 0 until thrown
	bool m_reRoll[5]{ false, false, false, false, false }; // false indicates not held for another throw
public:
	bool getHeld(int whichDie);

	void set_reRoll(int whichDie, bool hold);

	void rollDice(int whichDie, int newVal);

	void twoPairs(PlayInfo &player);

	void fullHouse(PlayInfo &player);

	void threeofaKind(PlayInfo &player);

	void fourofaKind(PlayInfo &player);

	void yahtzee(PlayInfo &player);

	void sequential(PlayInfo &player);

	void printValues();

	void checkUpper(int cat, PlayInfo &player);

	friend class PlayInfo;
	friend void throws(PlayInfo &player);
};


#endif //YAHTZY_DICE_H
