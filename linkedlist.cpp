#include <iostream>
using namespace std;

// linked list implementation

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

    void insert(int x)
    {
        Node *temp = new Node(x);
        if (head == NULL)
        {
            head = temp;
        }

        else // inserts at tail
        {
            Node *run = head;
            while (run->next != NULL)
            {
                run = run->next;
            }
            run->next = temp;
        }
    }

    void insert_after(int key, int curr)
    {
        Node *temp = head;
        Node *newNode = new Node(curr);
        while (temp != NULL)
        {
            if (temp->data == key)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        }
    }

    void display()
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << temp->data;
    }

    void reverse()
    {
        Node *curr = head;
        Node *prev = nullptr;
        Node *next = nullptr;

        while (curr)
        {
            next = curr->next; // next pointer one ahead of curr

            curr->next = prev;

            prev = curr;
            curr = next; // Reverse current node's next pointer
        }
        head = prev;
    }

     void reverse_k_nodes(int k)
    {
        if (head == NULL || k <= 1)
            return;

        Node *curr = head;
        Node *next = NULL;
        Node *newHead = NULL;
        Node *prevTail = NULL;

        bool reverseFlag = true;

        while (curr)
        {
            Node *groupHead = curr;
            int count = 0;

            if (reverseFlag)
            {
                // Reverse k nodes
                Node *prev = NULL;
                while (curr && count < k)
                {
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                    count++;
                }

                // Set head for the first reversed group
                if (!newHead)
                    newHead = prev;

                // Connect last group's tail to this group's head
                if (prevTail)
                    prevTail->next = prev;

                // The new tail is the original head of this group
                prevTail = groupHead;
            }
            else
            {
                // Skip k nodes
                while (curr && count < k)
                {
                    prevTail = curr;
                    curr = curr->next;
                    count++;
                }
            }

            reverseFlag = !reverseFlag; // toggle between reverse and skip
        }

        head = newHead;
    }

    int getmid(){
        Node* slow = head;
        Node* fast = head;
        while(fast->next->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    } 
};



int main()
{
    LinkedList l;

    l.insert(10);
    l.insert(20);
    l.insert(30);
    l.insert(40);
    l.insert(50);
    l.insert(60);
    l.insert(70);
    l.insert(80);
    l.insert(90);k
    l.insert(100);
    // l.reverse_k_nodes(3);
    // l.insert_after(1, 3);
    l.display();
    cout << "\nMid = " << l.getmid() << "\n";
}