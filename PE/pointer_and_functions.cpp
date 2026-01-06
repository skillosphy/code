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

struct Student
{
    int rollNo;
    string name;
    float gpa;
};

void swap(Student *a, Student *b)
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void inputStudents(Student *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].rollNo;
        cin >> arr[i].name;
        cin >> arr[i].gpa;
    }
}

void printStudents(Student *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i].rollNo << endl;
        cout << arr[i].name << endl;
        cout << arr[i].gpa << endl;
    }
}

Student *searchByRoll(Student *arr, int n, int roll)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i].rollNo == roll)
        {
            return &arr[i]; // found student
        }
    }
    return nullptr; // not found
}

void sortByGPA(Student *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((arr + j)->gpa < (arr + j + 1)->gpa)
            {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

clock_t s = clock();

void solve()
{

    // 721300550248
}

int main()
{
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student *list = new Student[n];

    cout << "\nEnter student details (rollNo name gpa):\n";
    inputStudents(list, n);

    cout << "\nInitial list:\n";
    printStudents(list, n);

    // Search test
    int rollToFind;
    cout << "\nEnter roll number to search: ";
    cin >> rollToFind;
    Student *found = searchByRoll(list, n, rollToFind);
    if (found != nullptr)
    {
        cout << "Found: " << found->rollNo << " "
             << found->name << " "
             << found->gpa << endl;
    }
    else
    {
        cout << "Student not found!\n";
    }

    // Sort test
    sortByGPA(list, n);
    cout << "\nAfter sorting by GPA:\n";
    printStudents(list, n);

    delete[] list; // free memory
    cout << "Execution Time: " << double(clock() - s) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}
