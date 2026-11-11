#include <iostream>
using namespace std;

class SavingsAccount {
private:                       // data is private: only member functions can change it
    int accNo;
    double balance;
    double trans[10];          // last 10 transactions (+ deposit, - withdraw)
    int count;
    void record(double amt);   // helper, defined outside

public:
    // defined INSIDE the class
    SavingsAccount(int no, double bal) { accNo = no; balance = bal; count = 0; }
    double getBalance() { return balance; }

    // defined OUTSIDE the class using ::
    void deposit(double amt);
    void withdraw(double amt);
    void miniStatement();
};

void SavingsAccount::record(double amt)
{
    if (count == 10) {                       // 11th transaction: array is full
        for (int i = 1; i < 10; i++)         // shift left, oldest is discarded
            trans[i - 1] = trans[i];
        count = 9;
    }
    trans[count++] = amt;
}

void SavingsAccount::deposit(double amt)
{
    balance += amt;
    record(amt);
}

void SavingsAccount::withdraw(double amt)
{
    if (amt > balance) {
        cout << "Withdraw " << amt << " failed: insufficient balance" << endl;
        return;
    }
    balance -= amt;
    record(-amt);
}

void SavingsAccount::miniStatement()
{
    cout << "--- Mini Statement, Account " << accNo << " ---" << endl;
    for (int i = 0; i < count; i++) {
        if (trans[i] > 0) cout << "Deposit  " << trans[i] << endl;
        else              cout << "Withdraw " << -trans[i] << endl;
    }
    cout << "Balance: " << balance << endl;
}

int main()
{
    SavingsAccount acc(1001, 5000);
    for (int i = 1; i <= 11; i++)       // 11 deposits: 100, 200 ... 1100
        acc.deposit(i * 100);
    acc.withdraw(250);                  // 12th transaction
    acc.withdraw(100000);               // fails, not recorded
    acc.miniStatement();                // shows only the last 10
    return 0;
}
