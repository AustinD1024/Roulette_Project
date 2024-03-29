#include "Functions.h"

// Global variable to signal when the image display is finished
bool imageDisplayed = false;
std::mutex mtx; // Mutex for synchronization

// Global variable representing the title of the project
std::string projectName = "Roulette";

// Global variable for initial balance
int initialBalance = 1500;

std::atomic<bool> quit(false); //For Wheel Image

//Main Function
int main(int argc, char** argv) {


	// Launch a separate thread for image display
	std::thread imageThread(Image, argc, argv);


	// Seed the random number generator
	//std::srand(std::time(nullptr));
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	std::string playerName;


	// Initialize player data
	initializePlayerData(playerName, initialBalance);


	std::cout << "Welcome to " << projectName << "!" << std::endl;
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

		writePlayerDataToFile(playerName, initialBalance, playerPtr->getBalance());
	}


	std::cout << "Goodbye, " << playerPtr->getName() << "! Thanks for playing!" << std::endl;



	// Clean up memory
	delete playerPtr;

	// Join the image display thread
	imageThread.join();

	return 0;
}