#include <iostream>
#include <string>

using namespace std;

class Employee{
private:
    string EmpName;
    int ID;
    int Age;
    float Salary;

    string getStatus() const{
        if(Age <= 25){
            if(Salary <= 20000)
                return "Low\n";
            else
                return "Moderate\n";
        }
        else{
            if (Salary <= 21000)
                return "Low\n";
            else if (Salary > 21000 && Salary <= 60000)
                return "Moderate\n";
            else
                return "High\n";
        }
    }


public:
    void FeedInfo(){
        EmpName = "Jarif";
        ID = 220041214;
        Age = 20;
        Salary = 25000;
    }

    void ShowInfo() const{
        cout << "Employee Name: " << EmpName << endl;
        cout << "Employee ID: " << ID << endl;
        cout << "Employee Age: " << Age << endl;
        cout << "Employee Salary: " << Salary << endl;
        cout << "Employee Status: " << getStatus() << endl;
    }
};

int main(){
    Employee employee;

    employee.FeedInfo();
    employee.ShowInfo();

    return 0;
}
