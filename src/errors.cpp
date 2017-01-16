#include "errors.h"

using namespace pkr;
using namespace std;

wrong_action::wrong_action(string s): runtime_error(s) {
    
}
