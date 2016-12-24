#include "evaluator.h"

using namespace pkr;
using namespace std;

int Evaluator::evaluate(Card a, Card b, Card c, Card d, Card e, Card f, Card g) {
    vector<int> data  = {a.toInt(), b.toInt(), c.toInt(),  d.toInt(), e.toInt(), f.toInt(), g.toInt()};
    sort(data.begin(), data.end());
    return 0;
}