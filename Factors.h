#ifndef NINTENDO_FACTORS_H
#define NINTENDO_FACTORS_H


#include <algorithm>
#include "Polynomial.h"

class Factors {
public:
    vector<Polynomial> factors;
    Factors() : factors() {}
    Factors(unsigned long size) : factors(vector<Polynomial>(size, Polynomial("1"))) {

    }
    Factors(const Polynomial &p) : factors({p}) {}
    Factors(const vector<Polynomial> &factors) : factors(factors) {}

    Factors operator*=(Polynomial p) {
        factors.push_back(p);
        return *this;
    }

    Polynomial& operator[](const int index) {
        return factors[index - 1];
    }

    unsigned long size() {
        return factors.size();
    }

    string to_string() {
        string ret = "";
        for (auto f : factors)
            ret += f._b() + " ";
        return ret;
    }
};


#endif //NINTENDO_FACTORS_H
