#ifndef FUND_H
#define FUND_H

#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>

class Fund
{
public:
	// constructors
	Fund();

	// setter & getters
	void setName(string name);
	int getBalance() const;
	string getName() const;

	// Action/verbs
	bool addAmount(int amount_add);
	bool subtractAmount(int amount_sub);
	bool balanceCheck(int amount_sub);
	bool recordTransaction(Transaction trans);
	void printHistoryOfFund();
	void printHistory();

private:
	// data members
	string fund_name_;
	int balance_ = 0;
	vector<Transaction> history_;
};

#endif 