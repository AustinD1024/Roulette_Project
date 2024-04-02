#include "Functions.h"

void EndOfGameExpression(int AmountWon, std::string name, float PercentChange, int FinalBalance)
{
	//REGULAR EXPRESSION
	// Define the regular expression pattern to match "win" or "lose"
	std::string pattern = "(win|lose)";
	std::string AdjectiveWin;
	std::string AdjectiveLose;

	// Create a regex object
	std::regex regexPattern(pattern);

	//Determine adjective based on winning or losing
	if (AmountWon > 0)
	{
		AdjectiveWin = "win";
	}
	if (AmountWon < 0)
	{
		AdjectiveLose = "lose";
	}

	// Check if the test strings match the pattern
	if (std::regex_match(AdjectiveWin, regexPattern)) {
		std::cout << "Congratulations " << name << "! You won $" << AmountWon << " and are left with a balance of $" << FinalBalance << "! This is a % " << 100 - PercentChange << " gain!" << std::endl;
	}
	if (std::regex_match(AdjectiveLose, regexPattern)) {
		std::cout << "Sorry " << name << "! You lost $" << -1*AmountWon << " and are left with a balance of $" << FinalBalance << ". This is %" << 100 - PercentChange << " loss." << std::endl;
	}
	else
	{	}

}