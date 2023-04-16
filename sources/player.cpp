#include <iostream>
#include <string> // include the string header file
#include "player.hpp"


int Player::cardesTaken(){
    return winsCards.size();
}

int Player::stacksize(){
    return cards.size();
}

void Player:: addCard(Card card) {
    cards.push_back(card);
}


