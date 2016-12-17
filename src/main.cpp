#include "data_structures.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    Action a = Action::ActionBuilder().setPlayer("Vova").setMoney(10).setStreet(Street::flop).build();
    cout << a << endl;
    return 0;
}

