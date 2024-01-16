#include "bstree.h"

// default constructor
BSTree::BSTree()
{

}

int BSTree::Size() const
{
    return Size(root);
}

int BSTree::Size(Node* current) const
{
    if (!current)
    {
        return 0;
    }

    return 1 + Size(current->left) + Size(current->right);
}

// insert function
bool BSTree::Insert(Account* insert)
{
    if (insert == nullptr)
    {
        cerr << "ERROR: Null pointer provided for insertion." << endl;
        return false;
    }

    int insert_account = insert->getAccountID();
    if (insert_account < 0)
    {
        cerr << "ERROR: Account number not valid" << endl;
        return false;
    }

    if (root == nullptr)
    {
        root = new Node;
        root->p_acct = insert;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }
    else
    {
        Node* current = root;
        RecursiveInsert(current, insert);
    }
    return false;
}

bool BSTree::RecursiveInsert(Node* current, Account* insert) 
{
    if (insert->getAccountID() > current->p_acct->getAccountID()) 
    {
        if (current->right == nullptr) 
        {
            Node* insert_tree = new Node();
            insert_tree->p_acct = insert;
            insert_tree->left = nullptr;
            insert_tree->right = nullptr;
            current->right = insert_tree;
            return true;
        } else 
        {
            return RecursiveInsert(current->right, insert);
        }
    } 
    else if (insert->getAccountID() < current->p_acct->getAccountID()) 
    {
        if (current->left == nullptr) 
        {
            Node* insert_tree = new Node();
            insert_tree->p_acct = insert;
            insert_tree->left = nullptr;
            insert_tree->right = nullptr;
            current->left = insert_tree;
            return true;
        } else 
        {
            return RecursiveInsert(current->left, insert);
        }
    } else 
    {
        cerr << "ERROR: Account " << insert->getAccountID() << " is already open. Transaction refused. Try chosing a different number for account." << endl;
        return false;
    }
}

bool BSTree::Retrieve(const int& account_id, Account*& account) const 
{
    if (isEmpty()) 
    {
        cerr << "ERROR: Account list is empty." << endl;
        return false;
    }
    Node* current = root;

    while (current != nullptr) 
    {
        if (account_id == current->p_acct->getAccountID()) 
        {
            account = current->p_acct;
            return true;
        } else if (account_id > current->p_acct->getAccountID()) 
        {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    cerr << "ERROR: Account Number " << account_id << " not found in the tree." << endl;
    account = nullptr;

    return false;
}


void BSTree::Display() const
{
    if (root == NULL)
    {
        cerr << "ERROR: Account list is empty." << endl;
        return;
    }
    Print(root);
} 


void BSTree::Empty()
{
    if (root != nullptr) 
    {
        Empty(root);
    }
    root = nullptr;
}

void BSTree::Empty(Node* current)
{
    if (current != nullptr)
    {
        Empty(current->left);
        Empty(current->right);
        delete current->p_acct;  
        current->p_acct = nullptr; 
        delete current;
    }
}

bool BSTree::isEmpty() const
{
    return (root == NULL);
}

void BSTree::Print(Node* current) const
{
    if (current != nullptr)
    {
        // Traverse the left subtree
        Print(current->left);

        // Print the current account
        cout << *(current-> p_acct) << endl;

        // Traverse the right subtree
        Print(current->right);
    }
}

bool BSTree::Delete(const int& account_id, Account*& account) 
{
    return Delete(account_id, account, root);
}

bool BSTree::Delete(const int& account_id, Account*& account, Node*& current) 
{
    if (current == nullptr) 
    {
        cerr << "ERROR: Account Number " << account_id << " not found in the tree." << endl;
        account = nullptr;
        return false;
    }

    if (account_id < current->p_acct->getAccountID()) 
    {
      
        return Delete(account_id, account, current->left);
    } 
    else if (account_id > current->p_acct->getAccountID()) 
    {
    
        return Delete(account_id, account, current->right);
    } else 
    {
     
        account = current->p_acct;
        if (current->left == nullptr && current->right == nullptr) 
        {
           
            delete current;
            current = nullptr;
        } else if (current->left == nullptr) 
        {
          
            Node* temp = current;
            current = current->right;
            delete temp;
        } else if (current->right == nullptr) 
        {
           
            Node* temp = current;
            current = current->left;
            delete temp;
        } else 
        {
           
            Node* successor = FindSuccessor(current->right);
            current->p_acct = successor->p_acct;
            Delete(successor->p_acct->getAccountID(), account, current->right);
        }
        return true;
    }
}

BSTree::Node* BSTree::FindSuccessor(Node* node) const 
{
    while (node->left != nullptr) 
    {
        node = node->left;
    }
    return node;
}

// destructor
BSTree::~BSTree()
{
	Empty();
}