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

class Queue
{
public:
    Node *front;
    Node *rear;

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

        cout << "dequeued: " << temp->data << endl;

        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
    }

    void display()
    {
        Node *temp = front;

        while (temp != NULL)
        {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();

    q.display();
}
