#include <iostream>
using namespace std;
#include <vector>
class Solution // bubble sort
{
public:
    void sortColors(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < nums.size() - i - 1; j++)
            {
                int temp;
                if (nums[j] > nums[j + 1])
                {
                    temp = nums[j + 1];
                    nums[j + 1] = nums[j];
                    nums[j] = temp;
                }
            }
        }
    }
};

class Solution2 // insertion sort
{
public:
    void sortColors(vector<int> &nums)
    {
        for (int i = 1; i < nums.size(); i++)
        {
            int key = nums[i];
            int j = i - 1;

            while (j >= 0 && key < nums[j])
            {
                nums[j + 1] = nums[j];
                --j;
            }
            nums[j + 1] = key;
        }
    }
};

class Solution3 // selection sort
{
public:
    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void sortColors(vector<int> &nums)
    {
        for (int i = 0; i < nums.size() - 1; i++)
        {
            int min = i;
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[j] < nums[min])
                {
                    min = j;
                }
            }

            swap(&nums[min], &nums[i]);
        }
    }
};

class Solution4 // merge sort
{
public:
    void merge(int A[], int low, int high, int mid)
    {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        // Temporary arrays
        int left[n1];
        int right[n2];

        // Copy data
        for (int i = 0; i < n1; i++)
            left[i] = A[low + i];
        for (int j = 0; j < n2; j++)
            right[j] = A[mid + 1 + j];

        int i = 0, j = 0, k = low;

        // Merge the two halves
        while (i < n1 && j < n2)
        {
            if (left[i] <= right[j])
                A[k++] = left[i++];
            else
                A[k++] = right[j++];
        }

        // Copy remaining elements
        while (i < n1)
            A[k++] = left[i++];
        while (j < n2)
            A[k++] = right[j++];
    }
    void mergeSort(int A[], int low, int high)
    {
        if (low < high)
        {
            int mid;
            mid = (low + high) / 2;

            mergeSort(A, low, mid);
            mergeSort(A, mid + 1, high);

            merge(A, low, high, mid);
        }
    }
    void sortColors(vector<int> &nums)
    {
        int n = nums.size();
        int *arr = new int[n];

        for (int i = 0; i < n; i++)
            arr[i] = nums[i];

        mergeSort(arr, 0, n - 1);

        for (int i = 0; i < n; i++)
            nums[i] = arr[i];

        delete[] arr;
    }
};

class Solution5 // Quick sort
{

    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    int partition(int A[], int low, int high)
    {
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

    void quickSort(int A[], int low, int high)
    {
        if (low < high)
        {
            int partindex = partition(A, low, high);

            quickSort(A, low, partindex - 1);
            quickSort(A, partindex + 1, high);
        }
    }
};
