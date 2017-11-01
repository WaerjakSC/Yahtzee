#include <iostream>
#include <random>
#include "input.h"
#include "Dice.h"
#include "PlayInfo.h"
#include <algorithm>

using namespace std;


void compareScores(PlayInfo &player1, PlayInfo &player2, PlayInfo &player3, PlayInfo &player4,
                   PlayInfo &player5);
void scoreCard(PlayInfo &player1, PlayInfo &player2, PlayInfo &player3, PlayInfo &player4,
               PlayInfo &player5);

// Using Mersenne Twister (sp?) random number generator, and uniform_int_distribution for the 1-6 die cast.
mt19937 mt((unsigned int) time(
		nullptr)); // Apparently these are okay to put as a global according to the internet, I dunno
uniform_int_distribution<> die_cast(1, 6);

int main()
{
	cout << "Welcome to Yahtzee!\nUp to 5 people can play this game.\n";
	cout
			<< "You have three throws of five dice per turn.\nYou can choose to freeze/unfreeze a die at any time by typing its position in the dice sequence."
			<< "A frozen (held) die will have the letter \"H\" next to it.\n"
			<< "You can select any category to put your points in, but make sure your dice results fit that category.\n";
	vector<string> players = names();
	if (players.size() < 5)
	{
		players.resize(5);
	}
	PlayInfo player1(players[0], 0);
	PlayInfo player2(players[1], 0);
	PlayInfo player3(players[2], 0);
	PlayInfo player4(players[3], 0);
	PlayInfo player5(players[4], 0);
	bool play{ true };
	do
	{
		cout << "                         Player 1: " << player1.getName() << "  Player 2: " << player2.getName()
		     << " Player 3: "
		     << player3.getName() << " Player 4: " << player4.getName() << " Player 5: " << player5.getName() << " \n";
		scoreCard(player1, player2, player3, player4, player5);
		int rounds{ 1 };
		int totalRounds{ 0 };
		bool gameOver{ false };
		while (!gameOver)
		{
			switch (rounds)
			{
				case 1:
					throws(player1);
					totalRounds++;
					if (!player2.getName().empty())
					{
						rounds++;
					}
					if (!player1.getBonus() && totalRounds >= 6)
					{
						player1.check_upperFull();
					}
					if (totalRounds == 14 && player2.getName().empty())
					{
						gameOver = true;
					}
					break;
				case 2:
					throws(player2);
					totalRounds++;
					if (!player3.getName().empty())
					{
						rounds++;
					} else
					{
						rounds = 1;
					}
					if (!player2.getBonus() && totalRounds >= 6)
					{
						player2.check_upperFull();
					}
					if (totalRounds == 28)
					{
						gameOver = true;
					}
					break;
				case 3:
					throws(player3);
					totalRounds++;
					if (!player4.getName().empty())
					{
						rounds++;
					} else
					{ rounds = 1; }
					if (!player3.getBonus() && totalRounds >= 6)
					{
						player3.check_upperFull();
					}
					if (totalRounds == 42)
					{
						gameOver = true;
					}
					break;
				case 4:
					throws(player4);
					totalRounds++;
					if (!player5.getName().empty())
					{
						rounds++;
					} else
					{ rounds = 1; }
					if (!player4.getBonus() && totalRounds >= 6)
					{
						player4.check_upperFull();
					}
					if (totalRounds == 56)
					{
						gameOver = true;
					}
					break;
				case 5:
					throws(player5);
					rounds = 1;
					totalRounds++;
					if (!player5.getBonus() && totalRounds >= 6)
					{
						player5.check_upperFull();
					}
					if (totalRounds == 70)
					{
						gameOver = true;
					}
					break;
				default:
					break;
			}
			scoreCard(player1, player2, player3, player4, player5);
		}
		compareScores(player1, player2, player3, player4, player5);
		play = playAgain();
	} while (play);
	return 0;
}

/**
 * Scorecard function is just for displaying the scorecard each round. Got kinda lazy with the formatting so
 * as points get filled in they will displace some of the dividers.
 * @param player1
 * @param player2
 * @param player3
 * @param player4
 * @param player5
 * All params are just used to tell the function who's who.
 */
void scoreCard(PlayInfo &player1, PlayInfo &player2, PlayInfo &player3, PlayInfo &player4,
               PlayInfo &player5) // Just need to make the dice ascii, compare players to see who won, and some others
{
	cout << "                                                                                       \n";
	cout << "                       |  Player 1  |  Player 2  |  Player 3  |  Player 4  |  Player 5  | \n";
	cout << " _______________________________________________________________________________________\n";
	cout << "|  1. Ones             |      " << player1.getUpper(0) << "     |      " << player2.getUpper(0)
	     << "     |      " << player3.getUpper(0) << "     |      " << player4.getUpper(0) << "     |      "
	     << player5.getUpper(0) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  2. Twos             |      " << player1.getUpper(1) << "     |      " << player2.getUpper(1)
	     << "     |      " << player3.getUpper(1) << "     |      " << player4.getUpper(1) << "     |      "
	     << player5.getUpper(1) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  3. Threes           |      " << player1.getUpper(2) << "     |      " << player2.getUpper(2)
	     << "     |      " << player3.getUpper(2) << "     |      " << player4.getUpper(2) << "     |      "
	     << player5.getUpper(2) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  4. Fours            |      " << player1.getUpper(3) << "     |      " << player2.getUpper(3)
	     << "     |      " << player3.getUpper(3) << "     |      " << player4.getUpper(3) << "     |      "
	     << player5.getUpper(3) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  5. Fives            |      " << player1.getUpper(4) << "     |      " << player2.getUpper(4)
	     << "     |      " << player3.getUpper(4) << "     |      " << player4.getUpper(4) << "     |      "
	     << player5.getUpper(4) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  6. Sixes            |      " << player1.getUpper(5) << "     |      " << player2.getUpper(5)
	     << "     |      " << player3.getUpper(5) << "     |      " << player4.getUpper(5) << "     |      "
	     << player5.getUpper(5) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|   Upper Score        |      " << player1.calculateUpper() << "     |      " << player2.calculateUpper()
	     << "     |      " << player3.calculateUpper() << "     |      " << player4.calculateUpper()
	     << "     |      " << player5.calculateUpper() << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  7. Two Pairs        |      " << player1.getLower(0) << "     |      " << player2.getLower(0)
	     << "     |      " << player3.getLower(0) << "     |      " << player4.getLower(0) << "     |      "
	     << player5.getLower(0) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  8. Three of a Kind  |      " << player1.getLower(1) << "     |      " << player2.getLower(1)
	     << "     |      " << player3.getLower(1) << "     |      " << player4.getLower(1) << "     |      "
	     << player5.getLower(1) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  9. Four of a Kind   |      " << player1.getLower(2) << "     |      " << player2.getLower(2)
	     << "     |      " << player3.getLower(2) << "     |      " << player4.getLower(2) << "     |      "
	     << player5.getLower(2) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  10. Full House      |      " << player1.getLower(3) << "     |      " << player2.getLower(3)
	     << "     |      " << player3.getLower(3) << "     |      " << player4.getLower(3) << "     |      "
	     << player5.getLower(3) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  11. Small Straight  |      " << player1.getLower(4) << "     |      " << player2.getLower(4)
	     << "     |      " << player3.getLower(4) << "     |      " << player4.getLower(4) << "     |      "
	     << player5.getLower(4) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|  12. Large Straight  |      " << player1.getLower(5) << "     |      " << player2.getLower(5)
	     << "     |      " << player3.getLower(5) << "     |      " << player4.getLower(5) << "     |      "
	     << player5.getLower(5) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "| 13.  Yahtzee         |      " << player1.getLower(6) << "     |      " << player2.getLower(6)
	     << "     |      " << player3.getLower(6) << "     |      " << player4.getLower(6) << "     |      "
	     << player5.getLower(6) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "| 14.  Chance          |      " << player1.getLower(7) << "     |      " << player2.getLower(7)
	     << "     |      " << player3.getLower(7) << "     |      " << player4.getLower(7) << "     |      "
	     << player5.getLower(7) << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
	cout << "|     Total Score      |      " << player1.getPoints() << "     |      " << player2.getPoints()
	     << "     |      " << player3.getPoints() << "     |      " << player4.getPoints() << "     |      "
	     << player5.getPoints() << "     |\n";
	cout << "|______________________|____________|____________|____________|____________|____________|\n";
}

/**
 * Throws function handles the actual game, by calling the Dice class to roll the dice and calculate the values.
 * @param player Used to check categories and increment points for each player.
 */
void throws(PlayInfo &player)
{
	Dice die;
	int turnCount{ 0 };
	bool checkEarly{ false };
	while (turnCount <= 3)
	{
		turnCount++;
		if (turnCount < 3 && !checkEarly)
		{
			// Rolls the dice that the player isn't keeping.
			for (int i = 0; i < 5; i++)
			{
				if (!die.getHeld(i))
				{
					die.rollDice(i, die_cast(mt));
				}
			}
			// Prints the value of each die.
			die.printValues();
			vector<int> v = freezeDie();
			for (int item : v)
			{
				if (item == 0)
				{
					checkEarly = true;
					turnCount = 2;
					break;
				}
				die.set_reRoll(item - 1, !die.getHeld(item - 1));
			}
		} else if (turnCount == 3)
		{
			if (!checkEarly)
			{
				for (int i = 0; i < 5; i++)
				{
					if (!die.getHeld(i))
					{
						die.rollDice(i, die_cast(mt));
					}
				}
				die.printValues();
			}
			cout << "\nWhich category would you like to use? (1-14) \n"; // Ask player which category they want to use
			bool correct{ false };
			while (!correct)
			{
				int select = iInput();
				if (select <= 6 && !player.getScored(select))
				{
					correct = true;
					die.checkUpper(select, player);
				} else if (select > 6 && select <= 9 && !player.getScored(select))
				{
					correct = true;
					switch (select)
					{
						case 7:
							die.twoPairs(player);
							break;
						case 8:
							die.threeofaKind(player);
							break;
						case 9:
							die.fourofaKind(player);
							break;
						default:
							break;
					}
				} else
				{
					cout << "You already scored that category. ";
					continue;
				}
				if (select > 9 && !player.getScored(select))
				{
					switch (select)
					{
						case 10:
							die.fullHouse(player); // Full House (three + two)
							break;
						case 11:
							die.sequential(player);
							break;                  // Small Straight (Four sequential dice)
						case 12:
							die.sequential(player); // Large Straight (Five sequential dice)
							break;
						case 13:                    // Yahtzee
							die.yahtzee(player);
							break;
						case 14:                    // Chance
							die.checkUpper(select, player);
							break;
						default:
							break;
					}
					correct = true;
				} else if (select > 9 && player.getScored(select))
				{
					cout << "You already scored that category. ";
					continue;
				}
			}

		}
	}
}

void compareScores(PlayInfo &player1, PlayInfo &player2, PlayInfo &player3, PlayInfo &player4,
                   PlayInfo &player5)
{
	int topScore = std::max({player1.getPoints(),player2.getPoints(),player3.getPoints(),player4.getPoints(),player5.getPoints()});
	if (player1.getPoints() == topScore)
	{
		cout << player1.getName() << " wins with " << player1.getPoints() << "!";
	}
	if (player2.getPoints() == topScore)
	{
		cout << player2.getName() << " wins with " << player2.getPoints() << "!";
	}
	if (player3.getPoints() == topScore)
	{
		cout << player3.getName() << " wins with " << player3.getPoints() << "!";
	}
	if (player4.getPoints() == topScore)
	{
		cout << player4.getName() << " wins with " << player4.getPoints() << "!";
	}
	if (player5.getPoints() == topScore)
	{
		cout << player5.getName() << " wins with " << player5.getPoints() << "!";
	}
}