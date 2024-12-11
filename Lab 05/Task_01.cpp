#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Student{
private:
    string studentName;
    string department;
    string program;
    string section;
    int admissionYear;
    string address;
    double gpa;
    string studentID;

public:
    Student() : gpa(0.0) {}

    string getStudentName() const{ 
        return studentName; 
    }
    void setStudentName(const string &name){ 
        studentName = name;
    }

    string getDepartment() const{ 
        return department; 
    }
    void setDepartment(const string &dept){ 
        department = dept;
    }

    string getProgram() const{ 
        return program; 
    }
    void setProgram(const string &prog){ 
        program = prog; 
    }

    string getSection() const{ 
        return section; 
    }
    void setSection(const string &sec){ 
        section = sec; 
    }

    int getAdmissionYear() const{ 
        return admissionYear; 
    }
    void setAdmissionYear(int year){ 
        admissionYear = year; 
    }

    string getAddress() const{ 
        return address; 
    }
    void setAddress(const string &addr){ 
        address = addr; 
    }

    double getGPA() const{ 
        return gpa; 
    }
    void setGPA(double g){ 
        gpa = g; 
    }

    string getStudentID() const{ 
        return studentID; 
    }

    void generateID(){
        string year = to_string(admissionYear).substr(2);
        string type = "00";
        string dept = (department == "CSE") ? "41" : "42";
        string sec = (section == "A") ? "1" : (section == "B") ? "2" : "3";
        int number = rand() % 100;
        string num = (number < 10 ? "0" : "") + to_string(number);
        studentID = year + type + dept + sec + num;
    }

    void calculateGPA(const vector<int> &quizzes, int midterm, int finals, int attendance){
        vector<int> sortedQuizzes = quizzes;
        sort(sortedQuizzes.rbegin(), sortedQuizzes.rend());
        double quizTotal = (sortedQuizzes[0] + sortedQuizzes[1] + sortedQuizzes[2]) / 3.0;
        double total = (attendance * 0.10) + (quizTotal * 0.15) + (midterm * 0.25) + (finals * 0.50);
        gpa = total / 100 * 4;
    }
};

void EditInformationByKeyboard(Student &student){
    string input;
    int year;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, input);
    student.setStudentName(input);
    cout << "Enter Department: ";
    getline(cin, input);
    student.setDepartment(input);
    cout << "Enter Program: ";
    getline(cin, input);
    student.setProgram(input);
    cout << "Enter Section: ";
    getline(cin, input);
    student.setSection(input);
    cout << "Enter Admission Year: ";
    cin >> year;
    student.setAdmissionYear(year);
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, input);
    student.setAddress(input);
}

void generateInformationRandom(Student &student){
    vector<string> names = {"Abrar", "Saom", "Tanvir", "Mirza", "Juhan", "Maha", "Rodoshi"};
    vector<string> departments = {"CSE", "SWE"};
    vector<string> programs = {"Undergraduate"};
    vector<string> sections = {"A", "B"};
    vector<string> words = {"Street", "Lane", "Avenue", "Boulevard", "Road"};

    student.setStudentName(names[rand() % names.size()] + " " + names[rand() % names.size()]);
    student.setDepartment(departments[rand() % departments.size()]);
    student.setProgram(programs[rand() % programs.size()]);
    student.setSection(sections[rand() % sections.size()]);
    student.setAdmissionYear(rand() % 4 + 2020);
    student.setAddress(words[rand() % words.size()] + " " + words[rand() % words.size()] + " " + words[rand() % words.size()] + " " + words[rand() % words.size()] + " " + words[rand() % words.size()]);
    student.generateID();
    vector<int> quizzes(4);
    fo(int &quiz : quizzes) 
        quiz = rand() % 25;
    student.calculateGPA(quizzes, rand() % 25, rand() % 35, rand() % 15);
}

void ShowAllAlphabetically(Student ar[], int size) {
    sort(ar, ar + size, [](const Student &a, const Student &b) { return a.getStudentID() < b.getStudentID(); });
    for (int i = 0; i < size; ++i)
        cout << "Name: " << ar[i].getStudentName() << ", ID: " << ar[i].getStudentID() << ", GPA: " << ar[i].getGPA() << endl;
}

int main(){
    srand(time(0));
    const int numStudents = 100;
    Student students[numStudents];

    for(int i = 0; i < 2; ++i){
        EditInformationByKeyboard(students[i]);
        students[i].generateID();
        cout << "Generated ID for student " << i + 1 << ": " << students[i].getStudentID() << endl;
    }

    for (int i = 2; i < numStudents; ++i)
        generateInformationRandom(students[i]);

    ShowAllAlphabetically(students, numStudents);

    return 0;
}
