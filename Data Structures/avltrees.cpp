#include <bits/stdc++.h>
using namespace std;

#define nl "\n"

struct Node
{
    int val;
    Node *llink;
    Node *rlink;
    int height;

    Node(int x)
    {
        val = x;
        llink = nullptr;
        rlink = nullptr;
        height = 1;
    }
};

class AVLTree
{
    Node *root = nullptr;

public:
    int height(Node *p)
    {
        if (p == nullptr)
            return 0;
        return p->height;
    }

    int bf(Node *p)
    {
        if (p == nullptr)
            return 0;
        return (height(p->llink) - height(p->rlink));
    }

    // --- Rotations ---

    Node *rightrotate(Node *y)
    {
        Node *x = y->llink;
        Node *T2 = x->rlink;

        // Perform rotation
        x->rlink = y;
        y->llink = T2;

        // Update heights
        y->height = max(height(y->llink), height(y->rlink)) + 1;
        x->height = max(height(x->llink), height(x->rlink)) + 1;

        // Return new root
        return x;
    }

    Node *leftrotate(Node *x)
    {
        Node *y = x->rlink;
        Node *T2 = y->llink;

        // Perform rotation
        y->llink = x;
        x->rlink = T2;

        // Update heights
        x->height = max(height(x->llink), height(x->rlink)) + 1;
        y->height = max(height(y->llink), height(y->rlink)) + 1;

        return y;
    }

    // --- Insertion ---
    Node *insert(Node *p, int key)
    {
        // 1. Perform normal BST insertion
        if (p == NULL)
            return new Node(key);

        if (key < p->val)
            p->llink = insert(p->llink, key);
        else if (key > p->val)
            p->rlink = insert(p->rlink, key);
        else // Equal keys are not allowed in BST
            return p;

        // 2. Update height of this ancestor node
        p->height = 1 + max(height(p->llink), height(p->rlink));

        // 3. Get the balance factor
        int balance = bf(p);

        // 4. If unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < p->llink->val)
            return rightrotate(p);

        // Right Right Case
        if (balance < -1 && key > p->rlink->val)
            return leftrotate(p);

        // Left Right Case
        if (balance > 1 && key > p->llink->val)
        {
            p->llink = leftrotate(p->llink);
            return rightrotate(p);
        }

        // Right Left Case
        if (balance < -1 && key < p->rlink->val)
        {
            p->rlink = rightrotate(p->rlink);
            return leftrotate(p);
        }

        return p;
    }

    // --- Deletion (FIXED) ---
    Node *del(Node *p, int key)
    {
        // 1. Standard BST delete
        if (p == NULL)
            return p;

        if (key < p->val)
            p->llink = del(p->llink, key);
        else if (key > p->val)
            p->rlink = del(p->rlink, key);
        else
        {
            // Node found

            // Case 1 & 2: One child or No child
            if ((p->llink == NULL) || (p->rlink == NULL))
            {
                Node *temp = p->llink ? p->llink : p->rlink;

                // No child case
                if (temp == NULL)
                {
                    temp = p;
                    p = NULL;
                }
                else            // One child case
                    *p = *temp; // Copy the contents of the non-empty child

                delete temp;
            }
            else
            {
                // Case 3: Two children
                // Get the inorder successor (smallest in the right subtree)
                Node *temp = p->rlink;
                while (temp->llink != NULL)
                    temp = temp->llink;

                // Copy the inorder successor's data to this node
                p->val = temp->val;

                // Delete the inorder successor RECURSIVELY
                // This ensures balancing happens all the way back up
                p->rlink = del(p->rlink, temp->val);
            }
        }

        // If the tree had only one node then return
        if (p == NULL)
            return p;

        // 2. Update height of the current node
        p->height = 1 + max(height(p->llink), height(p->rlink));

        // 3. Get the balance factor
        int balance = bf(p);

        // 4. Balance the tree (Using BF checks, NOT key checks)

        // Left Left Case
        if (balance > 1 && bf(p->llink) >= 0)
            return rightrotate(p);

        // Left Right Case
        if (balance > 1 && bf(p->llink) < 0)
        {
            p->llink = leftrotate(p->llink);
            return rightrotate(p);
        }

        // Right Right Case
        if (balance < -1 && bf(p->rlink) <= 0)
            return leftrotate(p);

        // Right Left Case
        if (balance < -1 && bf(p->rlink) > 0)
        {
            p->rlink = rightrotate(p->rlink);
            return leftrotate(p);
        }

        return p;
    }

    // --- Utility Functions ---
    void inorder(Node *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            cout << p->val << " ";
            inorder(p->rlink);
        }
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    void remove(int key)
    {
        root = del(root, key);
    }

    void display()
    {
        cout << "Inorder: ";
        inorder(root);
        cout << nl;
    }
};

int main()
{
    AVLTree t;

    // Test Case
    t.insert(10);
    t.insert(30);
    t.insert(40);
    t.insert(75);
    t.insert(90);

    cout << "Original Tree:" << nl;
    t.display();

    cout << "Deleting 75 (Testing deletion):" << nl;
    t.remove(75);

    t.display();

    return 0;
}