#include <iostream>
#include <string>
using namespace std;

class BusTicket {
    static int issued;                 // shared by ALL tickets (exists only once)
    static const int CAPACITY = 3;     // seats in the bus
    int seat;
    string name;
public:
    BusTicket(const string& n)
    {
        seat = 0;                      // 0 means waiting list
        name = n;
        if (issued < CAPACITY) {       // TODO 1: give next seat if available
            issued++;
            seat = issued;
        }
    }
    static int count() { return issued; }   // TODO 2: seats issued so far

    void print() const
    {
        if (seat) cout << name << ": Seat " << seat << endl;
        else      cout << name << ": Waiting" << endl;
    }
};

int BusTicket::issued = 0;             // static member is defined outside the class

void bookInFunction(const string& n)   // tickets created inside a function
{
    BusTicket t(n);
    t.print();
}                                      // t is destroyed here, count is NOT reduced

int main()
{
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
                         BusTicket("Chitra"), BusTicket("Dev")};
    for (int i = 0; i < 4; i++) trip[i].print();
    cout << "Issued: " << BusTicket::count() << endl;

    bookInFunction("Esha");            // function called twice
    bookInFunction("Farid");
    cout << "Issued after function calls: " << BusTicket::count() << endl;
    return 0;
}
