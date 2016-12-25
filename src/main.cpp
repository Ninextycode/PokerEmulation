#include "headers.h"
#include "game.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    OneTwoGame game;
    shared_ptr<Player> p1 = static_pointer_cast<Player>(make_shared<AllInPlayer>("Nick"));
    shared_ptr<Player> p2 = static_pointer_cast<Player>(make_shared<AllInPlayer>("Max"));
    game.setPlayers({p1, p2});
    game.playGame();
    
    
    return 0;
}

