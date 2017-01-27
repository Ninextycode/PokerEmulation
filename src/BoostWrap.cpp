#include "game.h"
#include "deck.h"
#include <boost/python.hpp>

using namespace std;
using namespace boost::python;
using namespace pkr;

template<class containedType>
struct vector_from_seq_of {
    vector_from_seq_of() { 
        converter::registry::push_back(&convertible, &construct, type_id<vector<containedType>>());
    }
    static void* convertible(PyObject* obj_ptr) {
        if (!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr, "__len__")) return 0;
        return obj_ptr;
    }
    static void construct(PyObject* obj_ptr, converter::rvalue_from_python_stage1_data* data) {
        void* storage = ((converter::rvalue_from_python_storage<vector<containedType> >*)(data))->storage.bytes;
        new (storage) vector<containedType>();
        vector<containedType>* v = (vector<containedType>*)(storage);
        int l = PySequence_Size(obj_ptr); 
        if (l<0) 
            abort();
        v->reserve(l);
        for (int i = 0; i<l; i++) {
            v->push_back(extract<containedType>(PySequence_GetItem(obj_ptr, i))); 
        }
        data->convertible = storage;
    }
};

BOOST_PYTHON_MODULE(pokerlib) {
    vector_from_seq_of<string>();
    vector_from_seq_of<shared_ptr<Player>>();
    vector_from_seq_of<shared_ptr<Deck>>();   
    
    enum_<Street>("Street")
        .value("preflop", Street::preflop)
        .value("flop",  Street::flop)
        .value("turn",  Street::turn)
        .value("river", Street::river);

    enum_<Rank>("Rank")
        .value("A", A)
        .value("K", K)
        .value("Q", Q)
        .value("J", J)
        .value("T", T)
        .value("9", Rank::_9)
        .value("8", Rank::_8)
        .value("7", Rank::_7)
        .value("6", Rank::_6)
        .value("5", Rank::_5)
        .value("4", Rank::_4)
        .value("3", Rank::_3)
        .value("2", Rank::_2);
    
    enum_<Suit>("Suit")
        .value("s", s)
        .value("h", h)
        .value("d", d)
        .value("c", c);
    
    class_<Deck, shared_ptr<Deck>>("Deck")
        .def("shuffle", &Deck::shuffle)
        .def("pop_card", &Deck::popCard)
        .def("size", &Deck::size)
        .def("__len__", &Deck::size);
        
    class_<Card>("Card")
        .def(init<const char*>())
        .def(init<Rank, Suit>())
    	.def_readwrite("rank", &Card::rank)
        .def_readwrite("suit", &Card::suit)
        .def(self_ns::str(self));
    
    class_<CycleDeck,  bases<Deck>>("CycleDeck", no_init)
        .def(init<vector<string>>());
    
    class_<ConstantDeck,  bases<Deck>>("ConstantDeck");   
    
    
    struct GameWrap: Game, wrapper<Game>{
        using Game::Game;
        void playGame() override {
            this->get_override("play_game")();
            return; 
        }
        void onStartRound() const override {
            this->get_override("on_start_round")();
            return; 
        }
        void onCardsDealt(std::shared_ptr<Player> const player, Hand hand) const override {
            this->get_override("on_cards_dealt")(player, hand);
            return; 
        }
        void onFlopDealt(vector<Card> flop) const override {
            this->get_override("on_flop_dealt")(flop);
            return; 
        }
        void onTurnDealt(Card turn) const override {
            this->get_override("on_turn_dealt")(turn);
            return; 
        }
        void onRiverDealt(Card river) const override {
            this->get_override("on_river_dealt")(river);
            return; 
        }
        void onFinalCombinations(std::vector<Hand> hands, const std::vector<Card>& sharedCards) const override {
            this->get_override("on_final_combinations")(hands, sharedCards);
            return; 
        }
        void onGameEnd() const override {
            this->get_override("on_game_end")();
            return; 
        }
        void onNewAction(Action action) const override {
            this->get_override("on_new_action")(action);
            return; 
        }    
        int getInitialStack() const override {            
            return this->get_override("get_initial_stack")();
        }  
    };
    
    class_<GameWrap, boost::noncopyable>("Game")
        .def(init<shared_ptr<Deck>>())
        .def("get_players_data", &Game::getPlayersData, return_value_policy<copy_const_reference>())
        .def("get_street", &Game::getStreet)
        .def("set_players", &Game::setPlayers)
        .def("is_action_valid", &Game::isActionValid)
        .def("play_game", pure_virtual(&Game::playGame))
        
        .def("on_cards_dealt", pure_virtual(&GameWrap::onCardsDealt))
        .def("on_flop_dealt", pure_virtual(&GameWrap::onFlopDealt))
        .def("on_turn_dealt", pure_virtual(&GameWrap::onTurnDealt))
        .def("on_river_dealt", pure_virtual(&GameWrap::onRiverDealt))
        .def("on_final_combinations", pure_virtual(&GameWrap::onFinalCombinations))
        .def("on_game_end", pure_virtual(&GameWrap::onGameEnd))
        .def("on_new_action", pure_virtual(&GameWrap::onNewAction))
        .def("get_initial_stack", pure_virtual(&GameWrap::getInitialStack));
    
    struct PlayerWrap : Player, wrapper<Player> {
        void markAsWinner() override {
            this->get_override("mark_as_winner")();
            return;
        }
        Action preformAction(const Game& currentGame, Hand hand) override {
            return this->get_override("preform_action")(currentGame, hand);
        }
        std::string getName() const override {
            return this->get_override("get_name")();
        }
    };
    
    class_<PlayerWrap, boost::noncopyable>("Player") 
        .def("mark_as_winner", pure_virtual(&Player::markAsWinner))
        .def("preform_action", pure_virtual(&Player::preformAction))
        .def("get_name", pure_virtual(&Player::getName));
    
}
