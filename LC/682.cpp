#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{

    stack<int> ops;

public:
    int calPoints(vector<string> &operations)
    {

        for (string &op : operations)
        {
            if (op == "C")
            {
                ops.pop();
            }
            else if (op == "D")
            {
                ops.push(2 * ops.top());
            }
            else if (op == "+")
            {
                int x = ops.top();
                ops.pop();
                int y = ops.top();
                ops.push(x);
                ops.push(x + y);
            }
            else
            {
                ops.push(stoi(op));
            }
        }

        int sum = 0;
        while (!ops.empty())
        {
            sum += ops.top();
            ops.pop();
        }
    }
};
