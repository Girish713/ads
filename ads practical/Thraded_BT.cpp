/*C++ program to implement a threaded binary tree and perform five operations on it: insertion, in-order traversal, display
*/
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool lthread; // true if left pointer is thread
    bool rthread; // true if right pointer is thread

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = true;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;

    // Helper to find leftmost node from a given node
    Node* leftmost(Node* node) {
        if (!node) return nullptr;
        while (!node->lthread)
            node = node->left;
        return node;
    }

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int val) {
        Node* newNode = new Node(val);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            if (val == current->data) {
                cout << "Duplicate value not allowed.\n";
                delete newNode;
                return;
            }

            parent = current;

            if (val < current->data) {
                if (!current->lthread)
                    current = current->left;
                else
                    break;
            } else {
                if (!current->rthread)
                    current = current->right;
                else
                    break;
            }
        }

        if (val < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->lthread = false;
            parent->left = newNode;
        } else {
            newNode->right = parent->right;
            newNode->left = parent;
            parent->rthread = false;
            parent->right = newNode;
        }
    }

    // In-order traversal using threads (no recursion or stack)
    void inorder() {
        Node* current = leftmost(root);
        while (current) {
            cout << current->data << " ";

            if (current->rthread)
                current = current->right;
            else
                current = leftmost(current->right);
        }
        cout << endl;
    }

    // Display the structure (inorder with indicators)
    void display() {
        cout << "In-order Display (Threaded Tree): ";
        inorder();
    }
};

// ----------- MAIN PROGRAM -------------
int main() {
    ThreadedBinaryTree tree;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. In-order Traversal\n3. Display\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;

            case 2:
                cout << "In-order Traversal: ";
                tree.inorder();
                break;

            case 3:
                tree.display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
