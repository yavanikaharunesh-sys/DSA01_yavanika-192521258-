#include <iostream>
#include <chrono>
using namespace std;

class Time {
    int h, m;                                  // private data
public:
    Time(int hh, int mm) { h = hh; m = mm; }

    // friend functions: not members, but allowed to read private h and m
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
    friend int normalBetween(const Time& a, const Time& b);
};

// TODO 1: absolute difference in minutes (inline = compiler may paste the code)
inline int minutesBetween(const Time& a, const Time& b)
{
    int x = a.h * 60 + a.m;
    int y = b.h * 60 + b.m;
    return x > y ? x - y : y - x;
}

// TODO 2: is a earlier than b?
inline bool earlier(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

// Same work, but a normal (non-inline) function, for the timing comparison
int normalBetween(const Time& a, const Time& b)
{
    int x = a.h * 60 + a.m;
    int y = b.h * 60 + b.m;
    return x > y ? x - y : y - x;
}

int main()
{
    Time t1(9, 45), t2(13, 10);
    cout << minutesBetween(t1, t2) << " " << boolalpha << earlier(t2, t1) << endl;  // 205 false

    // Time 10,000,000 calls of each version
    const int N = 10000000;
    long long sum = 0;

    auto s1 = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) sum += minutesBetween(Time(i % 24, i % 60), t2);
    auto s2 = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) sum += normalBetween(Time(i % 24, i % 60), t2);
    auto s3 = chrono::steady_clock::now();

    cout << "inline     : " << chrono::duration_cast<chrono::milliseconds>(s2 - s1).count() << " ms" << endl;
    cout << "not inline : " << chrono::duration_cast<chrono::milliseconds>(s3 - s2).count() << " ms" << endl;
    cout << "(sum = " << sum << ", printed so the loops are not removed)" << endl;
    return 0;
}
