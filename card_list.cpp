// card_list.cpp
// Author: David Aguirre
// Implementation of the classes defined in card_list.h
#include "card_list.h"

custom_BST::custom_BST() : root(nullptr) {}
custom_BST::~custom_BST(){
  clear(root);
}
void custom_BST::clear(Node* node)
{
  if(!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

void custom_BST::insert(const Card& value)
{
  root = insertHelper(value,root,nullptr);
}

custom_BST::Node* custom_BST::insertHelper(const Card& value, Node* node, Node* parent)
{
  if(!node)
  {
    Node* newNode = new Node(value);
    newNode->parent = parent;
    return newNode;
  }
  if(value < node->key)
  {
    node->left = insertHelper(value,node->left,node);
  }
  else if(value > node->key)
  {
    node->right = insertHelper(value, node->right,node);
  }
  return node;
}

void custom_BST::remove(const Card& value){
  root = removeHelper(root, value);
}
custom_BST:: Node* custom_BST::removeHelper(Node* node, const Card& value){
  if(!node) return nullptr;
  
  if(value < node->key){              
    node->left = removeHelper(node->left,value);
  }
  else if(value > node->key){
    node->right = removeHelper(node->right,value);
  }
  else
  {
    //1 or 0 child
    if (!node->left)
    {
      Node* temp = node->right;
      
      if (temp) temp->parent = node->parent; 
      delete node;
      return temp;
    }
    else if(!node->right)
    {
      Node* temp = node->left;
      
      if (temp) temp->parent = node->parent; 
      delete node;
      return temp;
    }
    //2 child
    Node* temp = minimum(node->right);
    node->key = temp->key;
    node->right = removeHelper(node->right,temp->key);
  }
  return node;
}

bool custom_BST::contains(const Card& value) const{
  return containsHelper(root, value) != nullptr;
}
custom_BST::Node* custom_BST::containsHelper(Node* node, const Card& value) const
{
  if(!node)                  return nullptr;
  
  if(value == node->key)     return node;
  
  else if(value < node->key) return containsHelper(node->left,value);
  
  else                       return containsHelper(node->right,value);
}

void custom_BST::print() const {
  printInOrder(root);
}
void custom_BST::printInOrder(Node* node) const
{
  if(!node) return;
  printInOrder(node->left);
  std::cout<< node->key << std::endl;
  printInOrder(node->right);
}


//private helpers max and min
custom_BST::Node* custom_BST::minimum(Node* node) const{
  while(node && node->left) node = node->left;
  return node;
}

custom_BST::Node* custom_BST::maximum(Node* node) const{
  while(node && node->right) node = node->right;
  return node;
}

//iterators methods

custom_BST::iterator::iterator(Node* ptr) : current(ptr) {}

Card& custom_BST::iterator::operator*() const{
  return current->key;
}

Card* custom_BST::iterator::operator->() const{
  return &(current->key);
}

custom_BST::iterator& custom_BST::iterator::operator++(){
  if (current -> right){
    current = current->right;
    while(current->left){
      current = current->left;
    }
  }else{
    Node* parent = current->parent;
    while(parent && current == parent->right){
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

custom_BST::iterator& custom_BST::iterator::operator--(){
  if(current->left){
    current = current->left;
    while(current->right){
      current = current->right;
    }
  }else {
    Node* parent = current->parent;
    while(parent && current == parent->left){
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

bool custom_BST::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

bool custom_BST::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

custom_BST::iterator custom_BST::begin() const {
  return iterator(minimum(root));
}

custom_BST::iterator custom_BST::end() const {
  return iterator(nullptr);
}

custom_BST::iterator custom_BST::rbegin() const {
  return iterator(maximum(root));
}

custom_BST::iterator custom_BST::rend() const {
  return iterator(nullptr);
}

void playGame(custom_BST& player1, custom_BST& player2){
  bool p1Turn = true;
  bool matchFound = true;
  
  while(matchFound)
  {
    matchFound = false;
    
    if(p1Turn)
    {
      for(auto it = player1.begin(); it != player1.end(); ++it)
      {
        if(player2.contains(*it))
        {
          std::cout <<"Alice picked matching card "
                    <<*it << std::endl;
          
          Card value = *it;
          player2.remove(value);
          player1.remove(value);
          
          matchFound = true;
          break;
        }
      }
    }
    else
    {
      for(auto it = player2.rbegin(); it != player2.rend(); --it)
      {
        if(player1.contains(*it))
        {
          std::cout <<"Bob picked matching card "
                    <<*it << std::endl;
        
          Card value = *it;
          player1.remove(value);
          player2.remove(value);
          
          matchFound = true;
          break;
        }
      }
    }
    p1Turn = !p1Turn;
  }
}