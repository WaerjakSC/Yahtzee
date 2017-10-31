//
// Created by Waerjak on 27/10/2017.
//

#ifndef YAHTZY_PLAYINFO_H
#define YAHTZY_PLAYINFO_H


class PlayInfo
{
private:
	int m_points{ 0 }; // Current player points
	std::string m_name{ "unnamed" }; // Player name
	int m_upperSheet[6]{ 0, 0, 0, 0, 0, 0 };
	int m_lowerSheet[8]{ 0, 0, 0, 0, 0, 0, 0, 0 };
	bool m_scored[14]{ false };
	bool m_bonus{false};
	/*
	 * [0] = Two Pairs
	 * [1] = Three Of A Kind
	 * [2] = Four Of A Kind
	 * [3] = Full House (25p)
	 * [4] = Small Straight (30p)
	 * [5] = Large Straight (40p)
	 * [6] = Yahtzee (50p)
	 * [7] = Chance
	 */
public:
	void check_upperFull ();

	int calculateUpper();
	PlayInfo(std::string name, int points);

	bool getBonus() {return m_bonus;}
	bool getScored(int cat);

	int getPoints();

	int getUpper(int cat);

	int getLower(int cat);

	void incrementPoints(int dieVal, int cat);

	std::string getName();

	friend void throws(PlayInfo &player);

};


#endif //YAHTZY_PLAYINFO_H
