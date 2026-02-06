#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool available;

public:
    Book(int id, string title, string author)
        : id(id), title(title), author(author), available(true) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    void borrowBook() {
        available = false;
    }

    void returnBook() {
        available = true;
    }
};

class User {
private:
    int userId;
    string name;
    vector<int> borrowedBooks;

public:
    User(int userId, string name)
        : userId(userId), name(name) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }

    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); it++) {
            if (*it == bookId) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }

    void showBorrowedBooks() const {
        cout << "Borrowed Books IDs: ";
        for (int id : borrowedBooks)
            cout << id << " ";
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(int id, string title, string author) {
        books.emplace_back(id, title, author);
    }

    void registerUser(int id, string name) {
        users.emplace_back(id, name);
    }

    Book* findBook(int id) {
        for (auto &book : books)
            if (book.getId() == id)
                return &book;
        return nullptr;
    }

    User* findUser(int id) {
        for (auto &user : users)
            if (user.getUserId() == id)
                return &user;
        return nullptr;
    }

    void borrowBook(int userId, int bookId) {
        Book* book = findBook(bookId);
        User* user = findUser(userId);

        if (book && user && book->isAvailable()) {
            book->borrowBook();
            user->borrowBook(bookId);
            cout << "Book borrowed successfully.\n";
        } else {
            cout << "Borrowing failed.\n";
        }
    }

    void returnBook(int userId, int bookId) {
        Book* book = findBook(bookId);
        User* user = findUser(userId);

        if (book && user) {
            book->returnBook();
            user->returnBook(bookId);
            cout << "Book returned successfully.\n";
        } else {
            cout << "Return failed.\n";
        }
    }

    void searchByTitle(string title) {
        for (auto &book : books) {
            if (book.getTitle() == title) {
                cout << "Found: " << book.getTitle()
                     << " by " << book.getAuthor() << endl;
            }
        }
    }
};

//TEST CASES
int main() {
    Library library;

    // Add books
    library.addBook(1, "Effective C++", "Scott Meyers");
    library.addBook(2, "Data Structures", "Mark Weiss");

    // Register users
    library.registerUser(101, "George");
    library.registerUser(102, "Wainaina");

    // Test borrowing
    library.borrowBook(101, 1);
    library.borrowBook(102, 1); // negative case

    // Test return
    library.returnBook(101, 1);

    // Search test
    library.searchByTitle("C++ Programming");

    return 0;
}
