#include "simple_data_structs.h"

using namespace pkr;
using namespace std;

Deck::Deck() {
    this->cards.reserve(52);
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            this->cards.push_back(Card((Rank)i, (Suit)j));
        }
    }
}

void Deck::shuffle() {
    std::srand(std::time(nullptr));
    random_shuffle(this->cards.begin(), this->cards.end());
}

Card Deck::popCard() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}

int Deck::size() {
    return cards.size();
}