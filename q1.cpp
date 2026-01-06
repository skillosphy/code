// Mohammad Hassaan // 2024302 // CS // Assignment #2
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class q1_Solution
{
public:
    void insertion_sort(int A[], int low, int high)
    {
        for (int i = low + 1; i <= high; i++)
        {
            int key = A[i];
            int j = i - 1;
            while (j >= low && A[j] > key)
            {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = key;
        }
    }

    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    // Helper to find the index of the Median of Three (First, Middle, Last)
    int getMedianIndex(int A[], int low, int high)
    {
        int mid = low + (high - low) / 2;

        // Sort low, mid, high to find the median
        if (A[low] > A[mid])
            swap(&A[low], &A[mid]);
        if (A[low] > A[high])
            swap(&A[low], &A[high]);
        if (A[mid] > A[high])
            swap(&A[mid], &A[high]);

        // The median is now at the mid index
        return mid;
    }

    // Updated partition to accept the 'type' argument
    int partition(int A[], int low, int high, char type)
    {
        int pivotIndex = high; // Default to 'high' (standard)

        // Select pivot index based on the type passed
        if (type == 'M')
        {
            // Middle Element
            pivotIndex = low + (high - low) / 2;
        }
        else if (type == '3')
        {
            // Median of Three
            pivotIndex = getMedianIndex(A, low, high);
        }

        // Swap the chosen pivot to the end (high) so standard partition logic applies
        if (pivotIndex != high)
        {
            swap(&A[pivotIndex], &A[high]);
        }

        // --- Standard Partition Logic (same as before) ---
        int pivot = A[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++)
        {
            if (A[j] <= pivot)
            {
                i++;
                swap(&A[i], &A[j]);
            }
        }

        swap(&A[i + 1], &A[high]);
        return i + 1;
    }

    void quickSortA(int A[], int low, int high)
    {
        if (low < high)
        {
            int partindex = partition(A, low, high, 'M');
            quickSortA(A, low, partindex - 1);
            quickSortA(A, partindex + 1, high);
        }
    }

    // PART B: Pivot = Median of First, Last, Middle
    void quickSortB(int A[], int low, int high)
    {
        if (low < high)
        {
            int partindex = partition(A, low, high, '3');
            quickSortB(A, low, partindex - 1);
            quickSortB(A, partindex + 1, high);
        }
    }

    // PART C: Pivot = Middle + Insertion Sort if Size < 20
    void quickSortC(int A[], int low, int high)
    {
        if (low < high)
        {
            if (high - low + 1 < 20)
            {
                insertion_sort(A, low, high);
            }
            else
            {
                int partindex = partition(A, low, high, 'M');
                quickSortC(A, low, partindex - 1);
                quickSortC(A, partindex + 1, high);
            }
        }
    }

    // PART D: Pivot = Median + Insertion Sort if Size < 20
    void quickSortD(int A[], int low, int high)
    {
        if (low < high)
        {
            if (high - low + 1 < 20)
            {
                insertion_sort(A, low, high);
            }
            else
            {
                int partindex = partition(A, low, high, '3');
                quickSortD(A, low, partindex - 1);
                quickSortD(A, partindex + 1, high);
            }
        }
    }

    void print(int A[])
    {
        for (int i = 0; i < 10; i++) // printing only first 10 elements
            cout << A[i] << " ";
        cout << "..." << endl;
    }
};

int main()
{
    q1_Solution solution;
    srand(time(0));

    int N = 10000;

    int *arrA = new int[N];
    int *arrB = new int[N];
    int *arrC = new int[N];
    int *arrD = new int[N];

    // Generate random data
    for (int i = 0; i < N; i++)
    {
        int val = rand() % 100000; // Random number between 0 and 99999
        arrA[i] = val;
        arrB[i] = val;
        arrC[i] = val;
        arrD[i] = val;
    }

    // --- PART A ---
    cout << "a)\n";
    solution.quickSortA(arrA, 0, N - 1);
    solution.print(arrA);

    // --- PART B ---
    cout << "b)\n";
    solution.quickSortB(arrB, 0, N - 1);
    solution.print(arrB);

    // --- PART C ---
    cout << "c)\n";
    solution.quickSortC(arrC, 0, N - 1);
    solution.print(arrC);

    // --- PART D ---
    cout << "d)\n";
    solution.quickSortD(arrD, 0, N - 1);
    solution.print(arrD);

    delete[] arrA;
    delete[] arrB;
    delete[] arrC;
    delete[] arrD;

    // part e)
    /*
       For the 10,000 item array, the hybrid versions (Parts C and D) generally run faster.
       This is because switching to Insertion Sort for small lists (under 20 items) saves a lot of time
       by skipping unnecessary recursive calls at the bottom of the tree.

       Also, using the "Median of Three" pivot is safer than just picking the middle element.
       It keeps the partitions balanced and stops the sort from getting slow (O(n^2)) if the data
       happens to be nearly sorted already.
    */

    return 0;
}