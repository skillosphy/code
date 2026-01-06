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

class MyStack
{

    Node *topp;

public:
    MyStack()
    {
        topp = NULL;
    }

    void push(int x)
    {
        Node *newNode = new Node(x);
        newNode->next = topp;
        topp = newNode;
    }

    int pop()
    {
        int x = topp->val;
        topp = topp->next;

        return x;
    }

    int top()
    {
        return topp->val;
    }

    bool empty()
    {
        if (topp == nullptr)
        {
            return true;
        }
        return false;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->topp();
 * bool param_4 = obj->empty();
 */