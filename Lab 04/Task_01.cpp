#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

class Calculator{
private:
    float currentAngle;
    float previousAngle;
    string status;

    float degreesToRadians(float degrees) const{
        return degrees * M_PI / 180.0f;
    }

    float getCurrentAngle() const{
        return currentAngle;
    }

    void setCurrentAngle(float angle){
        previousAngle = currentAngle;
        currentAngle = angle;
        setStatus();
    }

    bool isCloseToZero(float value, float epsilon = 1e-6) const{
        return fabs(value) < epsilon;
    }

    string getStatus() const{
        return status;
    }

    void setStatus(){
        if (currentAngle > 0)
            status = "Positive";
        else if(isCloseToZero(currentAngle))
            status = "Zero";
        else
            status = "Negative";
    }

public:
    Calculator() : currentAngle(0.0f), previousAngle(0.0f){
        setStatus();
    }

    Calculator(float angle) : currentAngle(angle), previousAngle(0.0f){
        setStatus();
    }

    float calculateSine() const{
        return sin(degreesToRadians(currentAngle));
    }

    float calculateCosine() const{
        return cos(degreesToRadians(currentAngle));
    }

    float calculateTangent(){
        if(fmod(currentAngle, 180.0f) == 90.0f)
            currentAngle = previousAngle;
        return tan(degreesToRadians(currentAngle));
    }

    float calculateArcSine(){
        return asin(currentAngle);
    }

    float calculateArcCosine(){
        return acos(currentAngle);
    }

    float calculateArcTangent(){
        return atan(currentAngle);
    }

    void calculateForAngle(float angleValue){
        setCurrentAngle(angleValue);
        cout << "Calculating for angle (in degrees): " << angleValue << endl;
        cout << "Sine: " << sin(degreesToRadians(angleValue)) << endl;
        float cosine = cos(degreesToRadians(angleValue));
        if(isCloseToZero(cosine))
            cosine = 0.0f;
        cout << "Cosine: " << cosine << endl;
        if(fmod(angleValue, 180.0f) == 90.0f)
            cout << "Tangent: Invalid operation: undefined result" << endl;
        else
            cout << "Tangent: " << tan(degreesToRadians(angleValue)) << endl;
        cout << "Inverse of Sine: " << asin(degreesToRadians(angleValue)) << endl;
        cout << "Inverse of Cosine: " << acos(degreesToRadians(angleValue)) << endl;
        cout << "Inverse of Tangent: " << atan(degreesToRadians(angleValue)) << endl;

        cout << "\n" << endl;
    }

    void clear(){
        previousAngle = currentAngle;
        currentAngle = 0.0f;
        setStatus();
        cout << "Calculator reset to 0." << endl;
    }

    void display() const{
        cout << "Calculator display: " << currentAngle << " degrees" << endl;
    }

    ~Calculator(){
        cout << "Destructor of the Calculator object is called" << endl;
    }
};

int main(){
    Calculator calc;

    calc.calculateForAngle(90.0f);
    calc.calculateForAngle(45.0f);

    calc.clear();
    calc.display();

    return 0;
}
