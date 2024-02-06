#include <iostream>
#include "BigNumber.h"

using namespace std;

int main() {
    BigNumber t,d;
    t.setFromString("265625646252562562446432");
    d.setFromString("65262346265262245626622");
    cout << (t-d).toString() << endl;
    cout << (t+d).toString() << endl;
    cout << (t*d).toString() << endl;
}