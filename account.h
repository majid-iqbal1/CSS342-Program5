// Account.h
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <vector>
#include <iostream>
#include "transaction.h"
#include "fund.h"

using namespace std;

// constants variables
const int kInitialDepositAmount = 200;
const int kFundMax = 9;
const int kMoneyMarket = 0;
const int kPrimeMoneyMarket = 1;
const int kLongTermBond= 2;
const int kShortTermBond = 3;

class Account
{

public:
	// constructor
	Account();
	Account(string first_name, string last_name, int account_id);
	~Account();

	// setters & getters
	int getAccountID() const;
	int getBalance(int fund_number)const;
	string getFundName(int fund_number);
	string getFirstName() const;
	string getLastName()const;
	void setFundID(int fund_number);

	// action/verbs
	void AddToAccount(int fund_number, int amount);
	bool SubstractFunds(int fund_number, int amount, Transaction front_trans);
	void RecordTrans(Transaction trans, int fund_number);
	void WithdrawLinked(int primary_fund, int secondary_fund, int amount);
	void PrintHistory();
	void PrintFundHistory(int fund_number);
	void error(int amount, const string& first_name, const string& last_name, int fund_number, bool transfer);

	// ostream operator
	friend ostream& operator << (ostream &out, Account& account);

private:
	// data members
	string first_name_;
	string last_name_;
	int account_id_;
	int fund_id_;
	Fund array_fund_[kFundMax];
};
#endif