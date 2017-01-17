#include "headers.h"
#include "game.h"
#include "deck.h"
#include <iostream>

using namespace std;
using namespace pkr;

int main(int argc, char** argv) {
    vector<vector<Card>> cards {
        {
             (Card)"Kc", (Card)"Jd", (Card)"9h", (Card)"3s", (Card)"5s",
             (Card)"As", (Card)"Ac",
             (Card)"Ah", (Card)"Ad",
             (Card)"7c", (Card)"2c"            
        } 
    };
    shared_ptr<Deck> deck(make_shared<CycleDeck>(cards));
    OneTwoGame game(deck);
    shared_ptr<Player> p1(make_shared<AllInPlayer>("Nick"));
    shared_ptr<Player> p2(make_shared<AllInPlayer>("Max"));
    shared_ptr<Player> p3(make_shared<AllInPlayer>("Don"));
    game.setPlayers({p1, p2, p3});

    game.playGame();

    return 0;
}

