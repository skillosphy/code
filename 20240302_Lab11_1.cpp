// Mohammad Hassaan
// 2024302
// CS
// Lab 11 -- Task 1

#include <bits/stdc++.h>
using namespace std;

class LinearHash
{
    int table_size;
    vector<int> table;
    int EMPTY = -1;

public:
    LinearHash(int ts) : table_size(ts), table(ts, -1) {}

    int hashFunction(int key)
    {
        return key % table_size;
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        // Linear probing: search for next empty slot
        while (table[index] != EMPTY)
        {
            index = (index + 1) % table_size;
        }
        table[index] = key;
    }

    bool search(int key)
    {
        int index = hashFunction(key);
        int startNode = index;
        while (table[index] != EMPTY)
        {
            if (table[index] == key)
                return true;
            index = (index + 1) % table_size;
            if (index == startNode)
                break; // Wrapped around
        }
        return false;
    }

    void display()
    {
        for (int i = 0; i < table_size; i++)
        {
            if (table[i] != EMPTY)
                cout << i << " -> " << table[i] << endl;
            else
                cout << i << " -> " << "Empty" << endl;
        }
    }
};

int main()
{
    int m, n, key, searchKey;
    cout << "enter table size m ";
    cin >> m;
    LinearHash ht(m);

    cout << "enter number of keys to insert ";
    cin >> n;
    cout << "enter " << n << " keys ";
    for (int i = 0; i < n; i++)
    {
        cin >> key;
        ht.insert(key);
    }

    ht.display();

    cout << "enter key to search ";
    cin >> searchKey;
    ht.search(searchKey);
}
