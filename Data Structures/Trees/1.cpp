#include <bits/stdc++.h>
using namespace std;

#define fli(i, fc, n) for (int i = fc; i < n; i++)
#define rli(i, n, rc) for (int i = n; i > rc; i--)
#define sz(a) a.size()
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define nl "\n"
#define ff first
#define ss second

clock_t s = clock();

// --- AVL Tree ---
struct Node
{
    int val;
    Node *llink;
    Node *rlink;
    int height;
    Node(int x)
    {
        val = x;
        llink = nullptr;
        rlink = nullptr;
        height = 1;
    }
};

class AVLTree
{
    Node *root = nullptr;

public:
    int height(Node *p)
    {
        if (p == nullptr)
            return 0;
        return p->height;
    }
    int bf(Node *p)
    {
        if (p == nullptr)
            return 0;
        return (height(p->llink) - height(p->rlink));
    }
    Node *rightrotate(Node *y)
    {
        Node *x = y->llink;
        Node *T2 = x->rlink;
        x->rlink = y;
        y->llink = T2;
        y->height = max(height(y->llink), height(y->rlink)) + 1;
        x->height = max(height(x->llink), height(x->rlink)) + 1;
        return x;
    }
    Node *leftrotate(Node *x)
    {
        Node *y = x->rlink;
        Node *T2 = y->llink;
        y->llink = x;
        x->rlink = T2;
        x->height = max(height(x->llink), height(x->rlink)) + 1;
        y->height = max(height(y->llink), height(y->rlink)) + 1;
        return y;
    }
    Node *insert(Node *p, int key)
    {
        if (p == NULL)
            return new Node(key);
        if (key < p->val)
            p->llink = insert(p->llink, key);
        else if (key > p->val)
            p->rlink = insert(p->rlink, key);
        else
            return p;
        p->height = 1 + max(height(p->llink), height(p->rlink));
        int balance = bf(p);
        if (balance > 1 && key < p->llink->val)
            return rightrotate(p);
        if (balance < -1 && key > p->rlink->val)
            return leftrotate(p);
        if (balance > 1 && key > p->llink->val)
        {
            p->llink = leftrotate(p->llink);
            return rightrotate(p);
        }
        if (balance < -1 && key < p->rlink->val)
        {
            p->rlink = rightrotate(p->rlink);
            return leftrotate(p);
        }
        return p;
    }
    Node *del(Node *p, int key)
    {
        if (p == NULL)
            return p;
        if (key < p->val)
            p->llink = del(p->llink, key);
        else if (key > p->val)
            p->rlink = del(p->rlink, key);
        else
        {
            if ((p->llink == NULL) || (p->rlink == NULL))
            {
                Node *temp = p->llink ? p->llink : p->rlink;
                if (temp == NULL)
                {
                    temp = p;
                    p = NULL;
                }
                else
                    *p = *temp;
                delete temp;
            }
            else
            {
                Node *temp = p->rlink;
                while (temp->llink != NULL)
                    temp = temp->llink;
                p->val = temp->val;
                p->rlink = del(p->rlink, temp->val);
            }
        }
        if (p == NULL)
            return p;
        p->height = 1 + max(height(p->llink), height(p->rlink));
        int balance = bf(p);
        if (balance > 1 && bf(p->llink) >= 0)
            return rightrotate(p);
        if (balance > 1 && bf(p->llink) < 0)
        {
            p->llink = leftrotate(p->llink);
            return rightrotate(p);
        }
        if (balance < -1 && bf(p->rlink) <= 0)
            return leftrotate(p);
        if (balance < -1 && bf(p->rlink) > 0)
        {
            p->rlink = rightrotate(p->rlink);
            return leftrotate(p);
        }
        return p;
    }
    void inorder(Node *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            cout << p->val << " ";
            inorder(p->rlink);
        }
    }
    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = del(root, key); }
    void display()
    {
        cout << "Inorder: ";
        inorder(root);
        cout << nl;
    }
};

// --- Binary Search Tree ---
class BT
{
    Node *root = nullptr;
    int height(Node *p)
    {
        if (p == nullptr)
            return 0;
        else
            return 1 + std::max(height(p->llink), height(p->rlink));
    }
    void inorder(Node *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            cout << p->val << " ";
            inorder(p->rlink);
        }
    }
    void postorder(Node *p)
    {
        if (p != NULL)
        {
            postorder(p->llink);
            postorder(p->rlink);
            cout << p->val << " ";
        }
    }
    void preorder(Node *p)
    {
        if (p != NULL)
        {
            cout << p->val << " ";
            preorder(p->llink);
            preorder(p->rlink);
        }
    }
    Node *deleteHelper(Node *p, int x)
    {
        if (p == NULL)
        {
            cout << "Node not found" << nl;
            return NULL;
        }
        if (p->val > x)
            p->llink = deleteHelper(p->llink, x);
        else if (p->val < x)
            p->rlink = deleteHelper(p->rlink, x);
        else
        {
            if (p->llink == nullptr && p->rlink == nullptr)
            {
                delete p;
                return NULL;
            }
            else if (p->llink == NULL)
            {
                Node *temp = p->rlink;
                delete p;
                return temp;
            }
            else if (p->rlink == NULL)
            {
                Node *temp = p->llink;
                delete p;
                return temp;
            }
            else
            {
                Node *curr = p->rlink;
                Node *trail = p;
                while (curr->llink != NULL)
                {
                    trail = curr;
                    curr = curr->llink;
                }
                p->val = curr->val;
                if (trail == p)
                    p->rlink = curr->rlink;
                else
                    trail->llink = curr->rlink;
                delete curr;
                return p;
            }
        }
        return p;
    }

public:
    BT() { root = NULL; }
    bool isEmpty(Node *p) { return root == NULL; }
    int calculateheight() { return height(root); }
    void in() { inorder(root); }
    void post()
    {
        postorder(root);
        cout << nl;
    }
    void pre()
    {
        preorder(root);
        cout << nl;
    }
    void deleteNode(int x) { root = deleteHelper(root, x); }
    bool search(int x)
    {
        Node *current;
        bool found = false;
        if (root == NULL)
            return false;
        else
        {
            current = root;
            while (current != NULL && !found)
            {
                if (current->val == x)
                    found = true;
                else if (current->val > x)
                    current = current->llink;
                else
                    current = current->rlink;
            }
        }
        return found;
    }
    void insert(int x)
    {
        Node *curr;
        Node *trail;
        Node *newNode;
        newNode = new Node(x);
        if (root == NULL)
            root = newNode;
        else
        {
            curr = root;
            while (curr != nullptr)
            {
                trail = curr;
                if (curr->val == x)
                {
                    cout << "duplicate" << nl;
                    return;
                }
                else if (curr->val > x)
                    curr = curr->llink;
                else
                    curr = curr->rlink;
            }
            if (trail->val > x)
                trail->llink = newNode;
            else
                trail->rlink = newNode;
        }
    }
};

// --- Graph ---
class Graph
{
protected:
    int maxSize;
    int gSize;
    vector<vector<pair<int, int>>> graph;

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
            graph[i].clear();
        gSize = 0;
    }
    ~Graph() { clearGraph(); }
    void createGraph()
    {
        int numV, numE, v1, v2;
        cout << "enter num of v";
        cin >> numV;
        gSize = numV;
        graph.assign(gSize, vector<pair<int, int>>());
        cout << "enter num of E";
        cin >> numE;
        for (int i = 0; i < numE; i++)
        {
            int w;
            cout << "enter edge (source dest weight)";
            cin >> v1 >> v2 >> w;
            if (v1 < gSize && v2 < gSize)
                graph[v1].push_back({v2, w});
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
            if (!visited[curr])
            {
                visited[curr] = true;
                cout << curr << " ";
                for (int i = graph[curr].size() - 1; i >= 0; i--)
                {
                    int neighbor = graph[curr][i].first;
                    if (!visited[neighbor])
                        s.push(neighbor);
                }
            }
        }
        cout << nl;
    }
    void dijkstra(int startNode)
    {
        if (startNode >= gSize)
        {
            cout << "Invalid start node" << endl;
            return;
        }
        vector<int> dist(gSize, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[startNode] = 0;
        pq.push({0, startNode});
        while (!pq.empty())
        {
            int currentDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (currentDist > dist[u])
                continue;
            for (const auto &neighborPair : graph[u])
            {
                int v = neighborPair.first;
                int weight = neighborPair.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        cout << "--- Dijkstra Shortest Paths from Node " << startNode << " ---" << nl;
        cout << "Vertex\t\tDistance" << nl;
        for (int i = 0; i < gSize; i++)
        {
            cout << i << "\t\t";
            if (dist[i] == INT_MAX)
                cout << "INF";
            else
                cout << dist[i];
            cout << nl;
        }
    }
    void printGraph() const
    {
        for (int i = 0; i < gSize; i++)
        {
            cout << i << "--->";
            for (const auto &neighbour : graph[i])
                cout << "(" << neighbour.first << ",w=" << neighbour.second << ") ";
            cout << nl;
        }
    }
};

// --- Hash Chaining ---
class HashChaining
{
    int BUCKETS;
    list<int> *table;

public:
    HashChaining(int size)
    {
        BUCKETS = size;
        table = new list<int>[BUCKETS];
    }
    ~HashChaining() { delete[] table; }
    int hashFunction(int key) { return key % BUCKETS; }
    void insertItem(int key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }
    void deleteItem(int key)
    {
        int index = hashFunction(key);
        list<int>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            if (*i == key)
            {
                table[index].erase(i);
                cout << "Deleted " << key << " from index " << index << nl;
                return;
            }
        }
        cout << "Element " << key << " not found to delete." << nl;
    }
    bool searchItem(int key)
    {
        int index = hashFunction(key);
        for (auto x : table[index])
            if (x == key)
                return true;
        return false;
    }
    void displayHash()
    {
        cout << "--- Hash Table (Chaining) ---" << nl;
        for (int i = 0; i < BUCKETS; i++)
        {
            cout << i << " --> ";
            for (auto x : table[i])
                cout << x << " -> ";
            cout << "NULL" << nl;
        }
    }
};

// --- QuickSort ---
class QuickSort
{
public:
    int partition(int A[], int low, int high)
    {
        int pivot = A[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (A[j] <= pivot)
            {
                i++;
                swap(A[i], A[j]);
            }
        }
        swap(A[i + 1], A[high]);
        return i + 1;
    }
    void sort(int A[], int low, int high)
    {
        if (low < high)
        {
            int partidx = partition(A, low, high);
            sort(A, low, partidx - 1);
            sort(A, partidx + 1, high);
        }
    }
};

// --- MergeSort ---
class MergeS
{
public:
    void merge(int A[], int low, int high, int mid)
    {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int left[n1];
        int right[n2];
        for (int i = 0; i < n1; i++)
            left[i] = A[low + i];
        for (int j = 0; j < n2; j++)
            right[j] = A[mid + 1 + j];
        int i = 0;
        int j = 0;
        int k = low;
        while (i < n1 && j < n2)
        {
            if (left[i] <= right[j])
                A[k++] = left[i++];
            else
                A[k++] = right[j++];
        }
        while (i < n1)
            A[k++] = left[i++];
        while (j < n2)
            A[k++] = right[j++];
    }
    void sort(int A[], int low, int high)
    {
        if (low < high)
        {
            int mid = (low + high) / 2;
            sort(A, low, mid);
            sort(A, mid + 1, high);
            merge(A, low, high, mid);
        }
    }
};

void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << nl;
}                                                      