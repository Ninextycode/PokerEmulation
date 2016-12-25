#include "evaluator.h"
#include "evaluator/SevenEval.h"

using namespace pkr;
using namespace std;

int Evaluator::evaluate(Card a, Card b, Card c, Card d, Card e, Card f, Card g) {
    return SevenEval::GetRank(a.toInt(), b.toInt(), c.toInt(),  d.toInt(), e.toInt(), f.toInt(), g.toInt());
}