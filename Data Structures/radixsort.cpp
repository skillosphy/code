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
    RadixSort rs;
    vector<int> arr = {329, 457, 657, 839, 436, 720, 355};
    int n = arr.size();
    int digits = 3; // Maximum 3 digits

    cout << "Original Array: ";
    rs.printArray(arr, n);

    rs.radixSort(arr, n, digits);

    cout << "Sorted Array: ";
    rs.printArray(arr, n);
}

class RadixSort
{
public:
    static const int d = 10;

    void radixSort(vector<int> &A, int N, int d)
    {
        // Initialize 10 queues for digits 0-9
        queue<int> Q[d];

        int D = 1;

        // Process each digit position
        for (int k = 1; k <= d; k++)
        {
            D = D * 10;

            // Distribute numbers into queues based on current digit
            for (int i = 0; i < N; i++)
            {
                int digit = (A[i] % D) / (D / 10);
                Q[digit].push(A[i]);
            }

            // Collect numbers back from queues in order
            int j = 0;
            for (int p = 0; p < 10; p++)
            {
                while (!Q[p].empty())
                {
                    A[j] = Q[p].front();
                    Q[p].pop();
                    j++;
                }
            }
        }
    }

    void printArray(vector<int> &A, int N)
    {
        for (int i = 0; i < N; i++)
        {
            cout << A[i] << " ";
        }
        cout << nl;
    }
};

int main()
{
    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}