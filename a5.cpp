#include <iostream>
using namespace std;

#define MAX_SIZE 5

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
    Node *rear;
    int count;

    Queue()
    {
        rear = NULL;
        count = 0;
    };

    bool isEmpty()
    {
        if (rear == NULL)
        {
            return true;
        }

        return false;
    }

    void enqueue(int val)
    {
        if (count == MAX_SIZE)
        {
            cout << "Queue overflow" << endl;
            return;
        }

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

    void dequeue()
    {
        if (count == 0)
        {
            cout << "Queue underflow\n";
            return;
        }

        int value;
        if (rear->next == rear)
        {
            value = rear->data;
            delete rear;
            rear = nullptr;
        }
        else
        {
            Node *temp = rear->next;
            value = temp->data;
            rear->next = temp->next;
            delete temp;
        }

        count--;
        cout << "Dequeued: " << value << endl;
    }
};

int main()
{
    Queue q;
    int num;
    int num2;

    cout << "Attempting to queue when queue full: " << endl;
    for (int i = 1; i < 6; i++)
    {
        cout << "Enter integer " << i << endl;
        cin >> num;
        q.enqueue(num);
    }

    cout << "Enter extra integer" << endl;
    cin >> num2;
    q.enqueue(num2);

    cout << "Attempting to delete all and one extra" << endl;

    for (int j = 0; j <= 5; j++)
    {
        q.dequeue();
    }

    return 0;
}