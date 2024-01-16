#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"
#include <iostream>
using namespace std;

#

class BSTree
{
public:
    // constuctor
    BSTree();
    ~BSTree();

    // verb/actions
    bool Insert(Account* insert);
    bool Retrieve(const int& account_id, Account*& account) const;
    void Display() const;
    bool Delete(const int& account_id, Account*& account);
    void Empty();
    bool isEmpty() const;
    int Size() const;

private:
    // Node struct to create nodes for BST
    struct Node
    {
        Node* left = nullptr;
        Node* right = nullptr;
        Account* p_acct;
    };
    // helper functions to retrieve, delete and find successor, print, empty, insert, and tell size of nodes.
    Node* root = nullptr;
    Node* FindSuccessor(Node* current) const;
    bool RecursiveInsert(Node* cur, Account* insert);
    void Print(Node* print_node) const;
    bool Delete(const int& account_id, Account*& account, Node*& current);
    void Empty(Node* current);
    int Size(Node* current) const;
};
#endif
