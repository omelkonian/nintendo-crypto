#ifndef NINTENDO_POLYNOMIAL_H
#define NINTENDO_POLYNOMIAL_H

#include <vector>
#include <string>

#define REV(v) { reverse(v.begin(), v.end()); }

using namespace std;

class Polynomial {
public:
    vector<bool> bits;

    // Constructors
    Polynomial();
    Polynomial(unsigned long);
    Polynomial(vector<bool>);
    Polynomial(string);

    /******************************************************************************************************************/

    /**
     * GF Operations
     */
    // Addition
    Polynomial operator+=(const Polynomial &);
    friend Polynomial operator+(Polynomial &, const Polynomial &);

    // Multiplication
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend Polynomial operator^(const Polynomial &, int);
    Polynomial square() const;
    Polynomial sqrt() const;

    // Division
    friend pair<Polynomial, Polynomial> operator/(const Polynomial &, const Polynomial &);
    friend Polynomial operator|(const Polynomial &, const Polynomial &);
    friend Polynomial operator%(const Polynomial &, const Polynomial &);

    // GCD
    friend Polynomial gcd(const Polynomial &, const Polynomial &);

    // Derivative
    Polynomial derivative();

    // Shift
    Polynomial operator<<(int);
    Polynomial operator>>(int);

    /******************************************************************************************************************/

    // Utilities
    static Polynomial generate_random(int, int);
    friend bool operator==(const Polynomial &, string);
    unsigned long degree() const;
    unsigned long size() const { return bits.size(); }
    static void bring_to_same_size(Polynomial*, Polynomial*);
    static Polynomial ones(unsigned long);
    bool is_zero() const;
    bool is_one() const;
    Polynomial copy() const;
    Polynomial monic() const;
    string to_expr() const;
    string _b()const;
};

#endif //NINTENDO_POLYNOMIAL_H
