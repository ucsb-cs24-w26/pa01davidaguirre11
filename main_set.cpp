// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

void playGame(set<Card>& player1, set<Card>& player2);

void playGame(set<Card>& player1, set<Card>& player2){
  bool p1Turn = true;
  bool matchFound = true;
  
  while(matchFound)
  {
    matchFound = false;
    if(p1Turn)
    {
      for(auto it = player1.begin(); it != player1.end(); ++it)
      {
        auto found = player2.find(*it);
        if(found != player2.end())
        {
          cout << "Alice picked matching card "
               << *it << endl;
          player2.erase(found);
          player1.erase(it);
          
          matchFound = true;
          break;
        }
      }
    }
    else
    {
      for(auto it = player2.rbegin(); it != player2.rend(); ++it)
      {
        auto found = player1.find(*it);
        if(found != player1.end())
        {
          cout << "Bob picked matching card "
               << *it << endl;
          player1.erase(found);
          player2.erase(*it);
          
          matchFound = true;
          break;
        }
      }
    }
    p1Turn = !p1Turn;
  }
   
    
  //print
  cout << "\nAlice's cards:" << endl;
    for (const auto& card : player1)
        cout << card << endl;

    cout << "\nBob's cards:" << endl;
    for (const auto& card : player2)
        cout << card << endl;
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  
  // create two sets
  set<Card> player1;
  set<Card> player2;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    player1.insert(Card(suit,value));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    player2.insert(Card(suit,value));
  }
  cardFile2.close();
  
  //playGame
  playGame(player1, player2);
  return 0;
}

