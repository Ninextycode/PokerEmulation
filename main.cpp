#include "PokerSimuator.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    Action a = Action::ActionBuilder::build_ptr()->setPlayer("Dima")->setMoney(0)->setStreet(Street::preflop)->build();
    Action b = Action::ActionBuilder2().setPlayer("Vova").setMoney(10).setStreet(Street::flop).build();
    cout << a << endl;
    cout << b << endl;
    return 0;
}

