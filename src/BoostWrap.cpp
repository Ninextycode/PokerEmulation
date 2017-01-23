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
    
    class_<Deck>("Deck")
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
}
