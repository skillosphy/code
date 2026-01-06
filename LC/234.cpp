#include <iostream>
#include <stack>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {

        stack<int> Pal;

        ListNode *temp = head;
        while (temp != NULL)
        {
            Pal.push(temp->val);
            temp = temp->next;
        }

        ListNode *run = head;
        while (run != NULL)
        {
            if (run->val == Pal.top())
            {
                Pal.pop();
                run = run->next;
            }

            else
            {
                return false;
            }
        }
        return true;
    }
};