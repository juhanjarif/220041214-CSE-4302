#include <iostream>
using namespace std;

class RationalNumber{
private:
    int numerator;
    int denominator;

public:
    RationalNumber() : numerator(0), denominator(1){}; // default constructor added later on;
    void assign(int input_numerator, int input_denominator){
        if (input_denominator == 0) {
            cout << "You can not assign 0 as denominator." << endl;
            exit(0);
        }
        numerator = input_numerator;
        denominator = input_denominator;
    }

    double convert(){
        return float (numerator)/(denominator);
    }

    void invert(){
        if (numerator == 0) {
            cout << "You can not assign 0 as denominator. Inversion Failed." << endl;
            exit(0);
        }
        int temp = numerator;
        numerator = denominator;
        denominator = temp;
    }

    void print() {
        cout << "The Rational Number is " << numerator << "/" << denominator << endl;
    }
};

int main() {
    RationalNumber rational;

    rational.assign(-3, 1);
    rational.print();

    cout << "Decimal equivalent: " << rational.convert() << endl;

    rational.invert();
    rational.print();

    rational.assign(5, 0);

    return 0;
}
