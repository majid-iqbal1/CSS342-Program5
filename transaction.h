#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <ostream>
using namespace std;

class Transaction
{
public:
	// constructors
	Transaction();
	~Transaction();
	Transaction(char type, string first_name, string last_name, int account_number);
	Transaction(char type, int account_number, int fund_number, int amount);
	Transaction(char type, int account_number, int fund_number, int transfer_account_number, int transfer_fund_number, int amount);
	Transaction(char type, int account_number);
	Transaction(char type, int account_number, int fund_number);

	//These Construtors create a transaction that failed to process
	Transaction(char type, int account_number, int fund_number, int transfer_account_number, int transfer_fund_number, int amount, string fail_string);
	Transaction(char type, int account_number, int fund_number, int amount, string fail);

	bool isFailed();
	string getFail() const;
	char getTransactionType() const;
	string getFirstName() const;
	string getLastName() const;
	int getAccountID() const;
	int getFundID() const;
	int getTransferAccountID() const;
	int getTransferFundID() const;
	int getAmount() const;
	friend ostream & operator<<(ostream &out, const Transaction &trans);

private:
	char transaction_type_;
	string first_name_;
	string last_name_;
	string fail_;
	int account_id_, fund_id_, transfer_account_id_, transfer_fund_id_, amount_;
};

#endif
