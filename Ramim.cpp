#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool is_borrowed;
    string borrower;

    Book(string title, string author)
        : title(title), author(author), is_borrowed(false) {}

    void borrow(const string& borrower_name) {
        is_borrowed = true;
        borrower = borrower_name;
    }

    void returnBook() {
        is_borrowed = false;
        borrower = "";
    }

    void showDetails() const {
        cout << "Title: " << title << ", Author: " << author;
        if (is_borrowed) cout << " (Borrowed by " << borrower << ")";
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<string> search_history;

public:
    Library() {
        loadFromFile();
    }

    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        saveToFile();
    }

    void borrowBook(const string& title, const string& borrower_name) {
        for (auto& book : books) {
            if (book.title == title && !book.is_borrowed) {
                book.borrow(borrower_name);
                cout << "You borrowed: " << title << endl;
                saveToFile();
                return;
            }
        }
        cout << "Book is not available or already borrowed!" << endl;
    }

    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title && book.is_borrowed) {
                book.returnBook();
                cout << "You returned: " << title << endl;
                saveToFile();
                return;
            }
        }
        cout << "Book was not borrowed!" << endl;
    }

    void searchBook(const string& title) {
        search_history.push_back(title);
        for (const auto& book : books) {
            if (book.title == title) {
                book.showDetails();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void viewSearchHistory() const {
        if (search_history.empty()) {
            cout << "No search history available." << endl;
            return;
        }
        cout << "Search History:" << endl;
        for (const auto& query : search_history) {
            cout << "- " << query << endl;
        }
    }

    void showAllBooks() const {
        for (const auto& book : books) {
            book.showDetails();
        }
    }

    void saveToFile() const {
        ofstream outfile("data.txt", ios::trunc);
        for (const auto& book : books) {
            outfile << book.title << endl << book.author << endl << book.is_borrowed << endl << book.borrower << endl;
        }
        outfile.close();
    }

    void loadFromFile() {
        ifstream infile("data.txt");
        string title, author, borrower;
        bool is_borrowed;
        while (getline(infile, title) && getline(infile, author)) {
            infile >> is_borrowed;
            infile.ignore();
            getline(infile, borrower);
            books.push_back(Book(title, author));
            if (is_borrowed) {
                books.back().borrow(borrower);
            }
        }
        infile.close();
    }
};

int main() {
    Library library;
    int choice;
    string title, author, borrower_name;

    do {
        cout << "\n1. Add Book\n2. Borrow Book\n3. Return Book\n4. Search Book\n5. View Search History\n6. Show All Books\n7. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                library.addBook(title, author);
                break;
            case 2:
                cout << "Enter Book Title: "; getline(cin, title);
                cout << "Enter Borrower Name: "; getline(cin, borrower_name);
                library.borrowBook(title, borrower_name);
                break;
            case 3:
                cout << "Enter Book Title: "; getline(cin, title);
                library.returnBook(title);
                break;
            case 4:
                cout << "Enter Book Title to Search: "; getline(cin, title);
                library.searchBook(title);
                break;
            case 5:
                library.viewSearchHistory();
                break;
            case 6:
                library.showAllBooks();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}
