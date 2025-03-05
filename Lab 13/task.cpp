#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Employee{
protected:
    string name;
    int id;

public:
    Employee(int empId, string empName) : id(empId), name(empName) {}
    virtual ~Employee() {}

    virtual void display() const{
        cout << "Name: " << name << ", ID: " << id << endl;
    }

    int getId() const{
        return id;
    }
    string getName() const{
        return name;
    }

    virtual void save(ofstream &out) const = 0;
};

class FullTimeEmployee : public Employee{
    set<string> workSchedule;

public:
    FullTimeEmployee(int empId, string empName) : Employee(empId, empName) {}

    void addSchedule(const string &schedule){
        workSchedule.insert(schedule);
    }

    void display() const override{
        cout << "Full-Time Employees:" << endl;
        Employee::display();
        cout << "Work Schedule: ";
        for(const auto &temp : workSchedule)
            cout << temp << " ";
        cout << endl;
    }

    void save(ofstream &out) const override{
        out << id << "," << name;
        for(const auto &s : workSchedule)
            out << "," << s;
        out << endl;
    }
};

class PartTimeEmployee : public Employee{
    set<string> shifts;

public:
    PartTimeEmployee(int empId, string empName) : Employee(empId, empName) {}

    void addShift(const string &shift){
        shifts.insert(shift);
    }

    void display() const override{
        cout << "\nPart-Time Employees:" << endl;
        Employee::display();
        cout << "Shifts: ";
        for(const auto &s : shifts)
            cout << s << " ";
        cout << endl;
    }

    void save(ofstream &out) const override{
        out << id << "," << name;
        for(const auto &s : shifts)
            out << "," << s;
        out << endl;
    }
};

map<int, Employee*> employees;

void addEmployee(){
    int id;
    string name, type;
    cout << "Enter Employee ID: ";
    cin.ignore();
    cin >> id;
    cout << "Enter Employee name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter employee type (Full-Time/Part-Time): ";
    cin >> type;

    if(type == "Full-Time")
        employees[id] = new FullTimeEmployee(id, name);
    else if(type == "Part-Time")
        employees[id] = new PartTimeEmployee(id, name);
    else{
        cout << "Invalid type!\n";
        return;
    }

    cout << "Employee added successfully!\n";
}

void assignSchedule() {
    int id;
    string schedule;
    cout << "Enter employee ID: ";
    cin >> id;
    cin.ignore();

    auto it = employees.find(id);
    if(it != employees.end()){
        auto *emp = dynamic_cast<FullTimeEmployee *>(it->second);
        if(emp){
            cout << "Enter work schedule: ";
            getline(cin, schedule);
            emp->addSchedule(schedule);
            cout << "Work schedule assigned successfully!\n";
        }
        else
            cout << "Employee is not Full-Time!\n";
    }
    else
        cout << "Employee not found!\n";
}

void assignShift(){
    int id;
    string shift;
    cout << "Enter employee ID: ";
    cin >> id;
    cin.ignore();

    auto it = employees.find(id);
    if(it != employees.end()){
        auto *emp = dynamic_cast<PartTimeEmployee *>(it->second);
        if(emp){
            cout << "Enter shift timing: ";
            getline(cin, shift);
            emp->addShift(shift);
            cout << "Shift assigned successfully!\n";
        }
        else
            cout << "Employee is not Part-Time!\n";
    }
    else
        cout << "Employee not found!\n";
}

void displayData() {
    for(const auto &e : employees){
        if(dynamic_cast<FullTimeEmployee *>(e.second))
            e.second->display();
    }
    for(const auto &e : employees){
        if(dynamic_cast<PartTimeEmployee *>(e.second))
            e.second->display();
    }
}

void saveData() {
    ofstream fullOut("fulltime_employees.txt");
    ofstream partOut("parttime_employees.txt");

    if(!fullOut || !partOut){
        cout << "Error opening files!\n";
        return;
    }

    for(const auto &e : employees){
        if(auto *emp = dynamic_cast<FullTimeEmployee *>(e.second))
            emp->save(fullOut);
        else if(auto *emp = dynamic_cast<PartTimeEmployee *>(e.second))
            emp->save(partOut);
    }

    cout << "Data saved successfully!\n";
}

void loadData() {
    ifstream fullIn("fulltime_employees.txt");
    ifstream partIn("parttime_employees.txt");
    if(!fullIn || !partIn){
        cout << "Error opening files!\n";
        return;
    }

    for(auto &e : employees)
        delete e.second;
    employees.clear();
    int id;
    string name, word, line;

    while(getline(fullIn, line)){
        stringstream ss(line);
        getline(ss, word, ','); id = stoi(word);
        getline(ss, name, ',');

        auto emp = new FullTimeEmployee(id, name);
        while (getline(ss, word, ',')) emp->addSchedule(word);
        employees[id] = emp;
    }

    while(getline(partIn, line)){
        stringstream ss(line);
        getline(ss, word, ','); id = stoi(word);
        getline(ss, name, ',');

        auto emp = new PartTimeEmployee(id, name);
        while (getline(ss, word, ',')) emp->addShift(word);
        employees[id] = emp;
    }

    cout << "Data loaded successfully!\n";
}

int main(){
    int choice;
    cout << "\n1. Add Employee\n2. Assign Work Schedule\n3. Assign Shift\n4. Display Data\n5. Save Data\n6. Load Data\n7. Exit\nEnter choice: ";
    while(cin >> choice && choice != 7){
        switch(choice){
            case 1:
                addEmployee();
                break;
            case 2:
                assignSchedule();
                break;
            case 3:
                assignShift();
                break;
            case 4:
                displayData();
                break;
            case 5:
                saveData();
                break;
            case 6:
                loadData();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    for(auto &e : employees)
        delete e.second;
    return 0;
}
