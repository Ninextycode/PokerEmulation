#include "data_structures.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    Deck d;
    d.shuffle();
    while(d.size() > 0) {
         cout << d.popCard() << endl;
    }
   
    return 0;
}

