#include <iostream>
using namespace std;
struct fraction{
    int numerator;
    int denominator;
};
int main() {
    struct fraction firstFrac, secFrac;
    char ch;
    cout << "Enter fisrt fraction: ";
    cin >> firstFrac.numerator >> ch >> firstFrac.denominator;
    cout << "Enter second fraction: ";
    cin >> secFrac.numerator >> ch >> secFrac.denominator;
    cout << "Result: " << ((firstFrac.numerator*secFrac.denominator) + (firstFrac.denominator*secFrac.numerator)) << "/" << (firstFrac.denominator*secFrac.denominator);
    return 0;
}
