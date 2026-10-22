#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool issued;

public:
    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), issued(false) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return issued; }

    void issueBook() { issued = true; }
    void returnBook() { issued = false; }

    void display() const {
        cout << "\nBook ID: " << id
             << "\nTitle: " << title
             << "\nAuthor: " << author
             << "\nStatus: " << (issued ? "Issued" : "Available")
             << "\n-----------------------------\n";
    }
};

class Library {
private:
    vector<Book> books;

    int findBookIndex(int id) const {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].getId() == id) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    void addBook() {
        int id;
        string title, author;

        cout << "Enter book ID: ";
        if (!(cin >> id)) {
            cout << "Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (findBookIndex(id) != -1) {
            cout << "A book with this ID already exists.\n";
            return;
        }

        cout << "Enter book title: ";
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);

        if (title.empty() || author.empty()) {
            cout << "Title and author cannot be empty.\n";
            return;
        }

        books.emplace_back(id, title, author);
        cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books have been added yet.\n";
            return;
        }

        cout << "\n========== ALL BOOKS ==========\n";
        for (const Book& book : books) {
            book.display();
        }
    }

    void searchBook() const {
        int id;
        cout << "Enter book ID to search: ";
        if (!(cin >> id)) {
            cout << "Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
        } else {
            cout << "Book found:\n";
            books[index].display();
        }
    }

    void issueBook() {
        int id;
        cout << "Enter book ID to issue: ";
        if (!(cin >> id)) {
            cout << "Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
        } else if (books[index].isIssued()) {
            cout << "This book is already issued.\n";
        } else {
            books[index].issueBook();
            cout << "Book issued successfully!\n";
        }
    }

    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        if (!(cin >> id)) {
            cout << "Invalid ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(id);
        if (index == -1) {
            cout << "Book not found.\n";
        } else if (!books[index].isIssued()) {
            cout << "This book was not issued.\n";
        } else {
            books[index].returnBook();
            cout << "Book returned successfully!\n";
        }
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "      LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.displayBooks(); break;
            case 3: library.searchBook(); break;
            case 4: library.issueBook(); break;
            case 5: library.returnBook(); break;
            case 6: cout << "Thank you for using the Library Management System!\n"; break;
            default: cout << "Invalid choice. Please select 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}
