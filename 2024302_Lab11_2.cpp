// Mohammad Hassaan
// 2024302
// CS
// Lab 11 -- Task 2

#include <bits/stdc++.h>
using namespace std;

class QuadraticHash
{
    int n;
    vector<int> table;
    int EMPTY = -1;

public:
    QuadraticHash(int size) : n(size), table(size, -1) {}

    int hashFunction(int x)
    {
        return x % n;
    }

    void insert(int key)
    {
        int index = hashFunction(key);
        int i = 0;
        // Search for empty slot using (hash(x) + i^2) % n
        while (table[(index + i * i) % n] != EMPTY)
        {
            cout << "Collision at " << (index + i * i) % n << ", probing" << endl;
            i++;
        }
        table[(index + i * i) % n] = key;
    }

    bool search(int key)
    {
        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % n] != EMPTY)
        {
            if (table[(index + i * i) % n] == key)
                return true;
            i++;
            if (i == n)
                break;
        }
        return false;
    }

    void display()
    {
        for (int i = 0; i < n; i++)
        {
            cout << i << " : " << (table[i] == EMPTY ? "null" : to_string(table[i])) << endl;
        }
    }
};

int main()

{
    int size = 7;
    QuadraticHash ht(size);

    int keys[] = {10, 20, 30, 40}; // Example keys causing collisions
    for (int k : keys)
    {
        ht.insert(k);
    }

    ht.display();
    ht.search(20);
    ht.search(67);

    return 0;
}