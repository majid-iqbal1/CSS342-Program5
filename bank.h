#ifndef BANK_H_
#define BANK_H_

#include<queue>
#include "bstree.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class JollyBanker
{
public:
	// constructor
	JollyBanker();
	~JollyBanker();

	// actions/verbs
	bool ReadTransactions(const string& file_name);
	void ExecuteTransactions();
	void Display();
	
private:
	// data members queue and BSTree
	queue<Transaction> q_transaction_;
	BSTree account_list_;
};

#endif
