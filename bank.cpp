#include "bank.h"

JollyBanker::JollyBanker()
{

}

bool JollyBanker::ReadTransactions(const string& file_name) 
{
    ifstream in(file_name);
    if (!in) {
        cout << "Cannot Open file: " << file_name << endl;
        return false;
    }

    string read_line;
    while (getline(in, read_line)) {
        if (read_line.empty()) {
            break;
        }
        istringstream parse_line(read_line);
        char transaction_type;
        parse_line >> transaction_type;

        switch (transaction_type) {
            case 'O':
            case 'o': {
                int account_id;
                string last_name, first_name;
                parse_line >> account_id >> last_name >> first_name;

                // Check if both last_name and first_name are provided
                if (last_name.empty() || first_name.empty()) {
                    cerr << "ERROR: Both last name and first name must be provided when opening an account." << endl;
                    break;  // Skip further processing for this transaction
                }

                Transaction add_queue(transaction_type, last_name, first_name, account_id);
                q_transaction_.push(add_queue);
                break;
            }

            case 'D':
            case 'd':
            case 'W':
            case 'w': {
                int account_id, fund_id, amount;
                parse_line >> account_id >> fund_id >> amount;
                Transaction add_queue(transaction_type, account_id, fund_id, amount);
                q_transaction_.push(add_queue);
                break;
            }
            case 'T':
            case 't': {
                int account_id, from_Fund, transfer_account, to_fund, amount;
                parse_line >> account_id >> from_Fund >> transfer_account >> to_fund >> amount;
                Transaction add_queue(transaction_type, account_id, from_Fund, transfer_account, to_fund, amount);
                q_transaction_.push(add_queue);
                break;
            }
            case 'H':
            case 'h':
            case 'F':
            case 'f': {
                int account_id, fund_id;
                parse_line >> account_id;
                if (transaction_type == 'F' || transaction_type == 'f') {
                    parse_line >> fund_id;
                }
                Transaction add_queue(transaction_type, account_id, fund_id);
                q_transaction_.push(add_queue);
                break;

            }
            default:
                cerr << "ERROR: Invalid transaction type: '" << transaction_type << "'. The valid transaction types are: O: Open an account,  D: Deposit assets into a fund, W: Withdraw assets from a fund, T: Transfer assets between funds,  H: Display the history of all transactions, F: Display the history for all transactions of a given fund. " << endl;
                break;
        }
    }

    // Close the file after processing
    in.close();

    return true;
}

void JollyBanker::ExecuteTransactions()
{
    while (!q_transaction_.empty())
    {
        Transaction front_transaction = q_transaction_.front();
        char transaction_type = front_transaction.getTransactionType();

        switch (transaction_type)
        {
            case 'O':
            case 'o':
            {
                Account* account = new Account(front_transaction.getFirstName(), front_transaction.getLastName(), front_transaction.getAccountID());
                account_list_.Insert(account);
                break;
            }
            case 'D':
            case 'd':
            {
                // Process deposit transaction
                int account_number = front_transaction.getAccountID();
                int fund_number = front_transaction.getFundID();
                int amount_add = front_transaction.getAmount();
                Account* account;

                if (amount_add < 0)
                {
                    cerr << "ERROR: Cannot deposit a negative amount to Account " << account_number << " to Fund " << fund_number << "." << endl;
                    break; // Skip further processing for this transaction
                }

                if (account_list_.Retrieve(account_number, account))
                {
                    account->AddToAccount(fund_number, amount_add);
                    account->RecordTrans(front_transaction, fund_number);
                }
                else
                {
                    cerr << "ERROR: Account " << account_number << " not found for deposit." << endl;
                }
                break;
            }

            case 'W':
            case 'w':
            {
                // Process withdrawal transaction
                int account_number = front_transaction.getAccountID();
                int fund_number = front_transaction.getFundID();
                int amount_sub = front_transaction.getAmount();
                Account* account;

                if (amount_sub < 0)
                {
                    cerr << "ERROR: Cannot withdraw a negative amount from Account " << account_number << " to Fund " << fund_number << "." << endl;
                    break; // Skip further processing for this transaction
                }

                if (account_list_.Retrieve(account_number, account))
                {
                    account->SubstractFunds(fund_number, amount_sub, front_transaction);
                }
                else
                {
                    cerr << "ERROR: Account " << account_number << " not found for withdrawal." << endl;
                }
                break;
            }
            case 'T':
            case 't':
            {
                int account_number = front_transaction.getAccountID();
                int transfer_acct = front_transaction.getTransferAccountID();
                int fund_number = front_transaction.getFundID();
                int transfer_fund = front_transaction.getTransferFundID();
                int amount_sub = front_transaction.getAmount();
                Account* from;
                Account* to;

                if (amount_sub < 0)
                {
                    cerr << "ERROR: Cannot transfer a negative amount from Account " << account_number << " to Fund " << fund_number << " to Account " << transfer_acct << " Fund " << transfer_fund << "." << endl;
                    break; 
                }

                // Retrieve accounts during the execution phase
                if (account_list_.Retrieve(account_number, from) && account_list_.Retrieve(transfer_acct, to)) {
                    if (from->SubstractFunds(fund_number, amount_sub, front_transaction)) {
                        to->AddToAccount(transfer_fund, amount_sub);
                        to->RecordTrans(front_transaction, transfer_fund);
                    } else {
                        cerr << "ERROR: Not enough funds to transfer $" << amount_sub << " from account ID " << from->getAccountID()  << "'s "<< from->getFundName(fund_number) << " to account ID " << to->getAccountID()<< "'s " << to->getFundName(transfer_fund) << endl;
                        Transaction addToHistory('T', account_number, fund_number, amount_sub, transfer_acct, transfer_fund, "(Failed)");
                        from->RecordTrans(addToHistory, fund_number);
                        break;
                    }
                } 
                break;
            }

            case 'F':
            case 'f':
            {
                // Process fund history transaction
                int account_number = front_transaction.getAccountID();
                int fund_number = front_transaction.getFundID();
                Account* account;
                if (account_list_.Retrieve(account_number, account))
                {
                    account->PrintFundHistory(fund_number);
                    cout << endl;
                }
                else
                {
                    cerr << "ERROR: Account " << account_number << " not found for fund history." << endl;
                }
                break;
            }
            case 'H':
            case 'h':
            {
                // Process transaction history transaction
                int account_number = front_transaction.getAccountID();

                Account* account;
                if (account_list_.Retrieve(account_number, account))
                {
                    account->PrintHistory();
                    cout << endl;
                }
                else
                {
                    cerr << "ERROR: Account " << account_number << " not found for transaction history." << endl;
                }
                break;
            }

            default:
                cerr << "ERROR: Invalid transaction type: '" << transaction_type << "'. The valid transaction types are: O: Open an account,  D: Deposit assets into a fund, W: Withdraw assets from a fund, T: Transfer assets between funds,  H: Display the history of all transactions, F: Display the history for all transactions of a given fund. " << endl;
                break;
        }

        q_transaction_.pop();
    }
}

void JollyBanker::Display()
{
    cout << endl;
	cout << "-------------------------------------------" << endl;
	cout << "             Account Balances              " << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
	account_list_.Display();
}

JollyBanker::~JollyBanker()
{}