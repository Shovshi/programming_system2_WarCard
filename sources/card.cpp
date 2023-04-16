#include "card.hpp"
#include <cstdlib>
#include <iostream>

int Card::getNumCard(){
  int numCard;
  switch (this->rank) {
    case TWO:
      numCard = 2;
      break;
    case THREE:
      numCard = 3;
      break;
    case FOUR:
      numCard = 4;
      break;
    case FIVE:
      numCard = 5;
      break;
    case SIX:
      numCard = 6;
      break;
    case SEVEN:
      numCard = 7;
      break;
    case EIGHT:
      numCard = 8;
      break;
    case NINE:
      numCard = 9;
      break;
    case TEN:
        numCard = 10;
        break;
    case JACK:
        numCard = 11;
    case QUEEN:
        numCard = 12;
        break;
    case KING:
      numCard = 13;
      break;
    case ACE:
      numCard = 14;
      break;
  }
  return numCard;
}

void Card::printCard()
{
  std::string rankStr, suitStr;

  switch (this->rank) {
    case TWO:
      rankStr = "Two";
      break;
    case THREE:
      rankStr = "Three";
      break;
    case FOUR:
      rankStr = "Four";
      break;
    case FIVE:
      rankStr = "Five";
      break;
    case SIX:
      rankStr = "Six";
      break;
    case SEVEN:
      rankStr = "Seven";
      break;
    case EIGHT:
      rankStr = "Eight";
      break;
    case NINE:
      rankStr = "Nine";
      break;
    case TEN:
        rankStr = "Ten";
        break;
    case JACK:
        rankStr = "Jack";
        break;
    case QUEEN:
        rankStr = "Queen";
        break;
    case KING:
      rankStr = "King";
      break;
    case ACE:
      rankStr = "Ace";
      break;
  }

  switch (this->suit) {
    case CLUBS:
      suitStr = "Clubs";
      break;
    case DIAMONDS:
      suitStr = "Diamonds";
      break;
    case HEARTS:
      suitStr = "Hearts";
      break;
    case SPADES:
      suitStr = "Spades";
      break;
  }

  std::cout<<" " << rankStr << " of " << suitStr << std::endl;
}








