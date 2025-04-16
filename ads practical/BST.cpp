/*Develop a system for an online bookstore to manage its catalog using binary search trees (BSTs). 
Allow operations like adding new books, searching for books by title or author efficiently, and updating book information.
*/

#include <iostream>
#include <string>
using namespace std;

// Book Node for BST
struct Book {
    string title;
    string author;
    Book* left;
    Book* right;

    Book(string t, string a) {
        title = t;
        author = a;
        left = right = nullptr;
    }
};

class Bookstore {
private:
    Book* root;

    // Insert book into BST (by title)
    Book* insert(Book* node, string title, string author) {
        if (node == nullptr)
            return new Book(title, author);

        if (title < node->title)
            node->left = insert(node->left, title, author);
        else if (title > node->title)
            node->right = insert(node->right, title, author);
        else
            cout << "Book with this title already exists!\n";

        return node;
    }

    // Search by title
    Book* searchByTitle(Book* node, string title) {
        if (node == nullptr || node->title == title)
            return node;

        if (title < node->title)
            return searchByTitle(node->left, title);
        else
            return searchByTitle(node->right, title);
    }

    // Search by author (may have multiple results)
    void searchByAuthor(Book* node, string author) {
        if (node == nullptr)
            return;

        searchByAuthor(node->left, author);

        if (node->author == author)
            printBook(node);

        searchByAuthor(node->right, author);
    }

    void printBook(Book* book) {
        cout << "Title: " << book->title << ", Author: " << book->author << endl;
    }

public:
    Bookstore() {
        root = nullptr;
    }

    void addBook(string title, string author) {
        root = insert(root, title, author);
        cout << "Book added successfully.\n";
    }

    void findByTitle(string title) {
        Book* book = searchByTitle(root, title);
        if (book)
            printBook(book);
        else
            cout << "Book not found.\n";
    }

    void findByAuthor(string author) {
        cout << "Books by " << author << ":\n";
        searchByAuthor(root, author);
    }

    void updateBook(string title, string newAuthor) {
        Book* book = searchByTitle(root, title);
        if (book) {
            book->author = newAuthor;
            cout << "Book updated successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }
};

// -------- Main Program --------
int main() {
    Bookstore store;
    int choice;
    string title, author;

    do {
        cout << "\n1. Add Book\n2. Search by Title\n3. Search by Author\n4. Update Book\n5. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();  // Clear buffer

        switch (choice) {
            case 1:
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                store.addBook(title, author);
                break;
            case 2:
                cout << "Enter title to search: ";
                getline(cin, title);
                store.findByTitle(title);
                break;
            case 3:
                cout << "Enter author to search: ";
                getline(cin, author);
                store.findByAuthor(author);
                break;
            case 4:
                cout << "Enter title to update: ";
                getline(cin, title);
                cout << "Enter new author: ";
                getline(cin, author);
                store.updateBook(title, author);
                break;
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
