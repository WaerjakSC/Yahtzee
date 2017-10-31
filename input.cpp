//
// Created by Waerjak on 26/10/2017.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "input.h"

using namespace std;

/**
 * Function to return a vector that contains the number in sequence for each die the player would like to hold.
 * @return 1-5 selects a die, 0 skips right to category selection.
 */
vector<int> freezeDie()
{
	cout << "\nType (1-5) to freeze/unfreeze a die for next throw (0 to start selecting a category): ";
	string s;

	getline(cin, s);

	istringstream is(s);

	vector<int> v;
	int x;

	while (is >> x || !is.eof())
	{
		if (is.fail())
		{
			is.clear();
			is >> s;
			continue;
		}
		if (x >= 0 && x <= 5)
		{
			v.push_back(x);
		}
	}
	return v;
}

/** Collects each name and returns the vector by value to the main function.
 *
 * @return vector of words entered.
 */
vector<string> names()
{
	cout << "\nPlease enter your names separated by space: \n";
	string s;

	getline(cin, s);

	istringstream is(s);

	vector<string> v;
	string x;
	// feel like I'm making some redundancy mistakes here
	while (is >> x || !is.eof())
	{
		if (is.fail())
		{
			is.clear();
			is >> s;
			continue;
		}
		if (v.size() < 5)
		{
			v.push_back(x);
		}
	}
	return v;
}

/**
 * Simple check to ask if they want to play again.
 * @return
 */
bool playAgain()
{
	cout << "Do you want to play again? Y/N: ";
	char startGame{ 0 };
	while (startGame == 0)
	{
		cin >> startGame;
		cin.ignore(32767, '\n');
		if (startGame == 'n' || startGame == 'N')
		{
			return false;
		} else if (startGame != 'y' && startGame != 'Y')
		{
			cout << "Not valid input.\n";
			continue;
		} else
			return true;
	}

}
/**
 * int iInput()
 * Just a basic function to make sure the game doesn't crash if an invalid type is used.
 * @return - Function requires an integer before it allows the player to continue.
 */
int iInput ()
{
	while (true)
	{
		int bet{0};
		cin >> bet;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767,'\n');
			cout << "Please enter a valid number.\n";
		}
		else if (bet < 0)
		{
			cin.clear();
			cin.ignore(32767,'\n');
			cout << "Please enter a valid number.\n";
		}
		else if (bet > 14)
		{
			cin.clear();
			cin.ignore(32767,'\n');
			cout << "Please enter a valid number.\n";
		}
		else
		{
			cin.ignore(32767,'\n');
			return bet;
		}
	}
}