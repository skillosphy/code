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

clock_t s = clock();

// 2024302
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
    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}