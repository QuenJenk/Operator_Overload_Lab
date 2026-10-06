#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <utility>

// Quentin Jenkins 10/5/26
// Operator Overload Lab

// Manages customer details and balances using dynamic memory
class BankAccount {
    std::string accountNumber;
    std::string* accountHolderName;
    double* balance;

public:
    BankAccount() {
        accountNumber = "";
        accountHolderName = new std::string("");
        balance = new double(0.0);
    }

    BankAccount(std::string accNum, std::string name, double initialBalance) {
        accountNumber = std::move(accNum);
        accountHolderName = new std::string(std::move(name));
        balance = new double(initialBalance >= 0.0 ? initialBalance : 0.0);
    }

    // Rule of 3: Copy Constructor
    BankAccount(const BankAccount& other) {
        accountNumber = other.accountNumber;
        accountHolderName = new std::string(*other.accountHolderName);
        balance = new double(*other.balance);
    }

    // Rule of 3: Copy Assignment Operator (Exception Safe)
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            std::string* newName = new std::string(*other.accountHolderName);
            double* newBalance = new double(*other.balance);

            delete accountHolderName;
            delete balance;

            accountNumber = other.accountNumber;
            accountHolderName = newName;
            balance = newBalance;
        }
        return *this;
    }

    // Rule of 3: Destructor
    ~BankAccount() {
        delete accountHolderName;
        delete balance;
    }

    std::string getAccountNumber() const { return accountNumber; }
    std::string getAccountHolderName() const { return *accountHolderName; }
    double getBalance() const { return *balance; }

    void setAccountHolderName(const std::string& name) {
        if (!name.empty()) {
            *accountHolderName = name;
        }
    }

    // Deposit funds
    BankAccount& operator+=(double amount) {
        if (amount > 0) {
            *balance += amount;
        }
        return *this;
    }

    // Withdraw funds
    BankAccount& operator-=(double amount) {
        if (amount > 0 && amount <= *balance) {
            *balance -= amount;
        }
        return *this;
    }

    // Compare unique account numbers
    bool operator==(const BankAccount& other) const {
        return this->accountNumber == other.accountNumber;
    }

    // Compare balances
    bool operator<(const BankAccount& other) const {
        return *this->balance < *other.balance;
    }

    // Compare balances
    bool operator>(const BankAccount& other) const {
        return *this->balance > *other.balance;
    }

    static void printAccount(const BankAccount& account) {
        std::cout << "Acc No: " << account.getAccountNumber()
                  << " | Holder: " << account.getAccountHolderName()
                  << " | Balance: $" << account.getBalance() << "\n";
    }

    static BankAccount createAccountFromInput();
};

double getValidDouble(const std::string& prompt);
std::string getValidString(const std::string& prompt);

BankAccount BankAccount::createAccountFromInput() {
    std::string accNum = getValidString("Enter unique Account Number: ");
    std::string name = getValidString("Enter Account Holder Name: ");
    double initialBalance = getValidDouble("Enter Initial Balance: ");
    while (initialBalance < 0) {
        std::cout << "Initial balance cannot be negative.\n";
        initialBalance = getValidDouble("Enter Initial Balance: ");
    }
    return BankAccount(accNum, name, initialBalance);
}

int findAccountIndex(const std::vector<BankAccount>& accounts, const std::string& accNum) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == accNum) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {
    std::vector<BankAccount> bank;
    int choice = 0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== Welcome to the Banking Management System ===\n";

    do {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Create New Account (via Static Factory)\n";
        std::cout << "2. Deposit Funds (via +=)\n";
        std::cout << "3. Withdraw Funds (via -=)\n";
        std::cout << "4. Update Account Holder Name\n";
        std::cout << "5. Display All Accounts (via Static Print)\n";
        std::cout << "6. Find Wealthiest & Poorest Accounts (via > / <)\n";
        std::cout << "7. Exit\n";

        std::cout << "Enter your choice (1-7): ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                BankAccount newAcc = BankAccount::createAccountFromInput();

                bool duplicate = false;
                for (const auto &acc: bank) {
                    if (acc == newAcc) {
                        duplicate = true;
                        break;
                    }
                }

                if (duplicate) {
                    std::cout << "Error: An account with this number already exists!\n";
                } else {
                    bank.push_back(newAcc);
                    std::cout << "Account created successfully!\n";
                }
                break;
            }
            case 2: {
                std::string accNum = getValidString("Enter Account Number: ");
                int index = findAccountIndex(bank, accNum);

                if (index == -1) {
                    std::cout << "Account not found.\n";
                } else {
                    double amount = getValidDouble("Enter deposit amount: ");
                    if (amount > 0) {
                        bank[index] += amount;
                        std::cout << "Deposit successful! New Balance: $" << bank[index].getBalance() << "\n";
                    } else {
                        std::cout << "Deposit failed. Amount must be greater than 0.\n";
                    }
                }
                break;
            }
            case 3: {
                std::string accNum = getValidString("Enter Account Number: ");
                int index = findAccountIndex(bank, accNum);

                if (index == -1) {
                    std::cout << "Account not found.\n";
                } else {
                    double amount = getValidDouble("Enter withdrawal amount: ");
                    if (amount > 0 && amount <= bank[index].getBalance()) {
                        bank[index] -= amount;
                        std::cout << "Withdrawal successful! New Balance: $" << bank[index].getBalance() << "\n";
                    } else {
                        std::cout << "Withdrawal failed. Check if amount is valid and you have sufficient funds.\n";
                    }
                }
                break;
            }
            case 4: {
                std::string accNum = getValidString("Enter Account Number: ");
                int index = findAccountIndex(bank, accNum);

                if (index == -1) {
                    std::cout << "Account not found.\n";
                } else {
                    std::string newName = getValidString("Enter New Account Holder Name: ");
                    bank[index].setAccountHolderName(newName);
                    std::cout << "Account name updated successfully.\n";
                }
                break;
            }
            case 5: {
                if (bank.empty()) {
                    std::cout << "No accounts registered in the system.\n";
                } else {
                    std::cout << "\nRegistered Accounts\n";
                    for (const auto &account: bank) {
                        BankAccount::printAccount(account);
                    }
                }
                break;
            }
            case 6: {
                if (bank.size() < 2) {
                    std::cout << "At least two accounts are needed to perform a balance comparison.\n";
                    break;
                }
                size_t wealthiestIdx = 0;
                size_t poorestIdx = 0;

                for (size_t i = 1; i < bank.size(); ++i) {
                    if (bank[i] > bank[wealthiestIdx]) wealthiestIdx = i;
                    if (bank[i] < bank[poorestIdx]) poorestIdx = i;
                }

                std::cout << "\n--- Financial Ranking Comparison ---\n";
                std::cout << "Highest Balance: ";
                BankAccount::printAccount(bank[wealthiestIdx]);
                std::cout << "Lowest Balance:  ";
                BankAccount::printAccount(bank[poorestIdx]);
                break;
            }
            case 7:
                std::cout << "Thank you for using the Banking Management System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}

// User input validation for numeric types
double getValidDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid numeric input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// User input validation for non-empty text
std::string getValidString(const std::string& prompt) {std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}
