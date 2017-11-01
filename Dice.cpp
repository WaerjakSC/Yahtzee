//
// Created by Waerjak on 27/10/2017.
//

#include <string>
#include <iostream>
#include <vector>
#include "Dice.h"
#include "PlayInfo.h"
#include <algorithm>


using namespace std;

/**
 * Check if the die is held and rerolls the value if not.
 * @param whichDie The die used.
 * @return
 */
bool Dice::getHeld(int whichDie) { return m_reRoll[whichDie]; }

/**
 * Sets a die to be held for next throw.
 * @param whichDie Same in every Dice function
 * @param hold True or False depending on if die is held or not.
 */
void Dice::set_reRoll(int whichDie, bool hold) { m_reRoll[whichDie] = hold; }

/**
 * Function to roll all 5 dice.
 * @param whichDie
 * @param newVal Uses mt19937 to choose a new value
 */
void Dice::rollDice(int whichDie, int newVal) { m_dValue[whichDie] = newVal; }

/**
 * Checks for two pairs if that category is selected by the player.
 * @param player
 */
void Dice::twoPairs(PlayInfo &player)
{
	int total{ 0 };
	int newArray[5]{};
	for (int i = 0; i < 5; i++)
	{
		for (int j : m_dValue)
		{
			if (m_dValue[i] == j)
			{
				newArray[i] = m_dValue[i];
			}
		}

	}
	sort(newArray, newArray + 5);
	if (newArray[4] != 0)
	{
		newArray[3] = 0;
		for (int i : newArray)
		{
			total += i;
		}
		player.incrementPoints(total, 7);
	}
}

/**
 * Checks for Full House if that category is selected by the player.
 * @param player
 */
void Dice::fullHouse(PlayInfo &player)
{
	int total{ 0 };
	int newArray[5]{};
	for (int i = 0; i < 5; i++)
	{
		for (int j : m_dValue)
		{
			if (m_dValue[i] == j)
			{
				newArray[i] = m_dValue[i];
			}
		}

	}
	sort(newArray, newArray + 5);
	if (newArray[4] != 0)
	{
		if (newArray[1] == newArray[2] || newArray[4] == newArray[3])
		{
			player.incrementPoints(total, 10);
		}
	}
}

/**
 * Checks for Three of a Kind if that category is selected by the player.
 * @param player
 */
void Dice::threeofaKind(PlayInfo &player)
{
	int numbers[6]{ 0 };
	for (int i : m_dValue)
	{
		switch (i)
		{
			case 1:
				numbers[0]++;
				break;
			case 2:
				numbers[1] += 2;
				break;
			case 3:
				numbers[2] += 3;
				break;
			case 4:
				numbers[3] += 4;
				break;
			case 5:
				numbers[4] += 5;
				break;
			case 6:
				numbers[5] += 6;
				break;
			default:
				break;
		}
	}
	if (numbers[0] >= 3)
	{
		player.incrementPoints(numbers[0], 8);
	}
	if (numbers[1] >= 6)
	{
		player.incrementPoints(numbers[1], 8);
	}
	if (numbers[2] >= 9)
	{
		player.incrementPoints(numbers[2], 8);
	}
	if (numbers[3] >= 12)
	{
		player.incrementPoints(numbers[3], 8);
	}
	if (numbers[4] >= 15)
	{
		player.incrementPoints(numbers[4], 8);
	}
	if (numbers[5] >= 18)
	{
		player.incrementPoints(numbers[5], 8);
	}
}

/**
 * Checks for Four of a Kind if that category is selected by the player.
 * @param player
 */
void Dice::fourofaKind(PlayInfo &player)
{
	int numbers[6]{ 0 };
	for (int i : m_dValue)
	{
		switch (i)
		{
			case 1:
				numbers[0]++;
				break;
			case 2:
				numbers[1] += 2;
				break;
			case 3:
				numbers[2] += 3;
				break;
			case 4:
				numbers[3] += 4;
				break;
			case 5:
				numbers[4] += 5;
				break;
			case 6:
				numbers[5] += 6;
				break;
			default:
				break;
		}
	}
	if (numbers[0] >= 4)
	{
		player.incrementPoints(numbers[0], 9);
	}
	if (numbers[1] >= 8)
	{
		player.incrementPoints(numbers[1], 9);
	}
	if (numbers[2] >= 12)
	{
		player.incrementPoints(numbers[2], 9);
	}
	if (numbers[3] >= 16)
	{
		player.incrementPoints(numbers[3], 9);
	}
	if (numbers[4] >= 20)
	{
		player.incrementPoints(numbers[4], 9);
	}
	if (numbers[5] >= 24)
	{
		player.incrementPoints(numbers[5], 9);
	}
}

/**
 * Checks for Yahtzee if that category is selected by the player.
 * @param player
 */
void Dice::yahtzee(PlayInfo &player)
{
	int numbers[6]{ 0 };
	for (int i : m_dValue)
	{
		switch (i)
		{
			case 1:
				numbers[0]++;
				break;
			case 2:
				numbers[1] += 2;
				break;
			case 3:
				numbers[2] += 3;
				break;
			case 4:
				numbers[3] += 4;
				break;
			case 5:
				numbers[4] += 5;
				break;
			case 6:
				numbers[5] += 6;
				break;
			default:
				break;
		}
	}
	if (numbers[0] == 5)
	{
		player.incrementPoints(numbers[0], 13);
	}
	if (numbers[1] == 10)
	{
		player.incrementPoints(numbers[1], 13);
	}
	if (numbers[2] == 15)
	{
		player.incrementPoints(numbers[2], 13);
	}
	if (numbers[3] == 20)
	{
		player.incrementPoints(numbers[3], 13);
	}
	if (numbers[4] == 25)
	{
		player.incrementPoints(numbers[4], 13);
	}
	if (numbers[5] == 30)
	{
		player.incrementPoints(numbers[5], 13);
	}
}

/**
 * Checks for Small/Large Straight if either category is selected by the player.
 * @param player
 */
void Dice::sequential(PlayInfo &player)
{
	vector<int> container;
	for (auto i : m_dValue)
	{
		container.push_back(i);
	}
	sort(container.begin(), container.end());
	int add{ 0 };
	for (int i = 0; i < container.size(); i++)
	{
		if (container[i] == container[i + 1] + 1)
		{
			add++;
		}
	}
	if (add == 4)
	{
		player.incrementPoints(0, 11);
	} else if (add == 5)
	{
		player.incrementPoints(0, 12);
	}
}

/**
 * Prints the dice to terminal.
 */
void Dice::printValues()
{
	for (int i = 0; i < 5; i++)
	{
		if (m_reRoll[i])
		{
			cout << m_dValue[i] << "H "; // Could this link to ASCII dice?
		} else
		{
			cout << m_dValue[i] << " ";
		}
	}
}

/**
 * Checks for number of dice according to category and increments to m_points for the player.
 * @param cat
 * @param player
 */
void Dice::checkUpper(int cat, PlayInfo &player)
{
	int total{ 0 };
	switch (cat)
	{
		case 1:
			for (auto i:m_dValue)
			{
				if (i == 1)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 2:
			for (auto i:m_dValue)
			{
				if (i == 2)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 3:
			for (auto i:m_dValue)
			{
				if (i == 3)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 4:
			for (auto i:m_dValue)
			{
				if (i == 4)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 5:
			for (auto i:m_dValue)
			{
				if (i == 5)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 6:
			for (auto i:m_dValue)
			{
				if (i == 6)
				{
					total += i;
				}
			}
			player.incrementPoints(total, cat);
			break;
		case 14:
			for (auto i:m_dValue)
			{
				total += i;
			}
			player.incrementPoints(total, cat);
		default:
			break;
	}

}
