# Object_Classes_Lab

A C++ class for simulating a bank's financial database.

## Data Dictionary

| Attribute           | Data Type     | Description                    |
|---------------------|---------------|--------------------------------|
| `accountNumber`     | `std::string` | Unique identifier for the bank account. |
| `accountHolderName` | `std::string` | The full name of the account owner. |
| `balance`           | `double`      | The current financial balance stored in the account. |

## Methods List

| Method Signature             | Return Type   | Description               |
|------------------------------|---------------|---------------------------|
| `BankAccount()`                     | (Constructor) | Default constructor.      |
| `BankAccount(accNum, name, initialBalance)`  | (Constructor) | Parameterized constructor.|
| `getAccountNumber() const`           | `std::string` | Gets the account number.    |
| `getAccountHolderName() const`          | `std::string` | Gets the account holder's name.   |
| `getBalance() const`        | `double`        | Gets the current account balance.      |
| `setAccountHolderName(name)`                 | `void`        | Updates the account holder's name.      |
| `deposit(amount)`               | `bool`        | Deposits funds into the account.      |
| `withdraw(amount)`               | `bool`        | Withdraws funds from the account.      |