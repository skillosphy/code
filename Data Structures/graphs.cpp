#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
#define fli(i, fc, n) for (int i = fc; i < n; i++)
#define rli(i, n, rc) for (int i = n; i > rc; i--)
#define sz(a) a.size()
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define nl "\n"
using namespace std;
#define ff first
#define ss second

clock_t s = clock();

class graphType
{
protected:
    int maxSize;                          // Maximum number of vertices
    int gSize;                            // Current number of vertices
    vector<vector<pair<int, int>>> graph; // Adjacency list: (neighbor, weight)

public:
    // Constructor
    graphType(int size = 0)
    {
        maxSize = size;
        gSize = 0;
        graph.resize(size);
    }

    // Destructor
    ~graphType()
    {
        clearGraph();
    }

    bool isEmpty() const
    {
        return (gSize == 0);
    }

    // createGraph: Now uses console input instead of a file
    void createGraph()
    {
        int numVertices, numEdges, v1, v2;

        if (gSize != 0)
            clearGraph();

        cout << "Enter number of vertices: ";
        cin >> numVertices;
        gSize = numVertices;
        graph.assign(gSize, vector<pair<int, int>>()); // Reset/Resize the adjacency list

        cout << "Enter number of edges: ";
        cin >> numEdges;

        for (int i = 0; i < numEdges; i++)
        {
            int w;
            cout << "Enter edge (source destination weight): ";
            cin >> v1 >> v2 >> w;
            if (v1 < gSize && v2 < gSize)
            {
                graph[v1].push_back({v2, w});
            }
            else
            {
                cout << "Invalid vertex!" << endl;
                i--; // Retry this edge
            }
        }
    }

    void clearGraph()
    {
        for (int i = 0; i < gSize; i++)
        {
            graph[i].clear();
        }
        gSize = 0;
    }

    void printGraph() const
    {
        for (int i = 0; i < gSize; i++)
        {
            cout << i << " --> ";
            for (const auto &neighbor : graph[i])
            {
                cout << "(" << neighbor.first << ",w=" << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    // --- Traversals ---

    // 1. Full Depth First Traversal
    void depthFirstTraversal()
    {
        vector<bool> visited(gSize, false);
        for (int i = 0; i < gSize; i++)
        {
            if (!visited[i])
            {
                dft(i, visited);
            }
        }
        cout << endl;
    }

    // 2. DFT starting from a specific vertex
    void dftAtVertex(int vertex)
    {
        if (vertex >= gSize)
            return;
        vector<bool> visited(gSize, false);
        dft(vertex, visited);
        cout << endl;
    }

    // Internal recursive helper for DFT
    void dft(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";
        for (const auto &neighbor : graph[v])
        {
            int to = neighbor.first;
            if (!visited[to])
            {
                dft(to, visited);
            }
        }
    }

    // 3. Breadth First Traversal
    void breadthFirstTraversal()
    {
        vector<bool> visited(gSize, false);
        queue<int> q;

        for (int i = 0; i < gSize; i++)
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = true;

                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    cout << u << " ";

                    for (const auto &neighbor : graph[u])
                    {
                        int to = neighbor.first;
                        if (!visited[to])
                        {
                            visited[to] = true;
                            q.push(to);
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    // Dijkstra's algorithm for weighted directed graph
    void dijkstra(int src)
    {
        if (src >= gSize)
            return;
        const int INF = INT_MAX / 4;
        vector<int> dist(gSize, INF);
        dist[src] = 0;
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, src});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u])
                continue;
            for (const auto &edge : graph[u])
            {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from " << src << ":\n";
        for (int i = 0; i < gSize; i++)
        {
            if (dist[i] >= INF)
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};

// 2024302
void solve()
{
}

// driver: create graph, print it, and run Dijkstra
void solve()
{
    graphType g;
    g.createGraph();
    cout << "\nGraph adjacency list:\n";
    g.printGraph();
    cout << "Enter source vertex for Dijkstra: ";
    int src;
    cin >> src;
    cout << "\n";
    g.dijkstra(src);
}

int main()
{
    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}