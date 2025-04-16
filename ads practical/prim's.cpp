/*Design a program to represent a transportation network using graphs. 
The program should allow users to input cities and routes between them, 
and then visualize the network graphically. Additionally, it should support operations 
like adding new cities and routes and determining the minimum spanning tree of the entire network.  (Using Prims)
*/
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define INF 999999

class Graph {
    int V;
    vector<string> cities;
    vector<vector<int>> adjMatrix;

public:
    Graph(int v) {
        V = v;
        adjMatrix.resize(V, vector<int>(V, 0));
        cities.resize(V);
    }

    void inputCities() {
        cout << "Enter names of " << V << " cities:\n";
        for (int i = 0; i < V; i++) {
            cout << "City " << i << ": ";
            cin >> cities[i];
        }
    }

    void addRoute(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // undirected graph
    }

    void display() {
        cout << "\nAdjacency Matrix:\n\t";
        for (int i = 0; i < V; i++) cout << cities[i] << "\t";
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << cities[i] << "\t";
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void primMST() {
        vector<int> key(V, INF), parent(V, -1);
        vector<bool> inMST(V, false);
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1, minKey = INF;
            for (int v = 0; v < V; v++)
                if (!inMST[v] && key[v] < minKey)
                    minKey = key[v], u = v;

            inMST[u] = true;

            for (int v = 0; v < V; v++)
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v])
                    key[v] = adjMatrix[u][v], parent[v] = u;
        }

        cout << "\nMinimum Spanning Tree (Prim's):\n";
        int total = 0;
        for (int i = 1; i < V; i++) {
            cout << cities[parent[i]] << " - " << cities[i] << " : " << adjMatrix[i][parent[i]] << " km\n";
            total += adjMatrix[i][parent[i]];
        }
        cout << "Total distance: " << total << " km\n";
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
    for (int i = 0; i < r; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addRoute(u, v, w);
    }

    g.display();
    g.primMST();

    return 0;
}
