#include "Functions.h"

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