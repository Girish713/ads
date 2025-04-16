/*Optimal Route Planning Application: Create a route planning application that uses graphs to 
represent road networks and Dijkstra's algorithm for finding the shortest path between two locations.
 Allow users to input starting and destination points to get the optimal route.
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
        cities.resize(V);
        adjMatrix.resize(V, vector<int>(V, INF));
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
        adjMatrix[v][u] = w; // Undirected
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix (Distances):\n\t";
        for (int i = 0; i < V; i++) cout << cities[i] << "\t";
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << cities[i] << "\t";
            for (int j = 0; j < V; j++) {
                if (adjMatrix[i][j] == INF)
                    cout << "-\t";
                else
                    cout << adjMatrix[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void dijkstra(int start, int end) {
        vector<int> dist(V, INF);
        vector<int> parent(V, -1);
        vector<bool> visited(V, false);
        dist[start] = 0;

        for (int i = 0; i < V - 1; i++) {
            int u = -1, minDist = INF;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        if (dist[end] == INF) {
            cout << "No route found between " << cities[start] << " and " << cities[end] << ".\n";
            return;
        }

        // Reconstruct path
        vector<int> path;
        for (int v = end; v != -1; v = parent[v])
            path.insert(path.begin(), v);

        cout << "\nShortest path from " << cities[start] << " to " << cities[end] << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << cities[path[i]];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal distance: " << dist[end] << " km\n";
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

    g.displayMatrix();

    int start, end;
    cout << "\nEnter source city index: ";
    cin >> start;
    cout << "Enter destination city index: ";
    cin >> end;

    g.dijkstra(start, end);

    return 0;
}
