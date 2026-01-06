#include <bits/stdc++.h>
#include <algorithm>
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
    int data;    // data of node
    Node *llink; // pointer to left child
    Node *rlink; // ptr to rt child
    Node(int val)
    {
        data = val;
        llink = nullptr;
        rlink = nullptr;
    }
};

class BT
{
private:
    Node *root = NULL;

    int height(Node *p)
    {
        if (p == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + std::max(height(p->llink), height(p->rlink));
        }
    }

    // in order left root right

    void inorder(Node *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            cout << p->data << " ";
            inorder(p->rlink);
        }
    }

    void preorder(Node *p)
    {
        if (p != NULL)
        {
            cout << p->data << " ";
            preorder(p->llink);
            preorder(p->rlink);
        }
    }

    void postorder(Node *p)
    {
        if (p != NULL)
        {
            postorder(p->llink);
            postorder(p->rlink);
            cout << p->data << " ";
        }
    }

    void deletefromTree(Node *&p)
    {
        Node *curr;
        Node *trail;
        Node *temp;

        if (p == NULL)
        {
            cout << "Null node";
        }

        else if (p->llink == NULL && p->rlink == NULL)
        {
            temp = p;
            p = NULL;
            delete temp;
        }

        else if (p->llink == NULL)
        {
            temp = p;
            p = temp->rlink;
            delete temp;
        }

        else if (p->rlink == NULL)
        {
            temp = p;
            p = temp->llink;
            delete temp;
        }

        else
        {

            curr = p->llink;
            trail = NULL;
            while (curr->rlink != NULL)
            {
                trail = curr;
                curr = curr->rlink;
            } // end while
            p->data = curr->data;
            if (trail == NULL) // current did not move;
                // current == p->llink; adjust p
                p->llink = curr->llink;
            else
                trail->rlink = curr->llink;
        }
    }

public:
    BT()
    {
        root = NULL;
    }

    bool isEmpty(Node *p)
    {
        return root == NULL;
    }

    int calculateHeight()
    {
        return height(root);
    }

    void in()
    {
        std::cout << "Inorder Traversal: ";
        inorder(root);
        std::cout << "\n";
    }

    void pre()
    {
        std::cout << "Preorder Traversal: ";
        preorder(root);
        std::cout << "\n";
    }

    void post()
    {
        std::cout << "Postorder Traversal: ";
        postorder(root);
        std::cout << "\n";
    }

    bool search(int val)
    {
        Node *current;
        bool found = false;

        if (root == NULL)
        {
            return false;
        }

        else
        {
            current = root;
            while (current != NULL && !found)
            {
                if (current->data == val)
                {
                    found = true;
                }
                else if (current->data > val)
                {
                    current = current->llink;
                }

                else
                {
                    current = current->rlink;
                }
            }
        }

        return found;
    }

    void insert(int val)
    {
        Node *curr;
        Node *trail;
        Node *newNode;

        newNode = new Node(val);

        if (root == NULL)
        {
            root = newNode;
        }

        else
        {
            curr = root;

            while (curr != NULL)
            {
                trail = curr;

                if (curr->data == val)
                {
                    cout << "duplicate\n";
                    return;
                }

                else if (curr->data > val)
                {
                    curr = curr->llink;
                }

                else
                {
                    curr = curr->rlink;
                }
            }

            if (trail->data > val)
                trail->llink = newNode;
            else
                trail->rlink = newNode;
        }
    }

    void deleteNode(int val)
    {
        Node *curr;
        Node *trail;
        bool found = false;

        if (root == NULL)
        {
            cout << "empty tree";
        }

        else
        {
            curr = root;
            trail = root;

            while (curr != NULL && !found)
            {
                if (curr->data == val)
                {
                    found = true;
                }

                else
                {
                    trail = curr;
                    if (curr->data > val)
                        curr = curr->llink;
                    else
                        curr = curr->rlink;
                }
            }

            if (curr == NULL)
            {
                cout << "item not in tree";
            }

            else if (found)
            {
                if (curr == root)
                {
                    deletefromTree(root);
                }

                else if (trail->data > val)
                    deletefromTree(trail->llink);
                else
                    deletefromTree(trail->rlink);
            }
        }
    }
};

// 2024302

void solve()
{
    BT tree;

    cout << "--- Binary Search Tree Operations ---\n";
    cout << "1. Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(30); // Test duplicate

    cout << "\n2. Traversal Results:\n";
    tree.in(); // Expected: 20 30 40 50 60 70 80
    tree.pre();
    tree.post();
    cout << "Tree Height: " << tree.calculateHeight() << "\n";

    cout << "\n3. Search Test:\n";
    cout << "Searching for 40: " << (tree.search(40) ? "Found" : "Not Found") << "\n";
    cout << "Searching for 99: " << (tree.search(99) ? "Found" : "Not Found") << "\n";

    cout << "\n4. Deletion Tests:\n";

    // Test Case A: Delete a leaf node (20)
    tree.deleteNode(20);
    cout << "After deleting 20: ";
    tree.in();

    // Test Case B: Delete a node with one child (70)
    tree.deleteNode(70);
    cout << "After deleting 70: ";
    tree.in(); // Should show 80 is now the right child of 50

    // Test Case C: Delete the root with two children (50) - replaced by 60
    tree.deleteNode(50);
    cout << "After deleting root 50: ";
    tree.in(); // Expected: 30 40 60 80 (Root is now 60)
    cout << "Current Tree Height: " << tree.calculateHeight() << "\n";

    // Test Case D: Delete a non-existent item (99)
    tree.deleteNode(99);
}

int main()
{
    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}