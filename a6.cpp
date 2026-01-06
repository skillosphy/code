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

class LinkedList
{
public:
    Node *head = NULL;

    void insert()
    {
        int n;
        cout << "enter the number of student roll numbers you want to add" << endl;
        cin >> n;
        int val;
        for (int i = 1; i <= n; i++)
        {
            cout << "enter roll no for student " << i << endl;
            cin >> val;

            Node *newNode = new Node(val);

            if (head == NULL)
            {
                head = newNode;
            }

            else
            {
                Node *temp = head;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = newNode;
            }
        }
    }

    void insertnew()
    {
        int roll = 1;
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->data % 2 == 0)
            {
                Node *newNode = new Node(roll);
                newNode->next = temp->next;
                temp->next = newNode;

                temp = temp->next;
                roll++;
            }

            else
            {
                temp = temp->next;
            }
        }
    }

    void display()
    {
        Node *temp = head;
        cout << "roll numbers";
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{
    LinkedList stu;
    stu.insert();
    stu.insertnew();
    stu.display();
}