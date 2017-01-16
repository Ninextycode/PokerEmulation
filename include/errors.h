#ifndef ERRORS_H
#define ERRORS_H
 
#include "headers.h"

namespace pkr {
    class wrong_action: public std::runtime_error {
    public:
        wrong_action(std::string s);
    };
}

#endif /* ERRORS_H */

