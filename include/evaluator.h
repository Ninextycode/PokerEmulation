/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   evaluator.h
 * Author: maxim
 *
 * Created on 24 December 2016, 18:52
 */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "headers.h"
#include "simple_data_structs.h"
namespace pkr {
    class Evaluator {
    public:
        static int evaluate(Card a, Card b, Card c, Card d, Card e, Card f, Card g);
    };
}

#endif /* EVALUATOR_H */

