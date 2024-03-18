#ifndef BETCHECK_H
#define BETCHECK_H

//#include "Bet.h"
#include <iostream>
#include <vector>

// Class for Bet Check
class Bet_Check : public Bet {
private:
    std::vector<int> numbers;
    int payoutOdds; // New member variable for payout odds
    std::string name; // New member variable for the name of the bet
public:
    // Constructor to initialize the Bet_Check object with a vector of numbers
    Bet_Check(const std::vector<int>& nums, int payoutOdds, const std::string& name)
        : numbers(nums), payoutOdds(payoutOdds), name(name) {}

    bool isWinning(int winningNumber) const override {
        for (int num : numbers) {
            if (winningNumber == num) {
                return true;
            }
        }
        return false;
    }

    int payout(int betAmount) const override {
        return betAmount * payoutOdds; // Use the provided payout odds
    }

    std::string getName() const override {
        std::string betName = name + " (";
        for (size_t i = 0; i < numbers.size(); ++i) {
            betName += std::to_string(numbers[i]);
            if (i != numbers.size() - 1) {
                betName += ", ";
            }
        }
        betName += ")";
        return betName;
    }
};

#endif
