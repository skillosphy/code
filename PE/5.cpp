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
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    int sum = 1;
    for (int i = 0; i < sizeof(primes) / sizeof(primes[0]); i++)
    {
        int curr = primes[i];
        int max = curr;

        while (max * curr <= 20)
        {
            max *= curr;
        }
        sum *= max;
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
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}