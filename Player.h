#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player{
public:
    Player();
    Player(string, string, int);
    int getBase() const;
    int getRating() const;
    string getName() const;
    void incrementBase(const int);
    void resetBase();
private:
    string mLastName;
    string mFirstName;
    int mRating;
    int mCurrBase;
};

#endif