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
}

class QuickSort
{
    public:
    int partition(int A[], int low, int high)
    {
        int pivot = A[high];

        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (A[j] <= pivot)
            {
                i++;
                swap(A[i], A[j]);
            }
        }

        swap(A[i + 1], A[high]);
        return i + 1;
    }

    void sort(int A[], int low, int high)
    {
        if (low < high)
        {
            int partidx = partition(A, low, high);
            sort(A, low, partidx - 1);
            sort(A, partidx + 1, high);
        }
    }
};

void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << A[i] << " ";
    }
    cout << nl;
}

int main()
{

       int arr1[] = {64, 25, 34, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Original array: ";
    printArray(arr1, n1);

    QuickSort sorter1;
    sorter1.sort(arr1, 0, n1 - 1);
    cout << "Sorted array: ";
    printArray(arr1, n1);
    cout << nl;


    solve();
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
}
