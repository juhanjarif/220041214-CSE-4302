#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//task 01
class Vehicle {
protected:
    string licensePlate;
    string manufacturer;
    double carriageSizeLimit;

public:
    Vehicle(string license, string manufacturerName, double size)
        : licensePlate(license), manufacturer(manufacturerName), carriageSizeLimit(size) {}

    virtual void performMaintenance() = 0;
    virtual double calculateFuelConsumption(double distance) = 0;

    double getCarriageSizeLimit() const {
        return carriageSizeLimit;
    }

    virtual ~Vehicle() {}
};

//task 02 Gasoline Vehicle
class GasolineVehicle : public Vehicle {
protected:
    double fuelTankCapacity;
    string fuelType;

public:
    GasolineVehicle(string license, string manufacturerName, double size, double tankCapacity, string fuel)
        : Vehicle(license, manufacturerName, size), fuelTankCapacity(tankCapacity), fuelType(fuel) {}

    void performMaintenance() override {
        cout << "Gasoline Vehicle - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        return (distance / 100) * 5;
    }
};

//task 02 Electric Vehicle
class ElectricVehicle : public Vehicle {
protected:
    double batteryCapacity;
    double chargingTime;

public:
    ElectricVehicle(string license, string manufacturerName, double size, double batteryCap, double chargeTime)
        : Vehicle(license, manufacturerName, size), batteryCapacity(batteryCap), chargingTime(chargeTime) {}

    void performMaintenance() override {
        cout << "Electric Vehicle - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        return (distance / 100) * 10;
    }
};

//task 03 Motorcycle Car Truck
class Motorcycle : public GasolineVehicle {
public:
    Motorcycle(string license, string manufacturerName, double size, double tankCapacity, string fuel)
        : GasolineVehicle(license, manufacturerName, size, tankCapacity, fuel) {}

    void performMaintenance() override {
        cout << "Motorcycle - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        return (distance / 100) * 3;
    }
};

class Car : public GasolineVehicle {
protected:
    int passengerCapacity;

public:
    Car(string license, string manufacturerName, double size, double tankCapacity, string fuel, int passengers)
        : GasolineVehicle(license, manufacturerName, size, tankCapacity, fuel), passengerCapacity(passengers) {}

    void performMaintenance() override {
        cout << "Car - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        return (distance / 100) * 6;
    }
};

class Truck : public GasolineVehicle {
protected:
    double cargoCapacity;

public:
    Truck(string license, string manufacturerName, double size, double tankCapacity, string fuel, double cargoCap)
        : GasolineVehicle(license, manufacturerName, size, tankCapacity, fuel), cargoCapacity(cargoCap) {}

    void performMaintenance() override {
        cout << "Truck - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        return (distance / 100) * 15;
    }
};

//task 03 Hybrid Vehicle
class HybridVehicle : public GasolineVehicle, public ElectricVehicle {
protected:
    double energyRegenerationEfficiency;

public:
    HybridVehicle(string license, string manufacturerName, double size, double tankCapacity, string fuel,
                  double batteryCap, double chargeTime, double regenerationEfficiency)
        : GasolineVehicle(license, manufacturerName, size, tankCapacity, fuel),
          ElectricVehicle(license, manufacturerName, size, batteryCap, chargeTime),
          energyRegenerationEfficiency(regenerationEfficiency) {}

    void performMaintenance() override {
        cout << "Hybrid Vehicle - maintenance" << endl;
    }

    double calculateFuelConsumption(double distance) override {
        double fuelConsumption = (distance / 100) * 6;
        double electricityConsumption = (distance / 100) * 8;
        return fuelConsumption + electricityConsumption;
    }
};

//task 04
bool compare(Vehicle* a, Vehicle* b) {
    return a->getCarriageSizeLimit() > b->getCarriageSizeLimit();
}

void sort_vehicles_by_capacity(vector<Vehicle*>& vehicles) {
    sort(vehicles.begin(), vehicles.end(), compare);
}

int main() {
    vector<Vehicle*> vehicles;

    vehicles.push_back(new Motorcycle("MOTORCYCLE1", "MotorcycleManu", 200, 10, "Petrol"));
    vehicles.push_back(new Car("CAR1", "CarManu", 400, 50, "Petrol", 4));
    vehicles.push_back(new Truck("TRUCK1", "TruckManu", 1500, 100, "Diesel", 5000));
    vehicles.push_back(new ElectricVehicle("EV1", "EVManu", 1000, 50, 30));

    HybridVehicle* hybrid = new HybridVehicle("HYBRID1", "HybridManu", 1200, 40, "Petrol", 40, 30, 85);

    for (auto vehicle : vehicles)
        vehicle->performMaintenance();

    hybrid->performMaintenance();

    cout << endl;

    double distance = 200;
    for (auto vehicle : vehicles)
        cout << "Fuel Consumption for vehicle with size " << vehicle->getCarriageSizeLimit() << " is: " << vehicle->calculateFuelConsumption(distance) << " units" << endl;

    cout << "Fuel Consumption for Hybrid Vehicle is: " << hybrid->calculateFuelConsumption(distance) << " units" << endl;

    cout << endl;

    sort_vehicles_by_capacity(vehicles);
    cout << "Sorted Vehicles by Capacity:" << endl;
    for (auto vehicle : vehicles)
        cout << "Vehicle with size " << vehicle->getCarriageSizeLimit() << endl;

    for (auto vehicle : vehicles)
        delete vehicle;

    delete hybrid;

    return 0;
}
