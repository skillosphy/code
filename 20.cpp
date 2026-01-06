#include <iostream>
#include <stack>
using namespace std;

class Solution
{
    stack<char> Par;

public:
    bool isValid(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            char x = s[i];
            if (x == '(' || x == '{' || x == '[')
            {
                Par.push(s[i]);
            }

            else
            {
                if (Par.empty())
                {
                    return false;
                }

                char top = Par.top();
                Par.pop();

                if ((x == ')' && top != '(') ||
                    (x == '}' && top != '{') ||
                    (x == ']' && top != '['))
                {
                    return false;
                }
            }
        }
        return Par.empty();
    }
};