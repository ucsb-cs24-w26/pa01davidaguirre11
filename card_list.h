// card_list.h
// Author: David Aguirre
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

class custom_BST{
  private:
    struct Node{
      Card key;
      Node* left;
      Node* right;
      Node* parent;
      //constructor 
      Node(const Card& c) : key(c),left(nullptr),right(nullptr),parent(nullptr) { }
    };
    Node *root;
    //private helpers
    void clear(Node* node);
    Node* insertHelper(const Card& value,Node* node,Node* parent);
    Node* removeHelper(Node* node, const Card& value);
    Node* containsHelper(Node* node, const Card& value) const;
    
    Node* minimum(Node* node) const;
    Node* maximum(Node* node) const;
    void printInOrder(Node* node) const;
    
  public:
    custom_BST();
    ~custom_BST();
    
    //required public methods
    void insert(const Card& value);
    void remove(const Card& value);
    bool contains(const Card& value) const;
    void print() const;
    
    //bilateral iterators
    class iterator{
      private:
        Node* current;
      public:
        iterator(Node* ptr = nullptr);
        Card& operator*() const;
        Card* operator->() const;
        
        iterator& operator++();
        iterator& operator--();
        
        bool operator==(const iterator& check) const;
        bool operator!=(const iterator& check) const;
        
        friend class custom_BST;
    };
    
    //iterator methods
    iterator begin() const;
    iterator end() const;
    
    iterator rbegin() const;
    iterator rend() const;
};
void playGame(custom_BST& player1, custom_BST& player2);

#endif

