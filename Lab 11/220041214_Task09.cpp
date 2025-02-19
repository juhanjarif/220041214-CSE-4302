#include <fstream>
#include <iostream>
using namespace std;

class person
{
protected:
    char name[40];
    int age;

public:
    void getData(void)
    {
        cout << "\n Enter last name: ";
        cin >> name;
        cout << " Enter age: ";
        cin >> age;
    }

    void showData(void)
    {
        cout << "\n Name: " << name;
        cout << "\n Age: " << age;
    }

    void diskIn(int);
    void diskOut();
    static int diskCount();
};

void person::diskIn(int pn)
{
    ifstream infile;
    infile.open("PERSFILE.DAT", ios::binary);
    infile.seekg(pn * sizeof(person));
    infile.read((char*)this, sizeof(*this));
}

void person::diskOut()
{
    ofstream outfile;
    outfile.open("PERSFILE.DAT", ios::app | ios::binary);
    outfile.write((char*)this, sizeof(*this));
}

int person::diskCount()
{
    ifstream infile;
    infile.open("PERSFILE.DAT", ios::binary);
    infile.seekg(0, ios::end);
    return (int)infile.tellg() / sizeof(person);
}

int main()
{
    person p;
    char ch;
    do
    {
        cout << "Enter data for person:";
        p.getData();
        p.diskOut();
        cout << "Do another (y/n)? ";
        cin >> ch;
    } while(ch == 'y');

    int n = person::diskCount();
    cout << "There are " << n << " persons in file\n";
    for(int j = 0; j < n; j++)
    {
        cout << "\nPerson " << j;
        p.diskIn(j);
        p.showData();
    }
    cout << endl;
    return 0;
}
