#include <iostream>
using namespace std;

#include <iostream>
using namespace std;

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

class MyQueue
{
public:
    Node *rear;
    Node *front;

    MyQueue() : front(nullptr), rear(nullptr) {}

    void push(int x)
    {
        Node *newNode = new Node(x);

        if (rear == NULL)
        {
            rear = newNode;
            rear->next = nullptr;
            front = rear;
        }

        else
        {
            rear->next = newNode;
            newNode->next = nullptr;
            rear = newNode;
        }
    }

    int pop()
    {
        int x = front->val;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        return x;
    }

    bool empty()
    {
        if (front == nullptr)
        {
            return true;
        }
        return false;
    }

    int peek()
    {
        return front->val;
    }
};