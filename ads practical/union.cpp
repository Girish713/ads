/*You are organizing a conference with attendees from different countries. 
Some attendees can speak Spanish, some can speak German, and some can speak both languages.
 Write a program to find the union, intersection, and difference of sets.
*/
#include <iostream>
#include <set>
#include <iterator>
using namespace std;

// Function to print a set
void printSet(const set<string>& s) {
    for (const auto& element : s) {
        cout << element << " ";
    }
    cout << endl;
}

// Function to perform set union
set<string> unionSets(const set<string>& set1, const set<string>& set2) {
    set<string> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}

// Function to perform set intersection
set<string> intersectionSets(const set<string>& set1, const set<string>& set2) {
    set<string> result;
    for (const auto& element : set1) {
        if (set2.find(element) != set2.end()) {
            result.insert(element);
        }
    }
    return result;
}

// Function to perform set difference (set1 - set2)
set<string> differenceSets(const set<string>& set1, const set<string>& set2) {
    set<string> result;
    for (const auto& element : set1) {
        if (set2.find(element) == set2.end()) {
            result.insert(element);
        }
    }
    return result;
}

int main() {
    // Sets representing attendees speaking Spanish and German
    set<string> spanishSpeakers = {"Alice", "Bob", "Charlie", "David", "Eva"};
    set<string> germanSpeakers = {"Bob", "Charlie", "David", "Frank", "Grace"};

    // Display Spanish speakers
    cout << "Spanish Speakers: ";
    printSet(spanishSpeakers);

    // Display German speakers
    cout << "German Speakers: ";
    printSet(germanSpeakers);

    // Union of Spanish and German speakers
    set<string> unionSet = unionSets(spanishSpeakers, germanSpeakers);
    cout << "Union (Spanish or German speakers): ";
    printSet(unionSet);

    // Intersection of Spanish and German speakers
    set<string> intersectionSet = intersectionSets(spanishSpeakers, germanSpeakers);
    cout << "Intersection (Spanish and German speakers): ";
    printSet(intersectionSet);

    // Difference (Spanish speakers who don't speak German)
    set<string> differenceSet1 = differenceSets(spanishSpeakers, germanSpeakers);
    cout << "Difference (Spanish speakers who don't speak German): ";
    printSet(differenceSet1);

    // Difference (German speakers who don't speak Spanish)
    set<string> differenceSet2 = differenceSets(germanSpeakers, spanishSpeakers);
    cout << "Difference (German speakers who don't speak Spanish): ";
    printSet(differenceSet2);

    return 0;
}
