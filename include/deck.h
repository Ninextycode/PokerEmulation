#ifndef CUSTOM_DECK_H
#define CUSTOM_DECK_H

#include "simple_data_structs.h"

namespace pkr {
    class Deck {
    public:
        Deck();
        virtual void shuffle();
        Card popCard();
        int size();
    protected:
        virtual void refill();
        std::vector<Card> cards;
    };
    
    class ConstantDeck: public Deck {
        void shuffle() override;
    };
    
    class CycleDeck: public Deck {
        std::vector<std::vector<Card>> states;
        int state = 0;
    public: 
        CycleDeck(const std::vector<std::vector<Card>>& states);
        void shuffle() override;
    };
}
#endif /* CUSTOM_DECK_H */

