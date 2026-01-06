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
        count = 0;
    }

    void push(int x)
    {
        Node *temp = new Node(x);
        temp->next = top;
        top = temp;
        count++;
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

    void display()
    {
        Node *temp = top;
        while (temp != NULL)
        {
            cout << temp->data;
            temp = temp->next;
        }
    }

    void evenpop()
    {

        Stack odd;

        while (top != NULL)
        {
            if (top->data % 2 == 0)
            {
                cout << "even number popped " << pop() << endl;
            }

            else
            {
                int val = pop();
                odd.push(val);
            }
        }

        cout << "stack after even numbers popped" << endl;
        while (odd.top != NULL)
        {
            push(odd.pop());
        }
    }
};

int main()

{
    Stack s;
    int num;
    for (int i = 1; i < 11; i++)
    {
        cout << "Input integer " << i << endl;
        cin >> num;
        s.push(num);
    }

    s.evenpop();
    s.display();

    return 0;
}