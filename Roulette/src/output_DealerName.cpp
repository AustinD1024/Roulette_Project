#include "Functions.h"

// Overloaded function to handle string input
void output_DealerName(const std::string& name) {
	std::array<std::string, 4> Greeting = { {"I ", "am ", "your ", "dealer: "} }; //Use of array container
	// Output each element of the Greeting array
	for (const auto& word : Greeting) {
		std::cout << word;
	}
	std::cout << name;
}
// OVerloaded function to handle int input
void output_DealerName(int name) {
	std::cout << name << std::endl;
}