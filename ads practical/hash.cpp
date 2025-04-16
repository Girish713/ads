/*Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number.
 Make use of linear probing collision handling techniques
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TelephoneBook {
    struct Entry {
        string name;
        string phoneNumber;
        bool isOccupied;  // To mark if the slot is occupied
        bool isDeleted;   // To mark if the entry is deleted
    };

    vector<Entry> table;
    int size;

    // Hash function to compute index from name
    int hashFunction(const string& name) {
        int hashValue = 0;
        for (char ch : name) {
            hashValue += ch;
        }
        return hashValue % size;
    }

public:
    TelephoneBook(int n) {
        size = n;
        table.resize(size);
        for (int i = 0; i < size; ++i) {
            table[i].isOccupied = false;
            table[i].isDeleted = false;
        }
    }

    void insert(const string& name, const string& phoneNumber) {
        int index = hashFunction(name);
        int startIdx = index;  // Save the original index to avoid infinite loop

        // Linear probing to handle collisions
        while (table[index].isOccupied && !table[index].isDeleted) {
            index = (index + 1) % size;  // Move to the next index
            if (index == startIdx) {
                cout << "Table is full, cannot insert!" << endl;
                return;
            }
        }

        // Insert the new entry
        table[index].name = name;
        table[index].phoneNumber = phoneNumber;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        cout << "Inserted: " << name << " - " << phoneNumber << endl;
    }

    void search(const string& name) {
        int index = hashFunction(name);
        int startIdx = index;  // Save the original index to avoid infinite loop

        // Linear probing to handle collisions
        while (table[index].isOccupied) {
            if (table[index].name == name && !table[index].isDeleted) {
                cout << "Found: " << name << " - " << table[index].phoneNumber << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == startIdx) {
                break;  // Avoid infinite loop if all slots have been checked
            }
        }
        cout << "Not found: " << name << endl;
    }

    void deleteEntry(const string& name) {
        int index = hashFunction(name);
        int startIdx = index;

        // Linear probing to handle collisions
        while (table[index].isOccupied) {
            if (table[index].name == name && !table[index].isDeleted) {
                table[index].isDeleted = true;
                cout << "Deleted: " << name << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == startIdx) {
                break;
            }
        }
        cout << "Not found: " << name << endl;
    }

    void display() {
        cout << "\nTelephone Book Entries:\n";
        for (int i = 0; i < size; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted) {
                cout << table[i].name << " - " << table[i].phoneNumber << endl;
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter the size of the hash table: ";
    cin >> n;

    TelephoneBook tb(n);

    // Insert some telephone book entries
    tb.insert("Alice", "123-456-7890");
    tb.insert("Bob", "234-567-8901");
    tb.insert("Charlie", "345-678-9012");
    tb.insert("David", "456-789-0123");

    // Search for an entry
    tb.search("Bob");
    tb.search("Eve");

    // Delete an entry
    tb.deleteEntry("Charlie");

    // Display the current telephone book
    tb.display();

    return 0;
}
