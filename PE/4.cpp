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

void solve()
{
    int num, n, digit, pal;
    rli(i, 999, 99)
    {
        rli(j, 999, 99)
        {

                        n = i * j;
            num = n;
            int pal = 0;
            do
            {
                digit = num % 10;
                pal = (pal * 10) + digit;
                num = num / 10;

            } while (num != 0);

            if (n == pal)
            {
                cout << n << " is pal";
            }
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