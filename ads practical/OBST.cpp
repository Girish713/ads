/*Design a program to implement an Optimal Binary Search Tree (OBST) for a compiler symbol table.
 The program should efficiently store and retrieve identifiers, constants, and keywords encountered during lexical analysis.
*/
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// Structure for the OBST node
struct Node {
    string key;
    Node* left;
    Node* right;
    Node(string k) : key(k), left(nullptr), right(nullptr) {}
};

class OptimalBST {
private:
    vector<string> keys;  // List of symbols (identifiers, constants, keywords)
    vector<double> freq;  // Frequency of access for each symbol
    vector<vector<int>> cost;  // Store the optimal cost
    vector<vector<int>> root;  // Store the root of optimal subtrees

public:
    // Constructor
    OptimalBST(const vector<string>& k, const vector<double>& f) : keys(k), freq(f) {
        int n = keys.size();
        cost.resize(n + 1, vector<int>(n + 1, 0));
        root.resize(n + 1, vector<int>(n + 1, 0));
        
        // Initialize the cost for single symbols
        for (int i = 0; i < n; ++i) {
            cost[i][i] = freq[i];
            root[i][i] = i;
        }

        // Calculate optimal costs for larger subtrees
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                cost[i][j] = INT_MAX;

                // Try each symbol as root and calculate cost
                double sum = 0;
                for (int k = i; k <= j; ++k) {
                    sum += freq[k];
                }

                for (int r = i; r <= j; ++r) {
                    int tempCost = (r > i ? cost[i][r - 1] : 0) + (r < j ? cost[r + 1][j] : 0) + sum;
                    if (tempCost < cost[i][j]) {
                        cost[i][j] = tempCost;
                        root[i][j] = r;
                    }
                }
            }
        }
    }

    // Function to construct the optimal BST recursively
    Node* constructTree(int i, int j) {
        if (i > j) return nullptr;
        int r = root[i][j];
        Node* node = new Node(keys[r]);
        node->left = constructTree(i, r - 1);
        node->right = constructTree(r + 1, j);
        return node;
    }

    // Function to display the OBST in-order (for testing)
    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

    // Function to build and display the optimal BST
    void buildAndDisplay() {
        int n = keys.size();
        Node* rootNode = constructTree(0, n - 1);
        cout << "Inorder traversal of the Optimal Binary Search Tree: ";
        inorder(rootNode);
        cout << endl;
    }

    // Function to search for a key in the OBST
    Node* search(Node* root, const string& key) {
        if (root == nullptr || root->key == key) {
            return root;
        }

        if (key < root->key) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }

    // Function to insert a new symbol into the tree
    void insertSymbol(Node*& root, const string& key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }

        if (key < root->key) {
            insertSymbol(root->left, key);
        } else if (key > root->key) {
            insertSymbol(root->right, key);
        }
    }
};

int main() {
    // Symbols and their access probabilities (frequencies)
    vector<string> symbols = {"int", "float", "char", "while", "if", "return"};
    vector<double> frequencies = {0.15, 0.10, 0.05, 0.30, 0.20, 0.20};

    // Creating the OBST
    OptimalBST obst(symbols, frequencies);
    
    // Display the optimal binary search tree (in-order)
    obst.buildAndDisplay();

    // Example of searching for a symbol
    Node* searchResult = obst.search(obst.constructTree(0, symbols.size() - 1), "while");
    if (searchResult) {
        cout << "Found: " << searchResult->key << endl;
    } else {
        cout << "Symbol not found." << endl;
    }

    return 0;
}
