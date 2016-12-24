#ifndef SIMPLE_DATA_STRUCTS_H
#define SIMPLE_DATA_STRUCTS_H

#include "headers.h"

namespace pkr {
    enum Suit {
        s, p, d, f
    };
    std::ostream& operator<<(std::ostream& out, const Suit& suit);
    
    enum Rank{
        A, K, Q, J,  T, _9, _8, _7, _6, _5, _4, _3, _2
    };
    std::ostream& operator<<(std::ostream& out, const Rank& rank);
    
    struct Card {
    public:
        Rank rank;
        Suit suit;
        Card(Rank rank, Suit suit);
        Card();
        int toInt();
    friend std::ostream& operator<<(std::ostream& out, const Card& card);
    };
    
    struct Hand {
    public:
        Card c1;
        Card c2;
        Hand(Card c1, Card c2s);
        Hand();
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
    };
    
    class Deck {
    public:
        Deck();
        void shuffle();
        Card popCard();
        int size();
    private:
        std::vector<Card> cards;
    };
    
    enum class Street {
        preflop, flop, turn, river
    };
    std::ostream& operator<<(std::ostream& out, const Street& street);
}


#endif /* SIMPLE_DATA_STRUCTS_H */

