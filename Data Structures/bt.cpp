#include <bits/stdc++.h>
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

// 2024302
void solve()
{
}

struct Node
{
    int val;
    Node *llink;
    Node *rlink;

    Node(int x)
    {
        val = x;
        llink = nullptr;
        rlink = nullptr;
    }
};

class BT
{
    Node *root = nullptr;

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

    void inorder(Node *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            cout << p->val << " ";
            inorder(p->rlink);
        }
    }

    void postorder(Node *p)
    {
        if (p != NULL)
        {
            postorder(p->llink);
            postorder(p->rlink);
            cout << p->val << " ";
        }
    }

    void preorder(Node *p)
    {
        if (p != NULL)
        {
            cout << p->val << " ";
            preorder(p->llink);
            preorder(p->rlink);
        }
    }

    Node *deleteHelper(Node *p, int x)
    {
        if (p == NULL)
        {
            cout << "Node not found" << nl;
            return NULL;
        }

        // Find the node to delete
        if (p->val > x)
        {
            p->llink = deleteHelper(p->llink, x);
        }
        else if (p->val < x)
        {
            p->rlink = deleteHelper(p->rlink, x);
        }
        else
        {
            // Node found - delete it
            // Case 1: Leaf node
            if (p->llink == nullptr && p->rlink == nullptr)
            {
                delete p;
                return NULL;
            }
            // Case 2: No left child
            else if (p->llink == NULL)
            {
                Node *temp = p->rlink;
                delete p;
                return temp;
            }
            // Case 3: No right child
            else if (p->rlink == NULL)
            {
                Node *temp = p->llink;
                delete p;
                return temp;
            }
            // Case 4: Both children exist - find inorder successor
            else
            {
                Node *curr = p->rlink;
                Node *trail = p;

                while (curr->llink != NULL)
                {
                    trail = curr;
                    curr = curr->llink;
                }

                p->val = curr->val;

                if (trail == p)
                    p->rlink = curr->rlink;
                else
                    trail->llink = curr->rlink;

                delete curr;
                return p;
            }
        }
        return p;
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

    int calculateheight()
    {
        return height(root);
    }

    void in()
    {
        inorder(root);
    }

    void post()
    {
        postorder(root);
        cout << nl;
    }

    void pre()
    {
        preorder(root);
        cout << nl;
    }

    void deleteNode(int x)
    {
        root = deleteHelper(root, x);
    }

    bool search(int x)
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
                if (current->val == x)
                {
                    found = true;
                }

                else if (current->val > x)
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

    void insert(int x)
    {
        Node *curr;
        Node *trail;
        Node *newNode;

        newNode = new Node(x);

        //

        if (root == NULL)
        {
            root = newNode;
        }

        else
        {
            curr = root;

            while (curr != nullptr)
            {
                trail = curr;

                if (curr->val == x)
                {
                    cout << "duplicate" << nl;
                    return;
                }

                else if (curr->val > x)
                {
                    curr = curr->llink;
                }

                else
                {
                    curr = curr->rlink;
                }
            }

            if (trail->val > x)
                trail->llink = newNode;

            else
                trail->rlink = newNode;
        }
    }
};

int main()
{
    solve();

    cout << "=== Binary Search Tree Driver Code ===" << nl << nl;

    // Create a BST
    BT tree;

    cout << "Test 1: Inserting elements into BST" << nl;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
    {
        tree.insert(values[i]);
        cout << "Inserted: " << values[i] << nl;
    }
    cout << nl;

    // Test inorder traversal
    cout << "Test 2: Inorder Traversal (should be sorted)" << nl;
    cout << "Inorder: ";
    tree.in();
    cout << nl << nl;

    // Test preorder traversal
    cout << "Test 3: Preorder Traversal" << nl;
    cout << "Preorder: ";
    tree.pre();
    cout << nl << nl;

    // Test postorder traversal
    cout << "Test 4: Postorder Traversal" << nl;
    cout << "Postorder: ";
    tree.post();
    cout << nl << nl;

    // Test height
    cout << "Test 5: Calculate Height of Tree" << nl;
    cout << "Height: " << tree.calculateheight() << nl << nl;

    // Test search - found
    cout << "Test 6: Search for elements" << nl;
    int searchVal1 = 40;
    if (tree.search(searchVal1))
    {
        cout << "Element " << searchVal1 << " found in BST" << nl;
    }
    else
    {
        cout << "Element " << searchVal1 << " not found in BST" << nl;
    }

    // Test search - not found
    int searchVal2 = 100;
    if (tree.search(searchVal2))
    {
        cout << "Element " << searchVal2 << " found in BST" << nl;
    }
    else
    {
        cout << "Element " << searchVal2 << " not found in BST" << nl;
    }
    cout << nl;

    // Test duplicate insertion
    cout << "Test 7: Try to insert duplicate element" << nl;
    tree.insert(50);
    cout << nl;

    // Test deletion - leaf node
    cout << "Test 8: Delete leaf node (20)" << nl;
    tree.deleteNode(20);
    cout << "Inorder after deletion: ";
    tree.in();
    cout << nl << nl;

    // Test deletion - node with one child
    cout << "Test 9: Delete node with one child (30)" << nl;
    tree.deleteNode(30);
    cout << "Inorder after deletion: ";
    tree.in();
    cout << nl << nl;

    // Test deletion - node with two children
    cout << "Test 10: Delete node with two children (50)" << nl;
    tree.deleteNode(50);
    cout << "Inorder after deletion: ";
    tree.in();
    cout << nl << nl;

    // Test isEmpty on non-empty tree
    cout << "Test 11: Check if tree is empty" << nl;
    if (tree.isEmpty(nullptr))
    {
        cout << "Tree is empty" << nl;
    }
    else
    {
        cout << "Tree is not empty" << nl;
    }
    cout << nl;

    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}