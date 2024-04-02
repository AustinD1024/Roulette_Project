#include "Functions.h"


std::mutex mtx; // Mutex for synchronization

bool imageDisplayed = false; // Global variable to signal when the image display is finished
std::string projectName = "Roulette"; // Global variable representing the title of the project
int initialBalance = 1500; // Global variable for initial balance 
std::atomic<bool> quit(false); //For Wheel Image


//Template Function
template <typename T>
T AmountWon_AndEndExpression(T x, T y)
{
	return x + y;
}


//Main Function
int main(int argc, char** argv) {


	// Launch a separate thread for image display
	std::thread imageThread(Image, argc, argv);


	// Seed the random number generator
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	std::string playerName;


	// Initialize player data
	initializePlayerData(playerName, initialBalance);


	//Obtain user's first name
	std::cout << "Welcome to " << projectName << "!" << std::endl;
	std::cout << "Please enter your name: ";
	std::getline(std::cin, playerName);


	// Create a player object pointer
	Player* playerPtr = new Player(playerName, initialBalance);


	std::cout << "Hello, " << playerPtr->getName() << "! Your starting balance is $" << playerPtr->getBalance() << std::endl;


	unsigned int NumberBets = 0; //Always positive


	//Lamda Function to keep track of number of bets
	auto NumBetsTotal = [](unsigned int CurrentNumBets, unsigned int BetIncrement)
		{
			return CurrentNumBets + BetIncrement;
		};


	//While Loop that runs until player is out of money, or quits the game
	while (playerPtr->getBalance() > 0) {
		int betAmount;


		// Prompt the player for their bet
		std::cout << "Place your bet (0 to quit): $";
		std::cin >> betAmount;


		// Check if the player wants to quit
		if (betAmount == 0) {
			//std::cout << "Thanks for playing!" << std::endl;
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


		//Call Lamda Function and increment NumberBets
		NumberBets = NumBetsTotal(NumberBets, 1);

	}

	//Make sure image closes
	if (quit == false)
	{
		quit = true;
	}


	//File Handling
	writePlayerDataToFile(playerName, initialBalance, playerPtr->getBalance());


	//Determine amount won
	signed int Winnings; //can be positive or negative
	int Balance;
	Balance = playerPtr->getBalance();
	Winnings = AmountWon_AndEndExpression(Balance, -1 * initialBalance); //Call Template Function


	//Calculate how much percent of initial amount they have
	double FractionalChange = static_cast<float>(Balance)/static_cast<float>(initialBalance);
	float PercentageChange = 100*static_cast<float>(FractionalChange);


	std::cout << "\n####################################################################################################\n";
	
	//Call Regular Expression function for end of game expressions
	EndOfGameExpression(Winnings, playerPtr -> getName(), PercentageChange, playerPtr -> getBalance());


	//Output Number of bets
	std::cout << "During the game you made " << NumberBets << " bets!" << std::endl;


	//Final Expression (Using Template Function)
	std::string ThankYou = "Thank you for playing ";
	std::string FinalThankYou = AmountWon_AndEndExpression(ThankYou, playerPtr->getName());
	char exclamation_point = '!';
	std::cout << FinalThankYou << exclamation_point << std::endl;

	std::cout << "####################################################################################################\n\n";


	// Clean up memory
	delete playerPtr;


	// Join the image display thread
	imageThread.join();


	return 0;
}