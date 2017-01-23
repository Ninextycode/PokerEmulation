import pokerlib

deck = pokerlib.Deck()


deck.shuffle()
print(deck.size())
c = deck.pop_card()
print(c)
print(deck.size())


deck1 = pokerlib.CycleDeck([[pokerlib.Card("Ac")]])

deck.shuffle()
print(deck.size())
c = deck.pop_card()
print(c)
print(deck.size())