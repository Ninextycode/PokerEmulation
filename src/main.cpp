#include "headers.h"
#include "game.h"
#include "deck.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    cout << 123 << endl;
    shared_ptr<Deck> deck(make_shared<ConstantDeck>());
    OneTwoGame game(deck);
    shared_ptr<Player> p1(make_shared<AllInPlayer>("Nick"));
    shared_ptr<Player> p2(make_shared<AllInPlayer>("Max"));
    game.setPlayers({p1, p2});

    game.playGame();

    return 0;
}

