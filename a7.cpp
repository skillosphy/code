#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

class Stack
{
    Node *top;
    int count;

public:
    Stack()
    {
        top = NULL;
    }

    void push(int x)
    {
        Node *temp = new Node(x);
        temp->next = top;
        top = temp;
    }

    int pop()
    {
        Node *temp = top;
        top = top->next;
        int val = temp->data;
        count--;
        delete temp;
        return val;
    }
};

class Queue
{
public:
    Node *rear;
    int count = 0;

    void enqueue(int val)
    {

        Node *temp = new Node(val);

        if (count == 0)
        {
            temp->next = temp;
            rear = temp;
        }
        else
        {
            temp->next = rear->next;
            rear->next = temp;
            rear = temp;
        }

        count++;
        cout << "Enqueued: " << val << endl;
    }

    void display()
    {
        Node *front = rear->next;
        Node *temp = front;
        cout << "Queue contents: ";
        while (temp != rear)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << temp->data;
        cout << endl;
    }
};

void transfer(Stack &s, Queue &q)
{
    int val;
    for (int i = 0; i < 5; i++)
    {
        val = s.pop();
        q.enqueue(val);
    }
}

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    Stack s2;
    int val2;
    for (int i = 0; i < 5; i++)
    {
        val2 = s.pop();
        s2.push(val2);
    }

    Queue q;
    transfer(s2, q);
    q.display();
}