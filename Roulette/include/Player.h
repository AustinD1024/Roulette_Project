//#pragma once
//
//#include "Functions.h"
//
//// Player class definition
//class Player {
//private:
//	std::string name;
//	int balance;
//
//public:
//	// Constructor
//	Player(const std::string& playerName, int startingBalance)
//		: name(playerName), balance(startingBalance) {}
//
//	// Getter for name
//	std::string getName() const {
//		return name;
//	}
//
//	// Getter for balance
//	int getBalance() const {
//		return balance;
//	}
//
//	// Function to update balance
//	void updateBalance(int amount) {
//		balance += amount;
//	}
//};

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

	// Overloaded addition operator
	Player operator+(int amount) const {
		Player result = *this;
		result.balance += amount;
		return result;
	}

	// Overloaded subtraction operator
	Player operator-(int amount) const {
		Player result = *this;
		result.balance -= amount;
		return result;
	}


	// Operator overloading for calculating percentage change
	float operator/(int initialBalance) const {
		if (initialBalance == 0) {
			// Handle the error or return a default value
			return 0.0f;
		}
		return 100 * static_cast<float>(balance) / static_cast<float>(initialBalance);
	}
};
