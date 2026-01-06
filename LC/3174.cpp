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

// 2024302

class Solution
{
public:
    string clearDigits(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s.push_back(s[i]);
            if (s[i + 1] >= 0 && s[i + 1] <= 9)
            {
                s.pop_back();
                s.pop_back();
            }
        }
        return s;
    }
};
