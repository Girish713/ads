/*Develop a system for an online bookstore to manage its catalog using binary search trees (BSTs).
 Allow operations like adding new books, deleting for books by title or author efficiently, 
 and updating book information. Display post oredr
*/
#include <iostream>
using namespace std;

struct Book {
    string title;
    string author;
    float price;
    Book* left;
    Book* right;

    Book(string t, string a, float p) : title(t), author(a), price(p), left(nullptr), right(nullptr) {}
};

class BookStore {
    Book* root = nullptr;

    Book* insert(Book* node, string t, string a, float p) {
        if (!node) return new Book(t, a, p);
        if (t < node->title)
            node->left = insert(node->left, t, a, p);
        else if (t > node->title)
            node->right = insert(node->right, t, a, p);
        return node;
    }

    Book* minValue(Book* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Book* deleteBook(Book* node, string t) {
        if (!node) return nullptr;
        if (t < node->title)
            node->left = deleteBook(node->left, t);
        else if (t > node->title)
            node->right = deleteBook(node->right, t);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Book* temp = minValue(node->right);
            node->title = temp->title;
            node->author = temp->author;
            node->price = temp->price;
            node->right = deleteBook(node->right, temp->title);
        }
        return node;
    }

    void postOrder(Book* node) {
        if (!node) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << "Title: " << node->title << ", Author: " << node->author << ", Price: " << node->price << "\n";
    }

    void searchByTitle(Book* node, string t) {
        if (!node) {
            cout << "Book not found!\n";
            return;
        }
        if (t == node->title)
            cout << "Found: " << node->title << ", Author: " << node->author << ", Price: " << node->price << "\n";
        else if (t < node->title)
            searchByTitle(node->left, t);
        else
            searchByTitle(node->right, t);
    }

    void searchByAuthor(Book* node, string a) {
        if (!node) return;
        searchByAuthor(node->left, a);
        if (node->author == a)
            cout << "Title: " << node->title << ", Author: " << node->author << ", Price: " << node->price << "\n";
        searchByAuthor(node->right, a);
    }

    void update(Book* node, string t) {
        if (!node) {
            cout << "Book not found!\n";
            return;
        }
        if (t == node->title) {
            cout << "Enter new author and price: ";
            cin >> node->author >> node->price;
            cout << "Book updated.\n";
        } else if (t < node->title)
            update(node->left, t);
        else
            update(node->right, t);
    }

public:
    void addBook() {
        string t, a;
        float p;
        cout << "Enter title, author and price: ";
        cin >> t >> a >> p;
        root = insert(root, t, a, p);
    }

    void deleteBook() {
        string t;
        cout << "Enter title to delete: ";
        cin >> t;
        root = deleteBook(root, t);
    }

    void searchTitle() {
        string t;
        cout << "Enter title to search: ";
        cin >> t;
        searchByTitle(root, t);
    }

    void searchAuthor() {
        string a;
        cout << "Enter author to search: ";
        cin >> a;
        searchByAuthor(root, a);
    }

    void updateBook() {
        string t;
        cout << "Enter title to update: ";
        cin >> t;
        update(root, t);
    }

    void display() {
        cout << "\nBook Catalog (Post-order):\n";
        postOrder(root);
    }
};

int main() {
    BookStore store;
    int choice;

    do {
        cout << "\n1.Add Book\n2.Delete Book\n3.Search by Title\n4.Search by Author\n5.Update Book\n6.Display\n0.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: store.addBook(); break;
            case 2: store.deleteBook(); break;
            case 3: store.searchTitle(); break;
            case 4: store.searchAuthor(); break;
            case 5: store.updateBook(); break;
            case 6: store.display(); break;
        }
    } while (choice != 0);

    return 0;
}
