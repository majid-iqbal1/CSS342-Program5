#include "fund.h"

Fund::Fund()
{
	balance_ = 0;
}

bool Fund::addAmount(int amount_add)
{
	balance_ += amount_add;
	return true;
}

bool Fund::subtractAmount(int amount_sub)
{
	balance_ -= amount_sub;
	return true;
}

bool Fund::balanceCheck(int amount_sub)
{
	if (balance_ >= amount_sub)
	{
		return true;
	}
	return false;
}


bool Fund::recordTransaction(Transaction trans)
{
	history_.push_back(trans);
	return true;
}

void Fund::printHistory()
{
	if (history_.size() == 0)
	{
		return;
	}
	else
	{
		cout << fund_name_ << ": $" << balance_ << endl;
		for (int i = 0; i < history_.size(); i++)
		{
			cout << " " << history_[i];
		}
	}
}

void Fund::printHistoryOfFund()
{
	for (int i = 0; i < history_.size(); i++)
	{	
		cout << " " << history_[i];
	}
}

void Fund::setName(string name)
{
	this->fund_name_ = name;
}

int Fund::getBalance() const
{
	return balance_;
}

string Fund::getName() const
{
	return fund_name_;
}