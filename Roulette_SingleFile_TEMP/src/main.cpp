#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include <tuple>
#include <fstream>
#include <SDL.h>     
#include "image.h"
#include <thread>
#include <mutex>


// Global variable to signal when the image display is finished
bool imageDisplayed = false;
std::mutex mtx; // Mutex for synchronization

// Global variable representing the title of the project
std::string projectName = "Roulette";

// Global variable for initial balance
int initialBalance = 1500;

///////////////////////////////////////////////////////////////////////////////////
// Function to initialize player data from input file or create if not exists
void initializePlayerData(std::string& playerName, int& initialBalance) {
	std::ifstream inputFile("player_data.txt");
	if (inputFile.is_open()) {
		inputFile >> playerName; // Read player name
		inputFile.close();
	}
	else {
		std::ofstream createInputFile("player_data.txt");
		if (createInputFile.is_open()) {
			createInputFile << "John Doe" << std::endl;  // Default name
			createInputFile.close();
			playerName = "John Doe";
		}
		else {
			std::cerr << "Error: Unable to create player_data.txt" << std::endl;
			exit(1); // Exit the program with an error code
		}
	}

}


// Function to write player data to output file
void writePlayerDataToFile(const std::string& playerName, int initialBalance, int finalBalance) {
	std::ofstream outputFile("player_results.txt", std::ios::app);  // Open file in append mode
	if (outputFile.is_open()) {
		outputFile << "Player Name: " << playerName << std::endl;
		outputFile << "Initial Balance: $" << initialBalance << std::endl;
		outputFile << "Final Balance: $" << finalBalance << std::endl;
		outputFile << "Amount Won/Lost: $" << (finalBalance - initialBalance) << std::endl << std::endl;
		outputFile.close();
	}
	else {
		std::cerr << "Error: Unable to open player_results.txt for writing" << std::endl;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bet {
public:
	virtual bool isWinning(int winningNumber) const = 0;
	virtual int payout(int betAmount) const = 0;
	virtual std::string getName() const = 0;
	virtual ~Bet() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<std::vector<int>, std::string, int> getBettingOptionParameters(int option)
{
	std::string betName;
	int PayoutOdds;
	std::vector<int> numbers;
	numbers.clear();

	//Straight Bet
	if (option == 1)
	{
		betName = "Straight";
		PayoutOdds = 35;
		std::cout << "Enter your number: ";
		while (true)
		{
			int num;
			std::cin >> num;
			std::cout << std::endl;
			if (num < 1 || num > 36)
			{
				std::cout << "Invalid number. Please enter a number between 1 and 36: ";
				continue;
			}
			if (num >= 1 || num <= 36)
			{
				numbers.push_back(num);
				break;
			}
		}
		return std::make_tuple(numbers, betName, PayoutOdds);

	}

	//Split Bet
	if (option == 2)
	{
		betName = "Split";
		PayoutOdds = 17;

		std::vector<std::pair<int, int>> splitBets; // Vector to store all split bets

		// Generate horizontal splits
		for (int i = 1; i <= 36; ++i) {
			if (i % 3 != 0) { // Exclude splits ending with 3, 6, 9, ..., 36
				splitBets.emplace_back(i, i + 1);
			}
		}

		// Generate vertical splits
		for (int i = 1; i <= 33; ++i) {
			splitBets.emplace_back(i, i + 3);
		}

		// Output all possible split bets
		std::cout << "All possible split bets:" << std::endl;
		for (size_t i = 0; i < splitBets.size(); ++i) {
			std::cout << i + 1 << ". Split Bet (" << splitBets[i].first << ", " << splitBets[i].second << ")" << std::endl;
		}

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid split option
		while (!validChoice) {
			// Ask user to choose a split option
			std::cout << "Choose a split option (enter corresponding number): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && static_cast<size_t>(choice) <= splitBets.size()) {
				validChoice = true;
				std::cout << "You chose: Split Bet (" << splitBets[choice - 1].first << ", " << splitBets[choice - 1].second << ")" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter a number within the range." << std::endl;
			}
		}

		// Store chosen split numbers in the numbers vector
		numbers.push_back(splitBets[choice - 1].first);
		numbers.push_back(splitBets[choice - 1].second);

		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Street Bet
	if (option == 3)
	{
		betName = "Street";
		PayoutOdds = 11;
		std::vector<std::vector<int>> streetBets; // Vector to store all street bets

		// Generate street bets
		for (int i = 1; i <= 34; i += 3) {
			streetBets.push_back({ i, i + 1, i + 2 });
		}

		// Output all possible street bets
		std::cout << "All possible street bets:" << std::endl;
		for (size_t i = 0; i < streetBets.size(); ++i) {
			std::cout << i + 1 << ". Street Bet (" << streetBets[i][0] << ", " << streetBets[i][1] << ", " << streetBets[i][2] << ")" << std::endl;
		}

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid street option
		while (!validChoice) {
			// Ask user to choose a street option
			std::cout << "Choose a street option (enter corresponding number): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && static_cast<size_t>(choice) <= streetBets.size()) {
				validChoice = true;
				// Store chosen street numbers in the numbers vector
				numbers.insert(numbers.end(), streetBets[choice - 1].begin(), streetBets[choice - 1].end());
				std::cout << "You chose: Street Bet (" << streetBets[choice - 1][0] << ", " << streetBets[choice - 1][1] << ", " << streetBets[choice - 1][2] << ")" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter a number within the range." << std::endl;
			}
		}

		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Square bet
	if (option == 4)
	{
		betName = "Square";
		PayoutOdds = 8;

		std::vector<std::vector<int>> squareBets; // Vector to store all square bets

		// Generate square bets
		for (int i = 1; i <= 33; i += 3) {
			for (int j = 0; j < 2; ++j) {
				squareBets.push_back({ i + j, i + j + 1, i + j + 3, i + j + 4 });
			}
		}

		// Output all possible square bets
		std::cout << "All possible square bets:" << std::endl;
		for (size_t i = 0; i < squareBets.size(); ++i) {
			std::cout << i + 1 << ". Square Bet (" << squareBets[i][0] << ", " << squareBets[i][1] << ", "
				<< squareBets[i][2] << ", " << squareBets[i][3] << ")" << std::endl;
		}

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid square option
		while (!validChoice) {
			// Ask user to choose a square option
			std::cout << "Choose a square option (enter corresponding number): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && static_cast<size_t>(choice) <= squareBets.size()) {
				validChoice = true;
				// Store chosen square numbers in the numbers vector
				numbers.insert(numbers.end(), squareBets[choice - 1].begin(), squareBets[choice - 1].end());
				std::cout << "You chose: Square Bet (" << squareBets[choice - 1][0] << ", " << squareBets[choice - 1][1] << ", "
					<< squareBets[choice - 1][2] << ", " << squareBets[choice - 1][3] << ")" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter a number within the range." << std::endl;
			}
		}


		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Six Line Bet
	if (option == 5)
	{
		betName = "Six Line";
		PayoutOdds = 5;
		std::vector<std::vector<int>> sixLineBets; // Vector to store all six line bets

		// Generate six line bets
		for (int i = 1; i <= 31; i += 3) {
			sixLineBets.push_back({ i, i + 1, i + 2, i + 3, i + 4, i + 5 });
		}

		// Output all possible six line bets
		std::cout << "All possible six line bets:" << std::endl;
		for (size_t i = 0; i < sixLineBets.size(); ++i) {
			std::cout << i + 1 << ". Six Line Bet (";
			for (int num : sixLineBets[i]) {
				std::cout << num << " ";
			}
			std::cout << ")" << std::endl;
		}

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid six line option
		while (!validChoice) {
			// Ask user to choose a six line option
			std::cout << "Choose a six line option (enter corresponding number): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && static_cast<size_t>(choice) <= sixLineBets.size()) {
				validChoice = true;
				// Store chosen six line numbers in the numbers vector
				numbers.insert(numbers.end(), sixLineBets[choice - 1].begin(), sixLineBets[choice - 1].end());
				std::cout << "You chose: Six Line Bet (";
				for (int num : sixLineBets[choice - 1]) {
					std::cout << num << " ";
				}
				std::cout << ")" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter a number within the range." << std::endl;
			}
		}

		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Colors Bet
	if (option == 6)
	{
		betName = "Colors";
		PayoutOdds = 1;

		std::vector<std::vector<int>> colorBets = {
	{2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35}, // Black numbers
	{1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}     // Red numbers
		};


		// Output color options
		std::cout << "Choose a color option:" << std::endl;
		std::cout << "1. Black" << std::endl;
		std::cout << "2. Red" << std::endl;

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid color option
		while (!validChoice) {
			// Ask user to choose a color option
			std::cout << "Enter your choice (1 for Black, 2 for Red): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice == 1 || choice == 2) {
				validChoice = true;
				// Store chosen color numbers in the numbers vector
				numbers = colorBets[choice - 1];
				std::cout << "You chose: " << (choice == 1 ? "Black" : "Red") << " Bet" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter 1 for Black or 2 for Red." << std::endl;
			}
		}



		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Dozens bet
	if (option == 7)
	{
		betName = "Dozens";
		PayoutOdds = 2;

		std::vector<std::vector<int>> dozensBets = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},   // 1st dozen (1-12)
	{13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},   // 2nd dozen (13-24)
	{25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36}    // 3rd dozen (25-36)
		};


		// Output dozen options
		std::cout << "Choose a dozen option:" << std::endl;
		std::cout << "1. 1st Dozen (1-12)" << std::endl;
		std::cout << "2. 2nd Dozen (13-24)" << std::endl;
		std::cout << "3. 3rd Dozen (25-36)" << std::endl;

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid dozen option
		while (!validChoice) {
			// Ask user to choose a dozen option
			std::cout << "Enter your choice (1, 2, or 3): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && choice <= 3) {
				validChoice = true;
				// Store chosen dozen numbers in the numbers vector
				numbers = dozensBets[choice - 1];
				std::cout << "You chose: " << (choice == 1 ? "1st" : (choice == 2 ? "2nd" : "3rd")) << " Dozen Bet" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter 1, 2, or 3." << std::endl;
			}
		}

		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Highs/Lows
	if (option == 8)
	{
		betName = "Highs/Lows";
		PayoutOdds = 1;
		std::vector<std::vector<int>> highLowBets = {
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},   // Low numbers (1-18)
	{19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36}  // High numbers (19-36)
		};


		// Output high/low options
		std::cout << "Choose a high/low option:" << std::endl;
		std::cout << "1. Low (1-18)" << std::endl;
		std::cout << "2. High (19-36)" << std::endl;

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid high/low option
		while (!validChoice) {
			// Ask user to choose a high/low option
			std::cout << "Enter your choice (1 for Low, 2 for High): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice == 1 || choice == 2) {
				validChoice = true;
				// Store chosen high/low numbers in the numbers vector
				numbers = highLowBets[choice - 1];
				std::cout << "You chose: " << (choice == 1 ? "Low" : "High") << " Bet" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter 1 for Low or 2 for High." << std::endl;
			}
		}

		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Odds/Evens Bet
	if (option == 9)
	{
		betName = "Odds/Evens";
		PayoutOdds = 1;
		std::vector<std::vector<int>> oddsEvensBets = {
	{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35}, // Odd numbers
	{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36}  // Even numbers
		};


		// Output odd/even options
		std::cout << "Choose an odd/even option:" << std::endl;
		std::cout << "1. Odd" << std::endl;
		std::cout << "2. Even" << std::endl;

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid odd/even option
		while (!validChoice) {
			// Ask user to choose an odd/even option
			std::cout << "Enter your choice (1 for Odd, 2 for Even): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice == 1 || choice == 2) {
				validChoice = true;
				// Store chosen odd/even numbers in the numbers vector
				numbers = oddsEvensBets[choice - 1];
				std::cout << "You chose: " << (choice == 1 ? "Odd" : "Even") << " Bet" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter 1 for Odd or 2 for Even." << std::endl;
			}
		}
		return std::make_tuple(numbers, betName, PayoutOdds);
	}

	//Columns Bet
	if (option == 10)
	{
		betName = "Columns";
		PayoutOdds = 2;

		std::vector<std::vector<int>> columnBets = {
	{1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34},   // 1st column
	{2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35},   // 2nd column
	{3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36}    // 3rd column
		};

		// Output column options
		std::cout << "Choose a column option:" << std::endl;
		std::cout << "1. 1st Column" << std::endl;
		std::cout << "2. 2nd Column" << std::endl;
		std::cout << "3. 3rd Column" << std::endl;

		int choice;
		bool validChoice = false;

		// Loop until user chooses a valid column option
		while (!validChoice) {
			// Ask user to choose a column option
			std::cout << "Enter your choice (1, 2, or 3): ";
			std::cin >> choice;

			// Check if the choice is valid
			if (choice >= 1 && choice <= 3) {
				validChoice = true;
				// Store chosen column numbers in the numbers vector
				numbers = columnBets[choice - 1];
				std::cout << "You chose: " << (choice == 1 ? "1st" : (choice == 2 ? "2nd" : "3rd")) << " Column Bet" << std::endl;
			}
			else {
				std::cout << "Invalid choice! Please enter 1, 2, or 3." << std::endl;
			}
		}

		return std::make_tuple(numbers, betName, PayoutOdds);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Function to generate a random number between min and max (inclusive)
int randomNumber(int min, int max) {
	int rand_number = (std::rand() ^ 0x5A5A5A5A) % (max - min + 1) + min;
	return rand_number;
}

std::atomic<bool> quit(false); //For Wheel Image


int main(int argc, char**argv) {


	// Launch a separate thread for image display
	//bool quitFlag = false;
	//bool* quit = &quitFlag;
	//std::vector<std::string> imageFiles = { "Roulette_Wheel_Image.bmp", "Roulette_Betting_Board.bmp"};
	//Image(argc, argv, imageFiles);
	std::thread imageThread(Image, argc, argv);
	//std::thread imageThread2(Image2, argc, argv);


	// Seed the random number generator
	std::srand(std::time(nullptr));

	std::string playerName;

	//int initialBalance;

	// Initialize player data
	initializePlayerData(playerName, initialBalance);


	std::cout << "Welcome to " << projectName <<"!" << std::endl;
	std::cout << "Please enter your name: ";
	std::getline(std::cin, playerName);


	// Create a player object pointer
	Player* playerPtr = new Player(playerName, initialBalance);

	std::cout << "Hello, " << playerPtr->getName() << "! Your starting balance is $" << playerPtr->getBalance() << std::endl;

	int totalAmountWon = 0;

	while (playerPtr->getBalance() > 0) {
		int betAmount;

		// Prompt the player for their bet
		std::cout << "Place your bet (0 to quit): $";
		std::cin >> betAmount;

		// Check if the player wants to quit
		if (betAmount == 0) {
			std::cout << "Thanks for playing!" << std::endl;
			quit = true;
			break;
		}

		// Check if the bet amount is valid
		if (betAmount < 0 || betAmount > playerPtr->getBalance()) {
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
			int payout = betCheck.payout(betAmount);
			std::cout << "Congratulations! You win $" << payout << " with " << betCheck.getName() << std::endl;
			playerPtr->updateBalance(payout);
		}
		else {
			std::cout << "Sorry, you lose $" << betAmount << " with " << betCheck.getName() << std::endl;
			playerPtr->updateBalance(-betAmount);
		}

		// Display the updated balance
		std::cout << "Your balance is now $" << playerPtr->getBalance() << std::endl << std::endl;

		//int AmountWon = playerPtr->getBalance() - initialBalance;
		writePlayerDataToFile(playerName, initialBalance, playerPtr->getBalance());
	}


	std::cout << "Goodbye, " << playerPtr->getName() << "! Thanks for playing!" << std::endl;



	// Clean up memory
	delete playerPtr;

	// Join the image display thread (FIGURE OUT WHY IT WONT END PROGRAM!!!
	//quit = true;

	imageThread.join();
	//imageThread2.join();

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////