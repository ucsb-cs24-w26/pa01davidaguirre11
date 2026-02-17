// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
  
  custom_BST player1;
  custom_BST player2;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    Card c(suit,value);
    player1.insert(c);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string value = line.substr(2);
    Card c(suit,value);
    player2.insert(c);
  }
  cardFile2.close();
  
  //game function
  
  playGame(player1, player2);
  cout<<endl;
  cout << "Alice's cards: " << endl;
  player1.print();
  cout<<endl;
  cout << "Bob's cards: " << endl;
  player2.print();
  
  return 0;
}
