#include "deck.h"

using namespace pkr;
using namespace std;

Deck::Deck() {
    refill();
}

void Deck::refill() {
    this->cards.resize(52);
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            this->cards[i*4+j] = Card((Rank)i, (Suit)j);
        }
    }
}

void Deck::shuffle() {
    refill();
    std::srand(std::time(nullptr));
    // random_shuffle(this->cards.begin(), this->cards.end());
}

Card Deck::popCard() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}

int Deck::size() {
    return cards.size();
}

void ConstantDeck::shuffle() {
    refill();
}

CycleDeck::CycleDeck(const vector<vector<Card> >& states) {
    for(auto state: states) {
        this->states.push_back(state);
    }
    this->cards = states[state];
}

void CycleDeck::shuffle() {
    this->cards = states[(++state) % states.size()];
}