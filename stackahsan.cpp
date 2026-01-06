#include <iostream>
using namespace std;

#define MAX 5

class Queue
{

private:
    int data[MAX], front, rear;

public:
    Queue()
    {

        front = -1;
        rear = -1;
    }

    bool IsEmpty()
    {

        return (front == -1 || front > rear);
    }

    bool IsFull()
    {

        return rear == MAX - 1;
    }

    void Enqueue(int value)
    {

        if (IsFull())
        {

            cout << "The Queue is Empty" << endl;
            return;
        }

        if (front == -1)
            front = 0;

        data[++rear] = value;
    }

    void display()
    {

        if (IsEmpty())
        {

            cout << "The Stack is Empty" << endl;
            return;
        }

        for (int i = 0; i <= rear; i++)
        {
            cout << data[i] << " ";
        }

        cout << endl;
    }
};

int main()
{

    Queue q1;
    q1.Enqueue(10);
    q1.Enqueue(20);
    q1.Enqueue(30);
    q1.Enqueue(40);
    q1.display();

    return 0;
}