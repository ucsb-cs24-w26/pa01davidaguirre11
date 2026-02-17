// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card{
  public:
    Card();
    Card(char s, const std::string& v);
    
    char getSuit() const;
    std::string getValue() const;
    
    bool operator==(const Card& other) const;
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
  
  private:
    char suit;
    std::string value;
    
    int suitRank() const;
    int valueRank() const;
    
};
#endif
