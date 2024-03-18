#include <iostream>
#include <vector>
#include <tuple>

std::tuple<std::vector<int>, std::string, int> getBettingNumbers(int option)
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