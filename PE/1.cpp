// 2024302
#include <bits/stdc++.h>
using namespace std;
int main()
{
    // code
    int sum3 = 0, sum5 = 0, sum15 = 0, total = 0;
    for (int i = 3; i < 1000; i += 3)
    {
        sum3 += i;
    }
    for (int i = 5; i < 1000; i += 5)
    {
        sum5 += i;
    }
    for (int i = 15; i < 1000; i += 15)
    {
        sum15 += i;
    }

    total = (sum3 + sum5) - sum15;
    cout << total;
}
