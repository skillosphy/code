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

// 2024302
void solve()
{
}

class Graph
{
protected:
    int maxSize;                          // max number of vertices
    int gSize;                            // curr num vertices
    vector<vector<pair<int, int>>> graph; // adj list (neighbour, weight)

public:
    Graph(int size = 0)
    {
        maxSize = size;
        gSize = 0;
        graph.resize(size);
    }

    void clearGraph()
    {
        for (int i = 0; i < gSize; i++)
        {
            graph[i].clear();
        }

        gSize = 0;
    }

    ~Graph()
    {
        clearGraph();
    }

    void createGraph()
    {
        int numV, numE, v1, v2;

        cout << "enter num of v";
        cin >> numV;

        gSize = numV;

        graph.assign(gSize, vector<pair<int, int>>()); // reset/resize adj list

        cout << "enter num of E";
        cin >> numE;

        for (int i = 0; i < numE; i++)
        {
            int w;
            cout << "enter edge (source dest weight)";
            cin >> v1 >> v2 >> w;
            if (v1 < gSize && v2 < gSize)
            {
                graph[v1].push_back({v2, w});
            }

            else
                cout << "invalid v" << nl;
        }
    }

    void bfs(int StartNode)
    {
        if (StartNode < 0 || StartNode >= gSize)
            return;

        vector<bool> visited(gSize, false);
        queue<int> q;

        visited[StartNode] = true;
        q.push(StartNode);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (const auto &neighbourPair : graph[curr])
            {
                int neighbour = neighbourPair.first;
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
        cout << nl;
    }

    void dfs(int startNode)
    {
        if (startNode >= gSize)
            return;

        vector<bool> visited(gSize, false);
        stack<int> s;

        s.push(startNode);

        cout << "DFS Traversal: ";

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            // Only process if not visited yet
            if (!visited[curr])
            {
                visited[curr] = true;
                cout << curr << " ";

                // Push neighbors to stack
                // Note: We iterate in REVERSE so the first neighbor is popped first (LIFO)
                for (int i = graph[curr].size() - 1; i >= 0; i--)
                {
                    int neighbor = graph[curr][i].first;
                    if (!visited[neighbor])
                    {
                        s.push(neighbor);
                    }
                }
            }
        }
        cout << nl;
    }

    void printGraph() const
    {
        for (int i = 0; i < gSize; i++)
        {
            cout << i << "--->";

            for (const auto &neighbour : graph[i])
            {
                cout << "(" << neighbour.first << ",w=" << neighbour.second << ") ";
            }

            cout << nl;
        }
    }
};

int main()
{
    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}