#include <iostream>
using namespace std;

struct Parcel { double kg; bool express; bool insured; };

// Original problem: charge(double), charge(double,bool) and
// charge(double,bool=false,bool=false) together make charge(2.5) and
// charge(2.5,true) AMBIGUOUS. Fix: keep ONE function with defaults and
// let overloading separate the DIFFERENT kinds of input.

// 1) weight in grams (int)
double charge(int grams)
{
    cout << "[int grams] ";
    return grams / 1000.0 * 40;
}

// 2) weight in kg (double), optional extras (defaults given from the right)
double charge(double kg, bool express = false, bool insured = false)
{
    cout << "[double kg] ";
    double c = kg * 40;
    if (express) c += 50;
    if (insured) c += 20;
    return c;
}

// 3) a Parcel object
double charge(const Parcel& p)
{
    cout << "[Parcel]    ";
    double c = p.kg * 40;
    if (p.express) c += 50;
    if (p.insured) c += 20;
    return c;
}

int main()
{
    Parcel p = {3.0, true, false};

    cout << "charge(500)            -> " << charge(500) << endl;               // int exact match
    cout << "charge(2.5)            -> " << charge(2.5) << endl;               // double exact match
    cout << "charge(2.5, true, true)-> " << charge(2.5, true, true) << endl;   // defaults not needed
    cout << "charge(2)              -> " << charge(2) << endl;                 // int exact match
    cout << "charge(2.0f)           -> " << charge(2.0f) << endl;              // float promoted to double
    cout << "charge(p)              -> " << charge(p) << endl;                 // Parcel
    return 0;
}
