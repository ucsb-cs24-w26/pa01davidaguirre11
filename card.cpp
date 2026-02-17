// card.cpp
// Author: David Aguirre
// Implementation of the classes defined in card.h

#include "card.h"
#include <cstdlib> 

Card::Card() : suit('c'), value("a") {}


Card:: Card(char s, const std::string& v) : suit(s), value(v) {}

char Card::getSuit() const {
  return suit;
}

std::string Card::getValue() const {
  return value;
}

int Card::suitRank() const {
  switch (suit) {
    case 'c' : return 0;
    case 'd' : return 1;
    case 's' : return 2;
    case 'h' : return 3;
  }
  return -1;
}

int Card::valueRank() const {
  if(value == "a") return 1;
  if(value == "j") return 11;
  if(value == "q") return 12;
  if(value == "k") return 13;
  
  return std::stoi(value);
}

bool Card::operator==(const Card& other) const {
  return suit == other.suit && value == other.value;
}

bool Card::operator<(const Card& other) const {
  if(suitRank() != other.suitRank())
  {
    return suitRank() < other.suitRank();
  }
  //since suits are equal, compare values
  return valueRank() < other.valueRank();
}

bool Card::operator>(const Card& other) const {
  return other < *this; //reverses logic of operator <
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit << " " << card.value;
    return os;
}