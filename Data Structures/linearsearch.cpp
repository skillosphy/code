#include <iostream>
using namespace std;

int main()
{
    int arr[7] = {3, 1, 4, 2, 5, 6, 7};
    int temp;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int k = 0; k < 7; k++)
    {
        cout << arr[k] << " ";
    }
}