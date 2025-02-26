#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<deque>
#include<list>

using namespace std;

class Book{
private:
    string title;
    string author;
    string ISBN;

public:
    Book(string bookname, string authorname, string isbn) : title(bookname), author(authorname), ISBN(isbn) {}

    string getTitle() const{
        return title;
    }

    string getAuthor() const{
        return author;
    }

    string getISBN() const{
        return ISBN;
    }

    void display() const{
        cout << "Book Title: " << title << "\tAuthor Name: " << author << "\tISBN: " << ISBN << endl;
    }
};

class Library{
private:
    vector<Book> inventory;
    deque<Book> borrowedBooks;
    list<Book> archivedBooks;

public:
    void addBook(){
        string title, author, isbn;
        cout << "Enter the Book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the Author name: ";
        cin.ignore();
        getline(cin, author);
        cout << "Enter ISBN: ";
        cin.ignore();
        getline(cin, isbn);
        inventory.push_back(Book(title, author, isbn));
        cout << "Book added successfully!" << endl;
    }

    void borrowBook(){
        string isbn;
        cout << "Enter the ISBN of the Book that you want to borrow: ";
        cin.ignore();
        getline(cin, isbn);

        for(auto temp = inventory.begin(); temp != inventory.end(); temp++){
            if(temp->getISBN() == isbn){
                borrowedBooks.push_back(*temp);
                inventory.erase(temp);
                cout << "Book Borrowed Successfully!" << endl;
            }
        }
        cout << "Book not available!" << endl;
    }

    void returnBorrowedBook(){
        string isbn;
        cout << "Enter the ISBN of the Book that you want to return: ";
        cin.ignore();
        getline(cin, isbn);

        for(auto temp = borrowedBooks.begin(); temp != borrowedBooks.end(); temp++){
            if(temp->getISBN() == isbn){
                inventory.push_back(*temp);
                borrowedBooks.erase(temp);
                cout << "Book Returned Successfully!" << endl;
            }
        }
        cout << "Book not available!" << endl;
    }

    void archiveBook(){
        string isbn;
        cout << "Enter the ISBN of the Book that you want to archive: ";
        cin.ignore();
        getline(cin, isbn);

        for(auto temp = inventory.begin(); temp != inventory.end(); temp++){
            if(temp->getISBN() == isbn){
                archivedBooks.push_back(*temp);
                inventory.erase(temp);
                cout << "Book Archived Successfully!" << endl;
            }
        }
        cout << "Book not available!" << endl;
    }

    void displayAllBooks(){
        cout << "Inventory Books: " << endl;
        for(const auto& temp: inventory)
            temp.display();
        cout << endl;

        cout << "Borrowed Books: " << endl;
        for(const auto& temp: borrowedBooks)
            temp.display();
        cout << endl;

        cout << "Archived Books: " << endl;
        for(const auto& temp: archivedBooks)
            temp.display();
        cout << endl;
    }

    void saveData(){
        ofstream inventoryFile("inventory.txt");
        ofstream borrowedBooksFile("borrowedBooks.txt");
        ofstream archivedBooksFile("archivedBooks.txt");

        if(!inventoryFile || !borrowedBooksFile || !archivedBooksFile){
            cout << "error: loading file!" << endl;
            return;
        }

        for(const auto& temp: inventory)
            inventoryFile << temp.getTitle() << "," << temp.getAuthor() << "," << temp.getISBN() << endl;

        for(const auto& temp: borrowedBooks)
            borrowedBooksFile << temp.getTitle() << "," << temp.getAuthor() << "," << temp.getISBN() << endl;

        for(const auto& temp: archivedBooks)
            archivedBooksFile << temp.getTitle() << "," << temp.getAuthor() << "," << temp.getISBN() << endl;

        cout << "Data Loaded Successfully!" << endl;
    }

    void loadData(){
        ifstream inventoryFile("inventory.txt");
        ifstream borrowedBooksFile("borrowedBooks.txt");
        ifstream archivedBooksFile("archivedBooks.txt");

        if(!inventoryFile || !borrowedBooksFile || !archivedBooksFile){
            cout << "error: loading file!" << endl;
            return;
        }

        string line, title, author, isbn;
        while(getline(inventoryFile, line)){
            stringstream ss(line);
            if(getline(ss, title, ',') && getline(ss, author, ',') && getline(ss, isbn)){
                inventory.push_back(Book(title, author, isbn));
            }
        }

        while(getline(borrowedBooksFile, line)){
            stringstream ss(line);
            if(getline(ss, title, ',') && getline(ss, author, ',') && getline(ss, isbn)){
                borrowedBooks.push_back(Book(title, author, isbn));
            }
        }
        while(getline(archivedBooksFile, line)){
            stringstream ss(line);
            if(getline(ss, title, ',') && getline(ss, author, ',') && getline(ss, isbn)){
                archivedBooks.push_back(Book(title, author, isbn));
            }
        }

    }
};

int main(){
    Library lib;
    int choice;

    cout << "Welcome to IUT Library Management System\nEnter your choice:" << endl;
    cout << "1. Add a Book\n2. Borrow a Book\n3. Return Borrowed Book\n4. Archieve a Book\n5. Display All Book\n6. Save to Files\n7. Load the Files" << endl;
    cout << "Enter -1 to exit!" << endl;

    while(cin >> choice && choice != -1){
        switch(choice){
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.borrowBook();
                break;
            case 3:
                lib.returnBorrowedBook();
                break;
            case 4:
                lib.archiveBook();
                break;
            case 5:
                lib.displayAllBooks();
                break;
            case 6:
                lib.saveData();
                break;
            case 7:
                lib.loadData();
                break;
            default:
                cout << "Invalid Input!" << endl;
        }
    }
}
