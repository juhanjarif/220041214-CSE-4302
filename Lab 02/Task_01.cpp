#include <iostream>
using namespace std;
int main() {
    char ch;
    int a, b, c, d;
    cout << "Enter fisrt fraction: ";
    cin >> a >> ch >> b;
    cout << "Enter second fraction: ";
    cin >> c >> ch >> d;
    cout << "Result: " << ((a*d) + (b*c)) << "/" << (b*d);
    return 0;
}
