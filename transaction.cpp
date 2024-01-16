#include "transaction.h"
using namespace std;

Transaction::Transaction()
{}

Transaction::~Transaction()
{}

Transaction::Transaction(char type, string first_name, string last_name, int account_number)
{
	this->transaction_type_ = type;
	this->first_name_ = first_name;
	this->last_name_ = last_name;
	this->account_id_ = account_number;
}
Transaction::Transaction(char type, int account_number, int fund_number, int amount)
{
    this->transaction_type_ = type;
    this->account_id_ = account_number;
    this->fund_id_ = fund_number;
    this->amount_ = amount;
}


Transaction::Transaction(char type, int account_number, int fund_number, int amount, string fail)
{
	this->transaction_type_ = type;
	this->account_id_ = account_number;
	this->fund_id_ = fund_number;
	this->amount_ = amount;
	this->fail_ = fail;
}

Transaction::Transaction(char type, int account_number, int fund_number, int transfer_account_number, int transfer_fund_number, int amount)
{
	this->transaction_type_ = type;
	this->account_id_ = account_number;
	this->fund_id_ = fund_number;
	this->transfer_account_id_ = transfer_account_number;
	this->transfer_fund_id_ = transfer_fund_number;
	this->amount_ = amount;
}

Transaction::Transaction(char type, int account_number, int fund_number, int transfer_account_number, int transfer_fund_number, int amount, string fail_string)
{
	this->transaction_type_ = type;
	this->account_id_ = account_number;
	this->fund_id_ = fund_number;
	this->transfer_account_id_ = transfer_account_number;
	this->transfer_fund_id_ = transfer_fund_number;
	this->amount_ = amount;
	this->fail_ = fail_string;
}


Transaction::Transaction(char type, int account_number)
{
	this->transaction_type_ = type;
	this->account_id_ = account_number;
}

Transaction::Transaction(char type, int account_number, int fund_number)
{
	this->transaction_type_ = type;
	this->account_id_ = account_number;
	this->fund_id_ = fund_number;

}
//Checks if the string fail is empty, if it is not empty the transaction failed to process
bool Transaction::isFailed()
{
	if (fail_.empty()) 
	{
		return true;
	}
	return false;
}

string Transaction::getFail() const {
    return fail_;
}

char Transaction::getTransactionType() const
{
	return transaction_type_;
}

string Transaction::getFirstName() const
{
	return first_name_;
}

string Transaction::getLastName() const
{
	return last_name_;
}

int Transaction::getAccountID() const
{
	return account_id_;
}

int Transaction::getAmount() const
{
	return amount_;
}

int Transaction::getFundID() const
{
	return fund_id_;
}

int Transaction::getTransferAccountID() const
{
	return transfer_account_id_;
}

int Transaction::getTransferFundID() const
{
	return transfer_fund_id_;
}

ostream & operator<<(ostream & out, const Transaction & trans)
{
	if (trans.fail_.empty())
	{
		if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'd' || trans.getTransactionType() == 'W' || trans.getTransactionType() == 'w')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << " " << trans.getFundID() << " " << trans.getAmount();
		}
		else if (trans.getTransactionType() == 'T' || trans.getTransactionType() == 't')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << " " << trans.getFundID() << " " << trans.getTransferAccountID() << " "<< trans.getTransferFundID() << " " << trans.getAmount();
		}
		else
		{

		}
	}
	else
	{
		if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'd' || trans.getTransactionType() == 'W' || trans.getTransactionType() == 'w')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << " " << trans.getFundID() << " " << trans.getAmount() << " (FAILED)";
		}
		else if (trans.getTransactionType() == 'T' || trans.getTransactionType() == 't')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << " " << trans.getFundID() << " " << trans.getTransferFundID() << " " << trans.getAmount() << " " << trans.getTransferAccountID() << " (FAILED)";
		}
		else
		{

		}

	}
	return out << endl;

}