#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Coordinate{
private:
    float abscissa;
    float ordinate;
public:
    Coordinate() : abscissa(0), ordinate(0) {}
    Coordinate(float x, float y) : abscissa(x), ordinate(y) {}
    ~Coordinate() {}

    void display(){
        cout << "The Coordinate is (" << abscissa << ", " << ordinate << ")" << endl;
    }

    float getDistance(const Coordinate& c) const{
        return sqrt(pow((c.abscissa - abscissa), 2) + pow((c.ordinate - ordinate), 2));
    }

    void determineQuadrant(){
        if (abscissa > 0 && ordinate > 0)
            cout << "First Quadrant" << endl;
        else if (abscissa < 0 && ordinate > 0)
            cout << "Second Quadrant" << endl;
        else if (abscissa < 0 && ordinate < 0)
            cout << "Third Quadrant" << endl;
        else if (abscissa > 0 && ordinate < 0)
            cout << "Fourth Quadrant" << endl;
        else
            cout << "The point is the center" << endl;
    }

    void reflectOverX(){
        cout << "The reflection over X axis is : (" << abscissa << ", " << -ordinate << ")" << endl;
    }

    void reflectOverY(){
        cout << "The reflection over Y axis is : (" << -abscissa << ", " << ordinate << ")" << endl;
    }
    Coordinate& operator++(){
        abscissa++;
        ordinate++;
        return *this;
    }
    Coordinate operator++(int){
        Coordinate temp = *this;
        ++(*this);
        return temp;
    }
    Coordinate& operator--(){
        abscissa--;
        ordinate--;
        return *this;
    }
    Coordinate operator--(int){
        Coordinate temp = *this;
        --(*this);
        return temp;
    }

    friend istream& operator>>(istream& in, Coordinate& c){
        in >> c.abscissa >> c.ordinate;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Coordinate& c){
        out << "(" << c.abscissa << ", " << c.ordinate << ")";
        return out;
    }
};

int main() {
    Coordinate coord[10];
    vector<float> length(10);
    
    for(int i = 0; i < 10; i++)
        cin >> coord[i];

    for(int i = 0; i < 10; i++)
        length[i] = coord[i].getDistance(Coordinate(0, 0));

    for(int i = 0; i < 10; i++){
        for(int j = i + 1; j < 10; j++){
            if(length[i] > length[j]){
                float temp = length[j];
                length[j] = length[i];
                length[i] = temp;

                Coordinate tempCoord = coord[j];
                coord[j] = coord[i];
                coord[i] = tempCoord;
            }
        }
    }

    for(int i = 0; i < 10; i++)
        cout << coord[i] << "Distance from origin: " << length[i] << endl;

    return 0;
}
