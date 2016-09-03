#ifndef NINTENDO_POLYNOMIAL_H
#define NINTENDO_POLYNOMIAL_H

#include <vector>

using namespace std;

class Polynomial {
    vector<bool> bits;

public:
    // Constructors
    Polynomial(unsigned long);
    Polynomial(vector<bool>);
    Polynomial(string);

    /******************************************************************************************************************/

    /**
     * GF Operations
     */
    // Assignment
    Polynomial operator=(const Polynomial &);

    // Addition
    Polynomial operator+=(const Polynomial &);
    friend Polynomial operator+(Polynomial &, const Polynomial &);

    // Multiplication
    friend Polynomial operator*(const Polynomial &, const Polynomial &);

    // Shift
    Polynomial operator<<(int);
    Polynomial operator>>(int);

    /******************************************************************************************************************/

    // Utilities
    unsigned long get_degree() const;
    string to_expr();
    string to_bit_string();
};

#endif //NINTENDO_POLYNOMIAL_H
