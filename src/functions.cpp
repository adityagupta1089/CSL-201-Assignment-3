#include "../include/include.h"

int integer_casting(std::string s) {
    int hc = 0;
    for (unsigned i = (s.length() > 3) ? s.length() - 4 : 0; i < s.length(); i++) {
        hc <<= 8;
        hc += (int) s.at(i);
    }
    return hc;
}

int component_sum(std::string s) {
    int hc = 0;
    for (unsigned i = 0; i < s.length(); i++)
        hc += (int) s.at(i);
    return hc;
}

int polynomial_sum(std::string s) {
    int hc = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        hc *= 31;
        hc += (int) s.at(i);
    }
    return hc;
}

int cyclic_sum(std::string s) {
    int hc = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        hc = (hc << 5) | (hc >> 27);
        hc += (int) s.at(i);
    }
    return hc;
}

int division(int x) {
    return abs(x) % _N;
}

int mad(int x) {
    return abs(_A * x + _B) % _N;
}

int multiplication(int x) {
    return floor((x * A - floor(x * A)) * ((double) _N));
}
