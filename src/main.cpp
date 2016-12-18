#include "data_structs.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    Deck d;
    d.shuffle();
    Hand h(d.popCard(), d.popCard());
    cout << h << endl;
   
    return 0;
}

