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

class MergeS
{
public:
    void merge(int A[], int low, int high, int mid)
    {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        // temp arrays
        int left[n1];
        int right[n2];

        // copy data
        for (int i = 0; i < n1; i++)
        {
            left[i] = A[low + i];
        }

        for (int j = 0; j < n2; j++)
        {
            right[j] = A[mid + 1 + j];
        }
        int i = 0;
        int j = 0;
        int k = low;
        // merge
        while (i < n1 && j < n2)
        {
            if (left[i] <= right[j])
            {
                A[k++] = left[i++];
            }

            else
            {
                A[k++] = right[j++];
            }
        }

        // copy remaining data

        while (i < n1)
        {
            A[k++] = left[i++];
        }

        while (j < n2)
        {
            A[k++] = right[j++];
        }
    }

    void sort(int A[], int low, int high)
    {
        if (low < high)
        {
            int mid;
            mid = (low + high) / 2;

            sort(A, low, mid);
            sort(A, mid + 1, high);

            merge(A, low, high, mid);
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
    solve();

    // Driver code for MergeSort
    cout << "=== Merge Sort Driver Code ===" << nl << nl;

    // Test case 1: Basic unsorted array
    cout << "Test 1: Basic unsorted array" << nl;
    int arr1[] = {64, 25, 34, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Original array: ";
    printArray(arr1, n1);

    MergeS sorter1;
    sorter1.sort(arr1, 0, n1 - 1);
    cout << "Sorted array: ";
    printArray(arr1, n1);
    cout << nl;

    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}