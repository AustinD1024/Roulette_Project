//Function to ask User what they Want to Bet and display betting options
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits

int BettingOptions()
{
    int option;

    // Loop until a valid option is entered
    while (true) {
        std::cout << "Choose your bet option:" << std::endl;
        std::cout << "1. Straight (1 number)" << std::endl;
        std::cout << "2. Split (2 numbers)" << std::endl;
        std::cout << "3. Street (3 numbers)" << std::endl;
        std::cout << "4. Square (4 numbers)" << std::endl;
        std::cout << "5. Six Line (6 numbers)" << std::endl;
        std::cout << "6. Colors (black or red)" << std::endl;
        std::cout << "7. Dozens (12 numbers)" << std::endl;
        std::cout << "8. Highs/Lows (1-18 or 19-36)" << std::endl;
        std::cout << "9. Odds/Evens (18 Numbers)" << std::endl;
        std::cout << "10. Columns (12 numbers)" << std::endl;
        std::cout << "Enter number option: ";

        // Get user input
        std::cin >> option;

        std::cout << "\n\n";

        // Check if input is valid
        if (std::cin.fail() || option < 1 || option > 10) {
            std::cout << "Invalid input. Please enter a number between 1 and 10." << std::endl;
            // Clear the input buffer
            std::cin.clear();
            // Discard any remaining characters in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            // Input is valid, break out of the loop
            break;
        }
    }

    return option;
}