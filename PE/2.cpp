#include <bits/stdc++.h>
#define fli(fc, n, i) for (int i = fc; i < n; i++)
#define rli(i, n, rc) for (int i = n; i > rc; i--)
#define sz(a) a.size()
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define nl "\n"
using namespace std;
#define M2 998244353
#define M 1e9 + 7
#define ff first
#define ss second
#define N 100005

clock_t s = clock();

void solve()
{
    int a = 1;
    int b = 2;
    int c = 0;
    int sum = 2;
    for (; b < 4000000;)
    {
        c = a + b;
        a = b;
        b = c;
        if (c % 2 == 0)
        {
            sum += c;
        }
    }

    cout << sum;
}

int main()
{

    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    cout << fixed << setprecision(60);
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}