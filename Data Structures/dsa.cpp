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

struct Node
{
    int val;
    Node *next;

    Node(int x)
    {
        val = x;
        next = nullptr;
    }
};

class Stack
{
public:
    Node *top;

    Stack()
    {
        top = nullptr;
    }

    void push(int x)
    {
        Node *newNode = new Node(x);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        Node *temp = top;
        cout << "Popped" << temp->val;
        top = top->next;
    }

    int peek()
    {
        return top->val;
    }

    bool isFull()
    {
    }

    void display()
    {
        Node *temp = top;
        while (temp != NULL)
        {
            cout << temp->val;
            temp = temp->next;
        }
    }
};

class Queue
{
public:
    Node *front;
    Node *rear;

    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    void enqueue(int x)
    {
        Node *newNode = new Node(x);

        if (rear == NULL)
        {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    void dequeue()
    {
        Node *temp = front;
        cout << "dequeued" << temp->val;
        front = front->next;
    }

    void frontt()
    {
        cout << front->val;
    }

    void back()
    {
        cout << rear->val;
    }

    void display()
    {
        Node *temp = front;
        while (temp != NULL)
        {
            cout << temp->val;
            temp = temp->next;
        }
    }
};

int main()
{
    Stack s;

    s.push(5);
    s.pop();
    s.push(1);
    s.peek();
    s.display();

    Queue q;

    q.enqueue(10);
    q.dequeue();
    q.enqueue(20);
    q.frontt();
    q.back();
    q.display();
}