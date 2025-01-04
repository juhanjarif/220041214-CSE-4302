#include <iostream>

using namespace std;

class Kelvin;

class Celsius{
private:
    float temperature;

public:
    Celsius() : temperature(0) {}
    Celsius(float temp) : temperature(temp) {}
    ~Celsius() {}

    void assign(const float& temp){
        if(temp <= -273.15)
            cout << "Error!" << endl;
        else
            temperature = temp;
    }

    void display() const{
        cout << "The temperature is " << temperature << " Celsius" << endl;
    }

    float getTemp() const{
        return temperature;
    }
    Celsius& operator=(const Kelvin& k);
    Celsius& operator=(const Celsius& c){
        temperature = c.getTemp();
        return *this;
    }
};

class Fahrenheit{
private:
    float temperature;

public:
    Fahrenheit() : temperature(0) {}
    Fahrenheit(float temp) : temperature(temp) {}
    ~Fahrenheit() {}

    void assign(const float& temp){
        if(temp <= -459.67)
            cout << "Error!" << endl;
        else
            temperature = temp;
    }

    void display() const{
        cout << "The temperature is " << temperature << " Fahrenheit" << endl;
    }

    float getTemp() const{
        return temperature;
    }
    Fahrenheit& operator=(const Kelvin& k);

    Fahrenheit& operator=(const Celsius& c){
        temperature = (c.getTemp() * 9.0 / 5.0) + 32;
        return *this;
    }
};

class Kelvin{
private:
    float temperature;

public:
    Kelvin() : temperature(0) {}
    Kelvin(float temp) : temperature(temp) {}
    ~Kelvin() {}

    void assign(const float& temp){
        if(temp < 0)
            cout << "Error!" << endl;
        else
            temperature = temp;
    }

    void display() const{
        cout << "The temperature is " << temperature << " Kelvin" << endl;
    }

    float getTemp() const{
        return temperature;
    }
    Kelvin& operator=(const Fahrenheit& f);

    Kelvin& operator=(const Celsius& c){
        temperature = c.getTemp() + 273.15;
        return *this;
    }
};
Celsius& Celsius::operator=(const Kelvin& k){
    temperature = k.getTemp() - 273.15;
    return *this;
}
Fahrenheit& Fahrenheit::operator=(const Kelvin& k){
    temperature = (k.getTemp() - 273.15) * 9.0 / 5.0 + 32;
    return *this;
}
Kelvin& Kelvin::operator=(const Fahrenheit& f){
    temperature = (f.getTemp() - 32) * 5.0 / 9.0 + 273.15;
    return *this;
}

int main() {
    Celsius cel(50);
    Fahrenheit fahren(98);
    Kelvin kel(303);

    cel.display();
    fahren.display();
    kel.display();

    return 0;
}
