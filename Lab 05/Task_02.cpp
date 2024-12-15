#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Employee{
private:
    string name;
    string dateOfBirth;
    double salary;

    static int calculateAge(const string &dob){
        time_t t = time(0);
        tm *now = localtime(&t);
        int currentYear = now->tm_year + 1900;
        int yearOfBirth = stoi(dob.substr(6));
        return currentYear - yearOfBirth;
    }

public:
    Employee() : name("John Doe"), dateOfBirth("01/01/2002"), salary(10000) {}

    string getName() const{ 
        return name; 
    }
    
    void setName(const string &n){
        name = (n.length() > 2) ? n : "John Doe";
    }

    string getDateOfBirth() const{ 
        return dateOfBirth; 
    }
    void setDateOfBirth(const string &dob){
        if(calculateAge(dob) > 18)
            dateOfBirth = dob;
        else
            dateOfBirth = "01/01/2002";    
    }

    double getSalary() const{ 
        return salary; 
    }

    void setSalary(double s){
        salary = (s >= 10000 && s <= 100000) ? s : 10000;
    }

    void setInfo(const string &n, const string &dob, double s){
        setName(n);
        setDateOfBirth(dob);
        setSalary(s);
    }

    void getInfo() const{
        cout << "Name: " << name << ", DOB: " << dateOfBirth << ", Salary: " << salary << endl;
    }

    const Employee &compareAge(const Employee &e) const{
        return (calculateAge(this->dateOfBirth) > calculateAge(e.dateOfBirth)) ? *this : e;
    }

    int getAge() const{
        return calculateAge(dateOfBirth);
    }
};

string generateRandomName(){
    string randomString;
    int length = rand() % 8 + 3;
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabetSize = sizeof(alphabet) - 1; 
    srand(static_cast<unsigned int>(time(0)));

    for(int i = 0; i < length; ++i)
        randomString += alphabet[rand() % alphabetSize];

    return randomString;
}

string generateRandomDOB(){
    int year = rand() % 40 + 1950;
    int month = rand() % 12 + 1;
    int day = rand() % 28 + 1;
    return (month < 10 ? "0" : "") + to_string(month) + "/" + (day < 10 ? "0" : "") + to_string(day) + "/" + to_string(year);
}

double generateRandomSalary(){
    return rand() % 90001 + 10000;
}

void generateInformationRandom(Employee &employee){
    employee.setName(generateRandomName());
    employee.setDateOfBirth(generateRandomDOB());
    employee.setSalary(generateRandomSalary());
}

void ShowAllBasedOnAge(Employee ar[], int size){
    sort(ar, ar + size, [](const Employee &a, const Employee &b){
        return a.getAge() < b.getAge();
    }
    );
    for(int i = 0; i < size; ++i)
        cout << "Name: " << ar[i].getName() << ", Age: " << ar[i].getAge() << endl;
}

int main(){
    srand(time(0));

    const int numEmployees = 100;
    Employee employees[numEmployees];

    for(int i = 0; i < numEmployees; ++i)
        generateInformationRandom(employees[i]);

    ShowAllBasedOnAge(employees, numEmployees);

    return 0;
}
