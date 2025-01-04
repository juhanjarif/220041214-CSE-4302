#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

class Coordinate{
private:
    float abscissa;
    float ordinate;

public:
    Coordinate() : abscissa(0), ordinate(0) {}

    Coordinate(float x, float y) : abscissa(x), ordinate(y) {}

    ~Coordinate() {}

    void display() const{
        cout << "The Coordinate is: " << abscissa << ", " << ordinate << endl;
    }

    float distanceTo(const Coordinate& c) const{
        return sqrt(pow((c.abscissa - abscissa), 2) + pow((c.ordinate - ordinate), 2));
    }

    float getDistance() const{
        return sqrt(pow(abscissa, 2) + pow(ordinate, 2));
    }

    void move_x(float val){
        abscissa += val;
    }

    void move_y(float val){
        ordinate += val;
    }

    void move(float x_val, float y_val){
        abscissa += x_val;
        ordinate += y_val;
    }

    bool operator<(const Coordinate& c) const{
        return this->getDistance() < c.getDistance();
    }

    bool operator>(const Coordinate& c) const{
        return this->getDistance() > c.getDistance();
    }

    bool operator>=(const Coordinate& c) const{
        return this->getDistance() >= c.getDistance();
    }

    bool operator<=(const Coordinate& c) const{
        return this->getDistance() <= c.getDistance();
    }

    bool operator!=(const Coordinate& c) const{
        return this->getDistance() != c.getDistance();
    }

    bool operator==(const Coordinate& c) const{
        return this->getDistance() == c.getDistance();
    }

    static void randomAssignment(Coordinate c[], int size){
        srand(static_cast<unsigned>(time(0)));
        for(int i = 0; i < size; i++){
            float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10));
            float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10));
            c[i] = Coordinate(x, y);
        }
    }

    static void highest(const Coordinate c[], int size){
        int index = 0;
        for(int i = 1; i < size; i++){
            if(c[i] > c[index])
                index = i;
        }
        cout << "Coordinate with the highest index: ";
        c[index].display();
        cout << "Distance from origin: " << c[index].getDistance() << endl;
    }

    static void lowest(const Coordinate c[], int size){
        int index = 0;
        for(int i = 1; i < size; i++){
            if(c[i] < c[index])
                index = i;
        }
        cout << "Coordinate with the lowest index: ";
        c[index].display();
        cout << "Distance from origin: " << c[index].getDistance() << endl;
    }
};

int main() {
    const int n = 10;
    Coordinate coord[n];

    Coordinate::randomAssignment(coord, n);
    Coordinate::highest(coord, n);
    Coordinate::lowest(coord, n);

    return 0;
}
