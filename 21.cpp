#include <iostream>
using namespace std;

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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *result = new ListNode;
        ListNode *runner = result;

        while (list1 != NULL && list2 != NULL)
        {
            if (list1->val <= list2->val)
            {
                ListNode *newNode = new ListNode(list1->val);

                if (result == NULL)
                {
                    result = newNode;
                    runner = newNode;
                }

                else
                {
                    runner->next = newNode;
                    runner = newNode;
                }
                list1 = list1->next;
            }

            else
            {
                ListNode *newNode = new ListNode(list2->val);

                if (result == NULL)
                {
                    result = newNode;
                    runner = newNode;
                }

                else
                {
                    runner->next = newNode;
                    runner = newNode;
                }
                list2 = list2->next;
            }
        }

        while (list1 != NULL)
        {
            runner->next = list1;
            runner = list1;
            list1 = list1->next;
        }

        while (list2 != NULL)
        {
            runner->next = list2;
            runner = list2;
            list2 = list2->next;
        }

        return result->next;
    }
};
