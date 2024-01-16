#include "account.h"

// default constructor
Account::Account()
{
    account_id_ = 0;
}

// constructor
Account::Account(string first_name, string last_name, int account_id)
{
    this->first_name_ = first_name;
    this->last_name_ = last_name;
    this->account_id_ = account_id;
    // adding fund names in the list
    string fund_names[] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "International Fund"};
    for (int i = 0; i < kFundMax; i++)
    {
        array_fund_[i].setName(fund_names[i]);
    }

    // Deposit 200 into the Money Market fund
    array_fund_[kMoneyMarket].addAmount(kInitialDepositAmount);
}

//getter
int Account::getAccountID() const
{
    return account_id_;
}

// adding money to fund
void Account::AddToAccount(int fund_number, int amount)
{
    array_fund_[fund_number].addAmount(amount);
}

// The SubstractFunds function is checked and then used when subtracting money b/w two linked accounts.
bool Account::SubstractFunds(int fund_number, int amount, Transaction front_trans)
{
    if (amount < 0)
    {
        return false;
    }

    if (fund_number == kMoneyMarket || fund_number == kPrimeMoneyMarket || fund_number == kLongTermBond || fund_number == kShortTermBond)
    {
        if (fund_number == kMoneyMarket || fund_number == kPrimeMoneyMarket)
        {
            if (array_fund_[fund_number].balanceCheck(amount))
            {
                array_fund_[fund_number].subtractAmount(amount);
                array_fund_[fund_number].recordTransaction(front_trans);
                return true;
            }
            else if (array_fund_[kMoneyMarket].getBalance() + array_fund_[kPrimeMoneyMarket].getBalance() >= amount)
            {
                WithdrawLinked(kMoneyMarket, kPrimeMoneyMarket, amount);
                return true;
            }
            else
            {
                error(amount, getLastName(), getFirstName(), fund_number, true);
                return false;
            }
        }
        else if (fund_number == kLongTermBond || fund_number == kShortTermBond)
        {
            if (array_fund_[fund_number].balanceCheck(amount))
            {
                array_fund_[fund_number].subtractAmount(amount);
                array_fund_[fund_number].recordTransaction(front_trans);
                return true;
            }
            else if (array_fund_[kLongTermBond].getBalance() + array_fund_[kShortTermBond].getBalance() >= amount)
            {
                WithdrawLinked(kLongTermBond, kShortTermBond, amount);
                return true;
            }
            else
            {
                error(amount, getLastName(), getFirstName(), fund_number, true);
                return false;
            }
        }
    }
    else
    {
        if (array_fund_[fund_number].balanceCheck(amount))
        {
            array_fund_[fund_number].subtractAmount(amount);
            array_fund_[fund_number].recordTransaction(front_trans);
            return true;
        }
        else
        {
            error(amount, getLastName(), getFirstName(), fund_number, false);
            return false;
        }
    }

    return false;
}

// The WithdrawLinked function is used when withdrawing transfering money b/w two linked accounts.
void Account::WithdrawLinked(int primary_fund, int secondary_fund, int amount)
{
    int bal_available_primary = array_fund_[primary_fund].getBalance();
    int bal_available_secondary = array_fund_[secondary_fund].getBalance();

    if (bal_available_primary >= amount)
    {
        array_fund_[primary_fund].subtractAmount(amount);
        Transaction add_history('W', getAccountID(), primary_fund, amount);
        array_fund_[primary_fund].recordTransaction(add_history);
    }
    else if (bal_available_primary + bal_available_secondary >= amount)
    {
        array_fund_[primary_fund].subtractAmount(bal_available_primary);
        Transaction add_history('W', getAccountID(), primary_fund, bal_available_primary);
        array_fund_[primary_fund].recordTransaction(add_history);

        amount -= bal_available_primary;
        array_fund_[secondary_fund].subtractAmount(amount);
        Transaction add_history2('W', getAccountID(), secondary_fund, amount);
        array_fund_[secondary_fund].recordTransaction(add_history2);
    }
    else if (bal_available_primary >= 0 && bal_available_secondary >= amount)
    {
        array_fund_[secondary_fund].subtractAmount(amount);
        Transaction add_history('W', getAccountID(), secondary_fund, amount);
        array_fund_[secondary_fund].recordTransaction(add_history);
    }
    else
    {
        error(amount, getLastName(), getFirstName(), secondary_fund, false);
        Transaction add_history('W', getAccountID(), secondary_fund, amount, "Failed");
        array_fund_[secondary_fund].recordTransaction(add_history);
    }
}

// error function throw cerr if transfer/withdraw fails.
void Account::error(int amount, const string &first_name, const string &last_name, int fund_number, bool transfer)
{
    static bool already_printed_error = false; 

    if (!already_printed_error)
    {
        cerr << "ERROR: Not enough funds to " << (transfer ? "transfer" : "withdraw") << " $" << amount << " from " << last_name << " " << first_name << "'s " << getFundName(fund_number) << endl;
        Transaction addToHistory('W', getAccountID(), fund_number, amount, "Failed");
        array_fund_[fund_number].recordTransaction(addToHistory);

        if (transfer)
        {
            already_printed_error = true; 
        }
    }
}

// this method record transactions
void Account::RecordTrans(Transaction trans, int fund_number)
{
    array_fund_[fund_number].recordTransaction(trans);
}

// this method prints history
void Account::PrintHistory()
{
    cout << "Transaction History for " << last_name_ << " " << first_name_ << " "
         << "By Fund." << endl;
    for (int i = 0; i < kFundMax; i++)
    {
        array_fund_[i].printHistory();
    }
}

// this method prints fund history
void Account::PrintFundHistory(int fund_id)
{
    cout << "Transaction History for " << last_name_ << " " << first_name_ << " " << getFundName(fund_id) << " $" << getBalance(fund_id) << endl;
    array_fund_[fund_id].printHistoryOfFund();
}

// setter for fund ID
void Account::setFundID(int fund_number)
{
    this->fund_id_ = fund_number;
}

// getter
int Account::getBalance(int fund_number) const
{
    return array_fund_[fund_number].getBalance();
}

// getter
string Account::getFundName(int fund_number)
{
    return array_fund_[fund_number].getName();
}

// getter
string Account::getFirstName() const
{
    return first_name_;
}

// getter
string Account::getLastName() const
{
    return last_name_;
}

// ostream operator
ostream &operator<<(ostream &out, Account &account)
{
    out << account.getLastName() << " " << account.getFirstName() << " Account ID: " << account.getAccountID() << endl;
    for (int i = 0; i < kFundMax; i++)
    {
        out << "    " << account.getFundName(i) << ": $" << account.getBalance(i) << endl;
    }

    return out;
}

// destructor
Account::~Account()
{}
