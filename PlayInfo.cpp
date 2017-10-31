//
// Created by Waerjak on 27/10/2017.
//
#include <iostream>
#include <vector>
#include "PlayInfo.h"

using namespace std;


PlayInfo::PlayInfo(string name, int points) : m_points{points}, m_name{move(name)} {
}

/**
 * Checks the array for the upper section score, and if it's all been scored it checks if the player has more than
 * 63 points. If so, awards an additional 34 points and sets m_bonus to true so it doesn't need to run the function again.
 */
void PlayInfo::check_upperFull() {
	if (!m_bonus) {
		// Bool vector for converting from the array in PlayInfo m_scored.
		std::vector<bool> checks;
		// Simple count to see if all 6 values in checks are true.
		int count{0};
		int pointCheck{0};
		// Push back the value of true/false into the vector checks.
		for (int i = 0; i < 6; i++) {
			checks.push_back(m_scored[i]);
		}
		for (auto i : checks) {
			if (i == true) {
				count++;
			}
		}
		if (count == 6) {
			for (auto points : m_upperSheet) {
				pointCheck += points;
			}
			if (pointCheck >= 63) {
				m_points += 34;
				m_bonus = true;
			}
		}
	}

}

/**
 * Calculates the upper score for use in function void Scorecard
 * @return returns the calculated score for the upper part of the board.
 */
int PlayInfo::calculateUpper() {
	int upperScore{0};
	for (int i = 0; i < 5; i++) {
		upperScore += m_upperSheet[i];
	}
	return upperScore;
}

/**
 * Used in function void Scorecard for each upper point value.
 * @param cat Category number. Same in every function that takes "int cat".
 * @return Returns point value.
 */
int PlayInfo::getUpper(int cat) { return m_upperSheet[cat]; }

/**
 * Same as above but for lower sheet.
 * @param cat
 * @return
 */
int PlayInfo::getLower(int cat) { return m_lowerSheet[cat]; }


/**
 * Checks if a category has already been scored.
 * @param cat
 * @return true/false
 */
bool PlayInfo::getScored(int cat) { return m_scored[cat - 1]; }

/**
 * Returns total score.
 * @return
 */
int PlayInfo::getPoints() { return m_points; }

/**
 * Increments points for m_points and the relevant scorecard part.
 * @param dieVal Value of the dice for use in the categories that give score according to thrown dice.
 * @param cat
 */
void PlayInfo::incrementPoints(int dieVal, int cat) {
	// Upper sheet
	if (cat <= 6) {
		m_upperSheet[cat - 1] = dieVal;
		m_points += dieVal;
	}
	// Two Pairs, Three of a Kind, Four of a Kind, Chance
	else if (cat > 6 && cat <= 9 || cat == 14) {
		m_lowerSheet[cat - 7] = dieVal;
		m_points += dieVal;
	}
	// Full House (25p)
	else if (cat == 10) {
		m_lowerSheet[cat - 7] += 25;
		m_points += 25;
	}
	// Small Straight (30p)
	else if (cat == 11) {
		m_lowerSheet[cat - 7] += 30;
		m_points += 30;
	}
	// Large Straight (40p)
	else if (cat == 12) {
		m_lowerSheet[cat - 7] += 40;
		m_points += 40;
	}
	// Yahtzee (50p)
	else if (cat == 13) {
		m_lowerSheet[cat - 7] += 50;
		m_points += 50;
	}
	m_scored[cat - 1] = true;
}

/**
 * Returns the name of the player.
 * @return
 */
string PlayInfo::getName() { return m_name; }