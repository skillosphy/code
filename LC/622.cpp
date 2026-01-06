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

// circular queue 


struct Node {
    int val;
    Node* next;

    Node(int x) {
        val = x;
        next = nullptr;
    }
};

class MyCircularQueue {
public:
    Node* rear;
    int size;
    int capacity;

    MyCircularQueue(int k) {
        rear = nullptr;
        size = 0;
        capacity = k;
    }

    bool enQueue(int value) {
        if (isFull()) return false;

        Node* newNode = new Node(value);

        if (isEmpty()) {
            newNode->next = newNode;
            rear = newNode;
        } 
        else {
            newNode->next = rear->next; // new node points to front
            rear->next = newNode;       // old rear points to new node
            rear = newNode;             // update rear
        }

        size++;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;

        // Only one node
        if (rear->next == rear) {
            delete rear;
            rear = nullptr;
        } 
        else {
            Node* temp = rear->next; // front node
            rear->next = temp->next; // skip front
            delete temp;
        }

        size--;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return rear->next->val; // front = rear->next
    }

    int Rear() {
        if (isEmpty()) return -1;
        return rear->val;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};
 