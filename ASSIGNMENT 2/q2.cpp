#include <iostream>
#include <vector>
using namespace std;

// Returns a REFERENCE to the highest mark, so the caller can change it
int& highest(int marks[], int n)
{
    int best = 0;
    for (int i = 1; i < n; i++)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}

// DANGER: returns a reference to a local variable (compiler warns).
// It dies when the function ends, so using it is undefined behaviour.
int& badMax(int a, int b)
{
    int result = a > b ? a : b;
    return result;
}

int main()
{
    int marks[5] = {70, 85, 62, 91, 78};

    highest(marks, 5) += 2;                 // moderation +2 on the highest mark
    cout << "Highest after +2 moderation : " << marks[3] << endl;

    highest(marks, 5) = 90;                 // function call on the LEFT of =
    cout << "Highest after assignment    : " << marks[3] << endl;

    int copy = highest(marks, 5);           // return by copy
    copy += 50;
    cout << "Copy changed to " << copy << ", array still " << marks[3] << endl;

    const int& r = highest(marks, 5);       // const reference: read only
    cout << "Const reference reads       : " << r << endl;

    // Changed condition: a vector that grows
    vector<int> v = {70, 85, 91};
    int* before = &v[2];
    for (int i = 0; i < 100; i++) v.push_back(i);   // vector grows and moves
    int* after = &v[2];
    if (before != after)
        cout << "Vector grew: old reference is now dangling" << endl;

    cout << "badMax() is never called (undefined behaviour)" << endl;
    return 0;
}
