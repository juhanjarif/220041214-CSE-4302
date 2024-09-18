#include <iostream>
using namespace std;

class Counter{
private:
    int count = 0;
    int incrementStep;

public:
    void setIncrementStep(int newIncrementStep){
        incrementStep = newIncrementStep;
    }

    int getCount(){
        return count;
    }

    void increment(){
        count += incrementStep;
    }

    void resetCount(){
        count = 0;
    }
};

int main() {
    Counter myCounter;

    myCounter.setIncrementStep(3);
    myCounter.increment();
    cout << "count after first increment: " << myCounter.getCount();

    myCounter.increment();
    cout << "\ncount after second increment: " << myCounter.getCount();

    myCounter.resetCount();

    cout << "\nCount after reset: " << myCounter.getCount();

    return 0;
}
