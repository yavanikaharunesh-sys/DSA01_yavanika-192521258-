#include <iostream>
using namespace std;

// 1) call by value: gets a COPY of the fee
void byValue(long long fee, int percent)
{
    fee = fee - fee * percent / 100;
}

// 2) call by reference: works on the caller's own fee
void byReference(long long& fee, int percent)
{
    fee = fee - fee * percent / 100;
}

// 3) call by pointer: works on the caller's fee through its address
void byPointer(long long* fee, int percent)
{
    *fee = *fee - *fee * percent / 100;
}

int main()
{
    long long f1 = 45000, f2 = 45000, f3 = 45000;

    byValue(f1, 10);
    byReference(f2, 10);
    byPointer(&f3, 10);

    cout << "Original fee      : 45000" << endl;
    cout << "After by value    : " << f1 << endl;
    cout << "After by reference: " << f2 << endl;
    cout << "After by pointer  : " << f3 << endl;
    return 0;
}
