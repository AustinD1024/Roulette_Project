#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include "BettingOptions.h"
#include "Bet.h"
#include "Bet_Check.h"
#include "randomNumber.h"
#include "getBettingOptionParameters.h"


int main() {
    // Seed the random number generator
    std::srand(std::time(nullptr));

    int balance = 1000; // Starting balance
    int betAmount;

    std::cout << "Welcome to Roulette!" << std::endl;
    std::cout << "Your starting balance is $" << balance << std::endl;

    while (balance > 0) {
        // Ask the player for their bet
        std::cout << "Place your bet (0 to quit): $";
        std::cin >> betAmount;

        // Check if the player wants to quit
        if (betAmount == 0) {
            std::cout << "Thanks for playing!" << std::endl;
            break;
        }

        // Check if the bet amount is valid
        if (betAmount < 0 || betAmount > balance) {
            std::cout << "Invalid bet amount. Please try again." << std::endl;
            continue;
        }

        int option = BettingOptions(); // Call betting options function

        // Get betting option parameters
        auto bettingData = getBettingOptionParameters(option);
        std::vector<int> chosenNumbers = std::get<0>(bettingData);
        std::string betName = std::get<1>(bettingData);
        int payoutOdds = std::get<2>(bettingData);

        // Create Bet_Check object
        Bet_Check betCheck(chosenNumbers, payoutOdds, betName);

        // Spin the wheel and determine the outcome
        int winningNumber = randomNumber(1, 36);

        std::cout << std::endl;
        std::cout << "The wheel spins... " << winningNumber << "!\n\n";

        // Determine if the player wins or loses
        if (betCheck.isWinning(winningNumber)) {
            std::cout << "Congratulations! You win $" << betCheck.payout(betAmount) << " with " << betCheck.getName() << std::endl;
            balance += betCheck.payout(betAmount);
        }
        else {
            std::cout << "Sorry, you lose $" << betAmount << " with " << betCheck.getName() << std::endl << std::endl;;
            balance -= betAmount;
        }

        // Display the updated balance
        std::cout << "Your balance is now $" << balance << std::endl << std::endl;
    }

    return 0;
}
