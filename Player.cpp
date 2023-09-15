#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(){
    mFirstName = "J";
    mLastName = "Random";
    mRating = 3;
    mCurrBase = 0;
}

Player::Player(string fName, string lName, int rating){
    mLastName = lName;
    mFirstName = fName;
    mRating = rating;
    mCurrBase = 0;
}

int Player::getBase() const{
    return mCurrBase;
}

int Player::getRating() const{
    return mRating;
}

string Player::getName() const{
    return mFirstName + " " + mLastName;
}

void Player::incrementBase(const int X){
    mCurrBase += X;
}

void Player::resetBase(){
    mCurrBase = 0;
}