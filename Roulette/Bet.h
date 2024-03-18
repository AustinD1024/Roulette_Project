#ifndef BET_H
#define BET_H

#include <string>
// Base class for betting options
class Bet {
public:
    virtual bool isWinning(int winningNumber) const = 0;
    virtual int payout(int betAmount) const = 0;
    virtual std::string getName() const = 0;
    virtual ~Bet() {}
};

#endif