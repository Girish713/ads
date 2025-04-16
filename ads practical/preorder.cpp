/*C++ program to implement a threaded binary tree and perform five operations on it: insertion,  search, and display preorder
*/
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool rightThread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        rightThread = false;
    }
};

class ThreadedBinaryTree {
    Node* root;

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int key) {
        Node* ptr = root;
        Node* parent = nullptr;

        while (ptr != nullptr) {
            if (key == ptr->data) {
                cout << "Duplicate value not allowed.\n";
                return;
            }
            parent = ptr;
            if (key < ptr->data)
                ptr = ptr->left;
            else if (!ptr->rightThread)
                ptr = ptr->right;
            else
                break;
        }

        Node* newNode = new Node(key);
        if (!parent)
            root = newNode;
        else if (key < parent->data) {
            newNode->left = nullptr;
            newNode->right = parent;
            newNode->rightThread = true;
            parent->left = newNode;
        } else {
            newNode->left = nullptr;
            newNode->right = parent->right;
            newNode->rightThread = true;
            parent->right = newNode;
            parent->rightThread = false;
        }
    }

    void search(int key) {
        Node* ptr = root;
        while (ptr != nullptr) {
            if (key == ptr->data) {
                cout << "Found: " << key << endl;
                return;
            }

            if (key < ptr->data)
                ptr = ptr->left;
            else if (!ptr->rightThread)
                ptr = ptr->right;
            else
                break;
        }
        cout << "Not found.\n";
    }

    void preorder() {
        Node* ptr = root;
        while (ptr != nullptr) {
            cout << ptr->data << " ";
            if (ptr->left)
                ptr = ptr->left;
            else if (!ptr->rightThread)
                ptr = ptr->right;
            else {
                while (ptr && ptr->rightThread)
                    ptr = ptr->right;
                if (ptr)
                    ptr = ptr->right;
            }
        }
        cout << endl;
    }
};

int main() {
    ThreadedBinaryTree tbt;
    int choice, val;

    do {
        cout << "\n1.Insert\n2.Search\n3.Preorder Display\n0.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tbt.insert(val);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> val;
                tbt.search(val);
                break;
            case 3:
                cout << "Preorder Traversal: ";
                tbt.preorder();
                break;
        }
    } while (choice != 0);

    return 0;
}
