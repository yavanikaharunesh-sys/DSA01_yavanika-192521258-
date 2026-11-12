#include <iostream>
#include <chrono>
using namespace std;

const int K = 1000;                 // how many transactions to remember

// ORIGINAL (Q4 idea): when full, shift everything left -> O(K) per transaction
class ShiftLog {
    double t[K];
    int count = 0;
public:
    void add(double x)
    {
        if (count == K) {
            for (int i = 1; i < K; i++) t[i - 1] = t[i];   // slow: moves K items
            count--;
        }
        t[count++] = x;
    }
    double get(int i) { return t[i]; }                      // 0 = oldest
};

// REDESIGN: circular buffer -> just overwrite the oldest, O(1) per transaction
class CircularLog {
    double t[K];
    int start = 0, count = 0;
public:
    void add(double x)
    {
        if (count < K) t[(start + count++) % K] = x;
        else { t[start] = x; start = (start + 1) % K; }     // fast: no shifting
    }
    double get(int i) { return t[(start + i) % K]; }
};

int main()
{
    ShiftLog a;
    CircularLog b;

    // 1) Correctness: both must hold the same last K transactions
    for (int i = 1; i <= 2500; i++) { a.add(i); b.add(i); }
    bool same = true;
    for (int i = 0; i < K; i++) if (a.get(i) != b.get(i)) same = false;
    cout << "Both give same last " << K << " transactions: " << (same ? "YES" : "NO") << endl;

    // 2) Speed: add 500,000 transactions to each
    const int N = 500000;
    ShiftLog x;
    CircularLog y;

    auto s1 = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) x.add(i);
    auto s2 = chrono::steady_clock::now();
    for (int i = 0; i < N; i++) y.add(i);
    auto s3 = chrono::steady_clock::now();

    cout << "Original (shift)    : " << chrono::duration_cast<chrono::milliseconds>(s2 - s1).count() << " ms" << endl;
    cout << "Redesign (circular) : " << chrono::duration_cast<chrono::milliseconds>(s3 - s2).count() << " ms" << endl;
    cout << "(check: " << x.get(K - 1) + y.get(K - 1) << ")" << endl;
    return 0;
}
