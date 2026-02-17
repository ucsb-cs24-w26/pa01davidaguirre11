#include <iostream>
#include <cassert>
#include "card.h"
#include "card_list.h"

using namespace std;

/* =====================================================
   Helper function to create cards quickly
===================================================== */
Card C(char s, string v) {
    return Card(s, v);
}

/* =====================================================
   TEST BST PUBLIC METHODS
===================================================== */

void testInsertAndContains() {

    // 1?? Empty tree
    BST tree;
    assert(!tree.contains(C('c',"a")));

    // 2?? Single node
    tree.insert(C('c',"a"));
    assert(tree.contains(C('c',"a")));

    // 3?? Multiple nodes
    tree.insert(C('d',"3"));
    tree.insert(C('h',"9"));
    assert(tree.contains(C('d',"3")));
    assert(tree.contains(C('h',"9")));

    // 4?? Duplicate insert (should not duplicate)
    tree.insert(C('c',"a"));
    assert(tree.contains(C('c',"a")));

    // 5?? Edge: non-existent
    assert(!tree.contains(C('s',"5")));
}

void testRemove() {

    BST tree;

    // 1?? Remove from empty tree
    tree.remove(C('c',"a"));  // should not crash

    // 2?? Remove single node
    tree.insert(C('c',"a"));
    tree.remove(C('c',"a"));
    assert(!tree.contains(C('c',"a")));

    // 3?? Remove leaf node
    tree.insert(C('c',"a"));
    tree.insert(C('d',"3"));
    tree.remove(C('d',"3"));
    assert(!tree.contains(C('d',"3")));

    // 4?? Remove node with one child
    tree.insert(C('h',"9"));
    tree.remove(C('c',"a"));
    assert(!tree.contains(C('c',"a")));

    // 5?? Remove non-existent
    tree.remove(C('s',"7"));  // should not crash
}

void testPrint() {
    BST tree;

    tree.insert(C('h',"9"));
    tree.insert(C('c',"a"));
    tree.insert(C('d',"3"));

    cout << "Print test (should be sorted):" << endl;
    tree.print();
}

/* =====================================================
   TEST ITERATOR
===================================================== */

void testIteratorEmpty() {
    BST tree;
    assert(tree.begin() == tree.end());
    assert(tree.rbegin() == tree.rend());
}

void testIteratorSingle() {
    BST tree;
    tree.insert(C('c',"a"));

    auto it = tree.begin();
    assert(*it == C('c',"a"));

    ++it;
    assert(it == tree.end());
}

void testIteratorMultipleForward() {
    BST tree;

    tree.insert(C('h',"9"));
    tree.insert(C('c',"a"));
    tree.insert(C('d',"3"));

    auto it = tree.begin();

    assert(*it == C('c',"a"));
    ++it;
    assert(*it == C('d',"3"));
    ++it;
    assert(*it == C('h',"9"));
}

void testIteratorMultipleReverse() {
    BST tree;

    tree.insert(C('h',"9"));
    tree.insert(C('c',"a"));
    tree.insert(C('d',"3"));

    auto it = tree.rbegin();

    assert(*it == C('h',"9"));
    --it;
    assert(*it == C('d',"3"));
    --it;
    assert(*it == C('c',"a"));
}

void testIteratorComparison() {
    BST tree;
    tree.insert(C('c',"a"));

    auto it1 = tree.begin();
    auto it2 = tree.begin();

    assert(it1 == it2);

    ++it1;
    assert(it1 != it2);
}

/* =====================================================
   TEST playGame FUNCTION
===================================================== */

void playGame(BST& p1, BST& p2) {
    while (p1.begin() != p1.end() &&
           p2.begin() != p2.end()) {

        Card c1 = *p1.begin();
        Card c2 = *p2.begin();

        if (c1 == c2) {
            p1.remove(c1);
            p2.remove(c2);
        } else if (c1 < c2) {
            p1.remove(c1);
        } else {
            p2.remove(c2);
        }
    }
}

void testPlayCommonCards() {
    BST p1, p2;

    p1.insert(C('c',"a"));
    p2.insert(C('c',"a"));

    playGame(p1, p2);

    assert(p1.begin() == p1.end());
    assert(p2.begin() == p2.end());
}

void testPlayOneEmpty() {
    BST p1, p2;

    p1.insert(C('c',"a"));

    playGame(p1, p2);

    assert(p1.contains(C('c',"a")));
}

void testPlayNoCommon() {
    BST p1, p2;

    p1.insert(C('c',"a"));
    p2.insert(C('h',"9"));

    playGame(p1, p2);

    // both should eventually be empty
    assert(p1.begin() == p1.end());
    assert(p2.begin() == p2.end());
}

/* =====================================================
   MAIN TEST RUNNER
===================================================== */

int main() {

    testInsertAndContains();
    testRemove();
    testPrint();

    testIteratorEmpty();
    testIteratorSingle();
    testIteratorMultipleForward();
    testIteratorMultipleReverse();
    testIteratorComparison();

    testPlayCommonCards();
    testPlayOneEmpty();
    testPlayNoCommon();

    cout << "All tests passed!" << endl;

    return 0;
}
