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
#define M2 998244353
#define M 1e9 + 7
#define ff first
#define ss second
#define N 100005

clock_t s = clock();
vector<int> factors(ll n)
{
    vector<int> f;
    for (int x = 2; x * x <= n; x++)
    {
        if (n % x == 0)
        {
            f.push_back(x);
            while (n % x == 0)
                n /= x;
        }
    }
    if (n > 1)
        f.push_back(n);
    return f;
}

void solve()
{
    auto p = factors(600851475143 * 71);
    for (auto x : p)
        cout << x << " ";
    cout << endl;

    for (int x = 2; x <= n; x++)
    {
        if (sieve[x])
            continue;
        for (int u = 2 * x; u <= n; u += x)
        {
            sieve[u] = x;
        }
    }
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
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}