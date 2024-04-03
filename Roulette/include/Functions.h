#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include <tuple>
#include <fstream>
#include <regex>
#include <array>
#include <SDL.h>     
#include <thread>
#include <mutex>
#include "Functions.h"
#include "Bet.h"
#include "Player.h"
#include "Bet_Check.h"

void initializePlayerData(std::string& playerName, int& initialBalance);
void writePlayerDataToFile(const std::string& playerName, int initialBalance, int finalBalance);
int BettingOptions();
std::tuple<std::vector<int>, std::string, int> getBettingOptionParameters(int option);
int randomNumber(int min, int max);
void Image(int argc, char** argv);
void EndOfGameExpression(int Balance, std::string name, float PercentChange, int FinalBalance);
void output_DealerName(const std::string& name);
void output_DealerName(int name);

