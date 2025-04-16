/*Design a program to represent a transportation network using graphs.
 The program should allow users to input cities and routes between them,
  and then visualize the network graphically. Additionally, it should support operations like adding new cities
   and routes and determining the minimum spanning tree of the entire network. (Using Kruskal)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
    int V;
    vector<string> cities;
    vector<Edge> edges;

public:
    Graph(int v) {
        V = v;
        cities.resize(V);
    }

    void inputCities() {
        cout << "Enter names of " << V << " cities:\n";
        for (int i = 0; i < V; ++i) {
            cout << "City " << i << ": ";
            cin >> cities[i];
        }
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    int findParent(vector<int>& parent, int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = findParent(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = findParent(parent, x);
        int yroot = findParent(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void kruskalMST() {
        vector<Edge> result;
        int totalWeight = 0;

        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(V);
        vector<int> rank(V, 0);

        for (int i = 0; i < V; ++i)
            parent[i] = i;

        for (Edge e : edges) {
            int x = findParent(parent, e.src);
            int y = findParent(parent, e.dest);

            if (x != y) {
                result.push_back(e);
                totalWeight += e.weight;
                unionSets(parent, rank, x, y);
            }
        }

        cout << "\nMinimum Spanning Tree (Kruskal's):\n";
        for (Edge e : result)
            cout << cities[e.src] << " - " << cities[e.dest] << " : " << e.weight << " km\n";
        cout << "Total distance: " << totalWeight << " km\n";
    }

    void displayEdges() {
        cout << "\nAll Routes:\n";
        for (Edge e : edges)
            cout << cities[e.src] << " <-> " << cities[e.dest] << " : " << e.weight << " km\n";
    }

    void addNewCity(string name) {
        cities.push_back(name);
        V++;
    }

    int getCityCount() {
        return V;
    }

    void displayCityList() {
        cout << "\nCities:\n";
        for (int i = 0; i < V; ++i)
            cout << i << ": " << cities[i] << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    Graph g(n);
    g.inputCities();

    int r;
    cout << "Enter number of routes: ";
    cin >> r;
    cout << "Enter each route as: from_index to_index distance\n";
    for (int i = 0; i < r; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int choice;
    do {
        cout << "\n1. Display all routes\n2. Add new city\n3. Add new route\n4. Show MST (Kruskal)\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                g.displayEdges();
                break;
            case 2: {
                string city;
                cout << "Enter new city name: ";
                cin >> city;
                g.addNewCity(city);
                break;
            }
            case 3: {
                g.displayCityList();
                int u, v, w;
                cout << "Enter from_index to_index distance: ";
                cin >> u >> v >> w;
                g.addEdge(u, v, w);
                break;
            }
            case 4:
                g.kruskalMST();
                break;
        }
    } while (choice != 0);

    return 0;
}
