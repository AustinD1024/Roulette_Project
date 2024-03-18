#include <cstdlib>
#include <ctime>
#include "randomNumber.h"

// Function to generate a random number between min and max (inclusive)
int randomNumber(int min, int max) {
    int rand_number = std::rand() % (max - min + 1) + min;
    return rand_number;
}


