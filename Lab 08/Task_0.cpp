#include<iostream>
#include<string>
#include<vector>

using namespace std;

class vehicle{
protected:
    string licensePlate;
    string manufacturer;
    double carriageSize;
public:
    vehicle(string license, string manufacturerName, double size) : licensePlate(license), manufacturer(manufacturerName), carriageSize(size) {}
    virtual void maintenance(){
        cout << "Vehicle - maintenance" << endl;
    }
    virtual ~vehicle() {}
};

class gasolineVehicle : virtual public vehicle{
protected:
    double fuelTankCapacity;
    string fuelType;
public:
    gasolineVehicle(string license, string manufacturerName, double size, double tankCapacity, string fuel) : vehicle(license, manufacturerName, size), fuelTankCapacity(tankCapacity), fuelType(fuel) {}
    void maintenance() override{
        cout << "Gasoline Vehicle - maintenance" << endl;
    }
};

class electricVehicle : virtual public vehicle{
protected:
    double batteryCapacity;
    double chargingTime;
public:
    electricVehicle(string license, string manufacturerName, double size, double batteryCapacity, double chargingTime) : vehicle(license, manufacturerName, size), batteryCapacity(batteryCapacity), chargingTime(chargingTime) {}
    void maintenance() override{
        cout << "Electric Vehicle - maintenance" << endl;
    }
};

class hybridVehicle : public gasolineVehicle, public electricVehicle{
protected:
    double energyEfficiency;
public:
    hybridVehicle(string license, string manufacturerName, double size, double tankCapacity, string fuel, double batteryCapacity, double chargingTime, double efficiency)
        : vehicle(license, manufacturerName, size), gasolineVehicle(license, manufacturerName, size, tankCapacity, fuel), electricVehicle(license, manufacturerName, size, batteryCapacity, chargingTime), energyEfficiency(efficiency) {}
    void maintenance() override{
        cout << "Hybrid Vehicle - maintenance" << endl;
    }
};

class motorcycle : public gasolineVehicle{
public:
    motorcycle(string license, string manufacturerName, double size, double tankCapacity, string fuel) : vehicle(license, manufacturerName, size), gasolineVehicle(license, manufacturerName, size, tankCapacity, fuel) {}
    void maintenance() override{
        cout << "Motorcycle - maintenance" << endl;
    }
};

class car : public gasolineVehicle{
protected:
    int numberOfPassengers;
public:
    car(string license, string manufacturerName, double size, double tankCapacity, string fuel, int passengers) : vehicle(license, manufacturerName, size), gasolineVehicle(license, manufacturerName, size, tankCapacity, fuel), numberOfPassengers(passengers) {}
    void maintenance() override {
        cout << "Car - maintenance" << endl;
    }
};

class truck : public gasolineVehicle{
protected:
    double cargoCapacity;
public:
    truck(string license, string manufacturerName, double size, double tankCapacity, string fuel, double cargoCapacity) : vehicle(license, manufacturerName, size), gasolineVehicle(license, manufacturerName, size, tankCapacity, fuel), cargoCapacity(cargoCapacity) {}
    void maintenance() override{
        cout << "Truck - maintenance" << endl;
    }
};

class employee{
protected:
    string employeeName;
    int employeeID;
public:
    employee(string name, int id) : employeeName(name), employeeID(id) {}
    virtual ~employee() {}
};

class manager : public employee{
public:
    manager(string name, int id) : employee(name, id) {}
    void introduce(){
        cout << "Mr. " << employeeName << endl;
    }
};

class driver : public employee{
public:
    driver(string name, int id) : employee(name, id) {}
    void introduce(){
        cout << employeeName << endl;
    }
};

class branch {
protected:
    vector<motorcycle> motorcycles;
    vector<car> cars;
    vector<truck> trucks;
    vector<electricVehicle> electricVehicles;
    vector<hybridVehicle> hybridVehicles;
    vector<manager> managers;
    vector<driver> drivers;

public:
    void introduceEmployees() {
        for (auto& manager : managers) {
            manager.introduce();
        }
        for (auto& driver : drivers) {
            driver.introduce();
        }
    }

    void performMaintenance(){
        for(auto& motorcycle : motorcycles){
            motorcycle.maintenance();
        }
        for(auto& car : cars){
            car.maintenance();
        }
        for(auto& truck : trucks){
            truck.maintenance();
        }
        for(auto& ev : electricVehicles){
            ev.maintenance();
        }
        for(auto& hybrid : hybridVehicles){
            hybrid.maintenance();
        }
    }
    void addManager(const string& name, int id){
        managers.push_back(manager(name, id));
    }
    void addDriver(const string& name, int id){
        drivers.push_back(driver(name, id));
    }
    void addMotorcycle(const string& license, const string& manufacturer, double size, double tankCapacity, const string& fuel){
        motorcycles.push_back(motorcycle(license, manufacturer, size, tankCapacity, fuel));
    }
    void addCar(const string& license, const string& manufacturer, double size, double tankCapacity, const string& fuel, int passengers){
        cars.push_back(car(license, manufacturer, size, tankCapacity, fuel, passengers));
    }
    void addTruck(const string& license, const string& manufacturer, double size, double tankCapacity, const string& fuel, double cargoCapacity){
        trucks.push_back(truck(license, manufacturer, size, tankCapacity, fuel, cargoCapacity));
    }
    void addElectricVehicle(const string& license, const string& manufacturer, double size, double batteryCapacity, double chargingTime) {
        electricVehicles.push_back(electricVehicle(license, manufacturer, size, batteryCapacity, chargingTime));
    }
    void addHybridVehicle(const string& license, const string& manufacturer, double size, double tankCapacity, const string& fuel, double batteryCapacity, double chargingTime, double efficiency) {
        hybridVehicles.push_back(hybridVehicle(license, manufacturer, size, tankCapacity, fuel, batteryCapacity, chargingTime, efficiency));
    }
};

int main(){
    branch branchVar;

    for(int i=1; i<=2; i++){
        string license = "MOTORCYCLE" + to_string(i);
        string manufacturer = "MotorCycleManufacturer" + to_string(i);
        double size = 214.0 + (i*10);
        double tankCapacity = 11.0 + (i*2);
        string fuel = "Petrol";
        branchVar.addMotorcycle(license, manufacturer, size, tankCapacity, fuel);

        license = "CAR" + to_string(i);
        manufacturer = "CarManufacturer" + to_string(i + 1);
        double carSize = 41.0 + (i*100);
        double carTankCapacity = 40.0 + (i*1.5);
        int passengers = 5;
        branchVar.addCar(license, manufacturer, carSize, carTankCapacity, fuel, passengers);

        license = "TRUCK" + to_string(i);
        manufacturer = "TruckManufacturer" + to_string(i);
        double truckSize = 214.0 + (i*200);
        double truckTankCapacity = 100.0 + (i*5);
        double cargoCapacity = 2000.0 + (i*100);
        branchVar.addTruck(license, manufacturer, truckSize, truckTankCapacity, "Diesel", cargoCapacity);

        license = "EV" + to_string(i);
        manufacturer = "EVManufacturer" + to_string(i);
        double evSize = 2200.0 + (i*50);
        double batteryCapacity = 50.0 + (i*3);
        double chargingTime = 0.5 + (i*0.1);
        branchVar.addElectricVehicle(license, manufacturer, evSize, batteryCapacity, chargingTime);

        license = "HYBRID" + to_string(i);
        manufacturer = "HybridManufacturer" + to_string(i);
        double hybridSize = 2200.0 + (i*80);
        double tankCapacityHybrid = 40.0 + (i*2);
        double batteryCapacityHybrid = 40.0 + (i*3);
        double chargingTimeHybrid = 1.0 + (i*0.1);
        double efficiency = 15.0 + (i*0.5);
        branchVar.addHybridVehicle(license, manufacturer, hybridSize, tankCapacityHybrid, "Gasoline", batteryCapacityHybrid, chargingTimeHybrid, efficiency);
    }

    branchVar.introduceEmployees();
    branchVar.performMaintenance();

    return 0;
}
