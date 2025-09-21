#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
using namespace std;

typedef pair<int, int> Edge; // {cost, node}

// Function to perform Dijkstra's Algorithm
void dijkstra(unordered_map<int, vector<Edge>>& graph, int start, int end, int vertices) {
    vector<int> dist(vertices, numeric_limits<int>::max());
    vector<int> parent(vertices, -1);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto [weight, v] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Output shortest distance
    if (dist[end] == numeric_limits<int>::max()) {
        cout << "No path exists from " << start << " to " << end << endl;
        return;
    }

    cout << "Shortest distance from " << start << " to " << end << " is: " << dist[end] << endl;

    // Reconstruct shortest path
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    cout << "Path: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    unordered_map<int, vector<Edge>> graph;

    // Example graph (undirected)
    // Each edge is stored as {weight, neighbor}
    graph[0] = {{4, 1}, {1, 2}};
    graph[1] = {{4, 0}, {2, 2}, {6, 3}};
    graph[2] = {{1, 0}, {2, 1}, {3, 3}};
    graph[3] = {{6, 1}, {3, 2}};

    int start, end;
    cout << "Enter start node (0-3): ";
    cin >> start;
    cout << "Enter end node (0-3): ";
    cin >> end;

    dijkstra(graph, start, end, 4);

    return 0;
}
