#include "bank.h"

// main designed to take one input text file to then read the transaction by line then excute and display them
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    JollyBanker jollyBanker;
    if (!jollyBanker.ReadTransactions(argv[1])) {
        cerr << "Error reading transactions from file: " << argv[1] << ". Please check the file format. It must be a text file." << endl;
        return 1;
    }

    jollyBanker.ExecuteTransactions();
    jollyBanker.Display();

    return 0;
}
