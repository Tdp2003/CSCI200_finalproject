#include "Team.h"
#include <fstream>
#include <iostream>

using namespace std;

Team::Team(const bool home){
    mHome = home;
    mName = "";
    mpPlayers = new Array<Player*>();
}

string Team::getName() const{
    return mName;
}

List<Player*>* Team::getPlayers() const{
    return mpPlayers;
}


bool Team::formTeam(){
    //file stream opened
    ifstream fin;
    if(mHome){
        fin.open("homeTeam.txt");
    }else{
        fin.open("awayTeam.txt");
    }

    if(!fin.is_open()){
        cerr << "File could not be opened" << endl;
        return false;
    }
    //based on the correct file format, the names and ratings of each player on the team are added to 
    //the mpPlayers array, which is essentially the lineup
    string pFirstName = "";
    string pLastName = "";
    int rating(0), counter(0);

    fin >> mName;

    while(!fin.eof()){
        fin >> pFirstName;
        fin >> pLastName;
        fin >> rating;
        //check to make sure that the rating entered is valid
        if(rating > 5){
            rating = 5;
        }else if(rating < 0){
            rating = 0;
        }
        mpPlayers->insert(counter, new Player(pFirstName,pLastName,rating));
        counter++;
    }
    fin.close();
    return true;
}