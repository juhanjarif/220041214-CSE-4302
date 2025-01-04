#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class account {
protected:
    string accountNo;
    string accountName;
    float balance;

public:
    account(const string& name, float initialBalance) : accountName(name), balance(initialBalance){}

    virtual void description() const{
        cout << "General account.\n";
    }

    void setBalance(float amount){
        balance = amount;
    }

    float getBalance() const{
        return balance;
    }

    void setAccountName(const string& name){
        accountName = name;
    }

    string getAccountName() const{
        return accountName;
    }

    string getAccountNo() const{
        return accountNo;
    }
};

class currentAccount : public account{
protected:
    static int nextAccountNo;
    const static int serviceCharge = 100;

public:
    currentAccount(const string& name, float initialBalance) : account(name, initialBalance) {
        stringstream ss;
        ss << 100 << nextAccountNo++;
        accountNo = ss.str();
    }

    void description() const override{
        cout << "Current Account with service charge: " << serviceCharge << ".\n";
    }
};

int currentAccount::nextAccountNo = 1;

class savingsAccount : public account{
protected:
    static int nextAccountNo;
    float interestRate;
    float monthlyDepositAmount;

public:
    savingsAccount(const string& name, float initialBalance, float rate, float depositAmount) : account(name, initialBalance), interestRate(rate), monthlyDepositAmount(depositAmount) {
        stringstream ss;
        ss << 200 << nextAccountNo++;
        accountNo = ss.str();
    }

    void description() const override{
        cout << "Savings Account with interest rate: " << interestRate << "%.\n";
    }
};

int savingsAccount::nextAccountNo = 1;

class monthlyDepositScheme : public account{
protected:
    static int nextAccountNo;
    float interestRate;
    float monthlyDepositAmount;

public:
    monthlyDepositScheme(const string& name, float initialBalance, float rate, float depositAmount) : account(name, initialBalance), interestRate(rate), monthlyDepositAmount(depositAmount) {
        stringstream ss;
        ss << 300 << nextAccountNo++;
        accountNo = ss.str();
    }

    void description() const override{
        cout << "Monthly Deposit Scheme Account.\n";
    }
};

int monthlyDepositScheme::nextAccountNo = 1;

class loanAccount : public account{
protected:
    static int nextAccountNo;
    float interestRate;

public:
    loanAccount(const string& name, float initialBalance, float rate) : account(name, initialBalance), interestRate(rate){
        stringstream ss;
        ss << 900 << nextAccountNo++;
        accountNo = ss.str();
    }

    void description() const override{
        cout << "Loan Account with interest rate: " << interestRate << "%.\n";
    }
};

int loanAccount::nextAccountNo = 1;

class twoYearMDS : public monthlyDepositScheme{
protected:
    float maximumInterest;

public:
    twoYearMDS(const string& name, float initialBalance, float rate, float depositAmount, float maxInterest) : monthlyDepositScheme(name, initialBalance, rate, depositAmount), maximumInterest(maxInterest) {}

    void description() const override{
        cout << "Two-Year Monthly Deposit Scheme.\n";
    }
};

class fiveYearMDS : public monthlyDepositScheme{
protected:
    float maximumInterest;

public:
    fiveYearMDS(const string& name, float initialBalance, float rate, float depositAmount, float maxInterest)
        : monthlyDepositScheme(name, initialBalance, rate, depositAmount), maximumInterest(maxInterest) {}

    void description() const override{
        cout << "Five-Year Monthly Deposit Scheme.\n";
    }
};

class initialDepositMDS : public monthlyDepositScheme{
protected:
    float maximumInterest;
    float initialDepositAmount;

public:
    initialDepositMDS(const string& name, float initialBalance, float rate, float depositAmount, float maxInterest, float initDeposit)
        : monthlyDepositScheme(name, initialBalance, rate, depositAmount), maximumInterest(maxInterest), initialDepositAmount(initDeposit) {}

    void description() const override{
        cout << "Initial Deposit Monthly Deposit Scheme.\n";
    }
};

int main(){
    currentAccount ca("Abrar Shahriar", 5000);
    ca.description();
    cout << "Account No: " << ca.getAccountNo() << ", Balance: " << ca.getBalance() << endl;

    savingsAccount sa("Tanvir Mahmud", 10000, 5.0, 200);
    sa.description();
    cout << "Account No: " << sa.getAccountNo() << ", Balance: " << sa.getBalance() << endl;

    return 0;
}
