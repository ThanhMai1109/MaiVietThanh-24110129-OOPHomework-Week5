#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account;
class SavingsAccount;
class Transaction;
class Customer;

class Transaction
{
private:
    string type;
    string date;
    double ammount;

public:
    Transaction(string t, string d, double a) : type(t), date(d), ammount(a) {}
    string getType()
    {
        return type;
    }
    string getDate()
    {
        return date;
    }
    double getAmmount()
    {
        return ammount;
    }
    void displayTransactionInfo()
    {
        cout << "Transaction type: " << type << endl;
        cout << "Ammount: " << ammount << endl;
        cout << "Date: " << date << endl;
    }
};

class Account
{
protected:
    string accountNumber;
    double balance;
    string ownerName;
    vector<Transaction *> transactionHistory;

public:
    Account(string a, double b, string o) : accountNumber(a), balance(b), ownerName(o) {}
    string getAccountNumber()
    {
        return accountNumber;
    }
    double getBalance()
    {
        return balance;
    }
    string getOwnerName()
    {
        return ownerName;
    }
    virtual void deposit(double ammount)
    {
        balance += ammount;
        transactionHistory.push_back(new Transaction("Deposit", "2024-01-01", ammount));
    }
    virtual void withdraw(double ammount)
    {
        if (ammount <= balance)
        {
            balance -= ammount;
            transactionHistory.push_back(new Transaction("Withdraw", "2024-01-01", ammount));
        }
        else
        {
            cout << "The account balance is not enough" << endl;
        }
    }
    virtual void displayAccountInfo()
    {
        cout << "Account Number: " << accountNumber << endl
             << "Owner: " << ownerName << endl
             << "Balance: " << balance << endl;
    }
};

class SavingsAccount : public Account
{
private:
    double increaseRate;

public:
    SavingsAccount(string a, double b, string o, double r) : Account(a, b, o), increaseRate(r) {}
    void receiveMoney(double ammount)
    {
        balance += ammount * (1 + increaseRate);
    }
    void deposit(double ammount) override
    {
        balance += ammount * (1 + increaseRate);
        transactionHistory.push_back(new Transaction("Deposit (Savings)", "2024-01-01", ammount));
    }
    void withdraw(double ammount) override
    {
        if (ammount <= balance)
        {
            balance -= ammount;
            transactionHistory.push_back(new Transaction("Withdraw (Savings)", "2024-01-01", ammount));
        }
        else
            cout << "The account balance is not enough" << endl;
    }
    void displayAccountInfo() override
    {
        cout << "Savings Account Number: " << accountNumber << endl
             << "Owner: " << ownerName << endl
             << "Balance: " << balance << endl
             << "Increase Rate: " << increaseRate << endl;
    }
};

class Customer
{
private:
    string name;
    int id;
    vector<Account *> accounts;

public:
    Customer(string n, int i) : name(n), id(i) {}
    void addAccount(Account *a)
    {
        accounts.push_back(a);
    }
    string getName()
    {
        return name;
    }
    int getId()
    {
        return id;
    }
    void displayCustomerInfo()
    {
        cout << "Customer Name: " << name << endl;
        cout << "Customer ID: " << id << endl;
        cout << "Accounts: " << endl;
        for (const auto &a : accounts)
        {
            a->displayAccountInfo();
            cout << "------------------" << endl;
        }
    }
};

int main() // Testcase được tạo bởi ChatGPT
{
    // Tạo khách hàng
    Customer c1("Alice", 1001);
    Customer c2("Bob", 1002);

    // Tạo tài khoản thường
    Account *acc1 = new Account("ACC001", 500.0, "Alice");
    c1.addAccount(acc1);

    // Tạo tài khoản tiết kiệm với lãi suất 5%
    SavingsAccount *sav1 = new SavingsAccount("SAV001", 1000.0, "Alice", 0.05);
    c1.addAccount(sav1);

    // Tạo tài khoản khác cho Bob
    Account *acc2 = new Account("ACC002", 800.0, "Bob");
    c2.addAccount(acc2);

    // Thực hiện giao dịch với acc1
    cout << "\n--- Transactions on Alice's Normal Account ---" << endl;
    acc1->deposit(200);  // Nạp tiền
    acc1->withdraw(100); // Rút tiền
    acc1->displayAccountInfo();

    // Thực hiện giao dịch với sav1
    cout << "\n--- Transactions on Alice's Savings Account ---" << endl;
    sav1->deposit(500);  // Nạp tiền (có lãi suất 5%)
    sav1->withdraw(300); // Rút tiền
    sav1->displayAccountInfo();

    // Thông tin khách hàng
    cout << "\n--- Customer Info ---" << endl;
    c1.displayCustomerInfo();
    c2.displayCustomerInfo();

    // Kiểm tra Transaction riêng lẻ
    cout << "\n--- Example Transaction ---" << endl;
    Transaction t1("Transfer", "2025-09-19", 150.0);
    t1.displayTransactionInfo();

    // Dọn bộ nhớ
    delete acc1;
    delete sav1;
    delete acc2;

    return 0;
}