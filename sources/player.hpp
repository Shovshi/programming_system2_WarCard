#pragma once
#include <string>
#include <vector>
#include "card.hpp"
using namespace std;

class Player{
public:
    std::string name;
    bool isPlaying = false;
    vector<Card> cards;
    vector<Card> winsCards;
    vector<Card> lastTurnCards;
    int winsNum = 0;
    
    Player(string name){
        name = name;
    }

    Player(){}

    int stacksize();

    int cardesTaken();

    void addCard(Card card);
        
};