#pragma once

#include "Functions.h"

// Player class definition
class Player {
private:
	std::string name;
	int balance;

public:
	// Constructor
	Player(const std::string& playerName, int startingBalance)
		: name(playerName), balance(startingBalance) {}

	// Getter for name
	std::string getName() const {
		return name;
	}

	// Getter for balance
	int getBalance() const {
		return balance;
	}

	// Function to update balance
	void updateBalance(int amount) {
		balance += amount;
	}
};