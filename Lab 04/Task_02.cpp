#include <iostream>
#include <string>

using namespace std;

class BankAccount{
private:
    int accountNumber;
    string accountHolderName;
    string accountType;
    float currentBalance;
    const float minimumBalance;
    static int totalAccountsCreated;
    static int currentAccounts;
    static float totalSourceTaxCollected;

public:
    BankAccount(int accNum, const string& holderName, const string& type, float balance, float minBalance) : accountNumber(accNum), accountHolderName(holderName), accountType(type), currentBalance(balance), minimumBalance(minBalance) {
        if(balance < minBalance){
            cout << "Error: Initial balance cannot be less than minimum balance." << endl;
            exit(1);
        }
        totalAccountsCreated++;
        currentAccounts++;
    }

    ~BankAccount(){
        cout << "Account of Mr./Ms. " << accountHolderName << " with account no. " << accountNumber << " is destroyed with a balance of BDT " << currentBalance << endl;
        currentAccounts--;
    }

    void showInfo() const{
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Current Balance: " << currentBalance << " BDT" << endl;
        cout << "Minimum Balance: " << minimumBalance << " BDT" << endl;
    }

    void showBalance() const{
        cout << "Current Balance: " << currentBalance << " BDT" << endl;
    }

    void deposit(float amount){
        if(amount <= 0){
            cout << "Invalid deposit amount!" << endl;
            return;
        }
        currentBalance += amount;
        cout << "BDT " << amount << " deposited successfully." << endl;
        showBalance();
    }

    void withdrawal(float amount){
        if(amount <= 0){
            cout << "Invalid withdrawal amount!" << endl;
            return;
        }

        if(currentBalance - amount < minimumBalance){
            cout << "Error: Withdrawal would breach the minimum balance requirement." << endl;
            return;
        }
        currentBalance -= amount;
        cout << "BDT " << amount << " withdrawn successfully." << endl;
        showBalance();
    }

    void giveInterest(float rate = 3.0f){
        float interest = (currentBalance * rate) / 100.0f;
        float sourceTax = interest * 0.1f;
        totalSourceTaxCollected += sourceTax;
        interest -= sourceTax;
        currentBalance += interest;
        cout << "Interest of BDT " << interest << " credited to the account after deducting source tax." << endl;
        showBalance();
    }

    static int getTotalAccountsCreated(){ 
        return totalAccountsCreated; 
    }
    static int getCurrentAccounts(){ 
        return currentAccounts;
    }
    static float getTotalSourceTaxCollected(){ 
        return totalSourceTaxCollected; 
    }

    friend BankAccount& Larger(BankAccount& A, BankAccount& B);
};

int BankAccount::totalAccountsCreated = 0;
int BankAccount::currentAccounts = 0;
float BankAccount::totalSourceTaxCollected = 0.0f;

void display_stat(){
    cout << "Total Accounts Created: " << BankAccount::getTotalAccountsCreated() << endl;
    cout << "Current Accounts: " << BankAccount::getCurrentAccounts() << endl;
    cout << "Total Source Tax Collected: BDT " << BankAccount::getTotalSourceTaxCollected() << endl;
}

BankAccount& Larger(BankAccount& A, BankAccount& B){
    return (A.currentBalance > B.currentBalance) ? A : B;
}

int main(){
    BankAccount acc1(101, "Juhan Ahmed", "Savings", 10000.0f, 5000.0f);
    BankAccount acc2(102, "Tanvir Mahmud", "Current", 20000.0f, 10000.0f);

    acc1.showInfo();
    acc1.deposit(5000.0f);
    acc1.withdrawal(2000.0f);
    acc1.giveInterest();

    acc2.showInfo();
    acc2.giveInterest(5.0f);

    display_stat();
    return 0;
}
