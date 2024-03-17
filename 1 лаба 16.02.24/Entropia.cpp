#include "Entropia.h"

/*

    ‘”Õ ÷»ﬂ ›Õ“–Œœ»»
       
    H(x) = -≈(p(x) * log2(p(x)))

*/

double entropy(const vector<double>& probabilities) {
    double entropy_value = 0.0;
    for (double probability : probabilities) {
        if (probability > 0) {
            entropy_value -= probability * log2(probability);
        }
    }
    return entropy_value;
}
