#include "Functions.h"

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