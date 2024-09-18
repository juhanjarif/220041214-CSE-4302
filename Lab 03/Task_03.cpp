#include<iostream>
#include<cstring>
using namespace std;

class Medicine{
private:
    char TradeName[30];
    char GenericName[30];
    double unitPrice = 0;

    int input_nos = 1;
    double discountPercent = 5;

public:
    void assignName(char name[], char genericName[]){
        strcpy(TradeName, name);
        strcpy(GenericName, genericName);
    }
    void assignPrice(double price){
        unitPrice = price;
    }
    void setDiscountPercent(double percent){
        discountPercent = percent;
    }
    double getSellingPrice(int nos){
        input_nos = nos;
        return (unitPrice - unitPrice*(discountPercent/100)) * input_nos;
    }
    void display(){
        cout << "MRP. of " << TradeName << " (" << GenericName << ") " << "is BDT " << unitPrice << ". " << "The current discount " << discountPercent << "%. Selling price BDT " << getSellingPrice(input_nos) << "." << endl;
    }
};
int main(){
    Medicine myMedicine;

    char medsName[] = "Napa";
    char genName[] = "Paracetamol";

    myMedicine.assignName(medsName, genName);
    myMedicine.assignPrice(1);
    myMedicine.setDiscountPercent(10);
    myMedicine.getSellingPrice(10);

    myMedicine.display();
}
