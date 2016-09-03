#include <iostream>
#include <assert.h>
#include <algorithm>

#include "Polynomial.h"

using namespace std;

// Constructors
Polynomial::Polynomial(unsigned long size) : bits(vector<bool>(size)) {}

Polynomial::Polynomial(vector<bool> bits) : bits(bits) {}

Polynomial::Polynomial(string bitstring) {
    for (auto c : bitstring)
        this->bits.push_back(c == '1');
}

// GF operations
Polynomial Polynomial::operator=(const Polynomial &other) {
    return Polynomial(other.bits);
}

Polynomial Polynomial::operator<<(int offset) {
    rotate(bits.begin(), bits.begin() + offset, bits.end());
    for (unsigned long i = 0; i < offset; i++)
        bits[bits.size() - 1 - i] = false;
    return *this;
}

Polynomial Polynomial::operator>>(int offset) {
    reverse(bits.begin(), bits.end());
    *this << offset;
    reverse(bits.begin(), bits.end());
    return *this;
}

Polynomial operator+(Polynomial &p1, const Polynomial &p2) {
    return p1 += p2;
}

Polynomial Polynomial::operator+=(const Polynomial &other) {
    unsigned long size = bits.size();
    assert(size == other.bits.size());
    for (int i = 0; i < size; i++)
        bits[i] = bits[i] != other.bits[i];
    return *this;
}

Polynomial operator*(const Polynomial &a, const Polynomial &b) {
    unsigned long size = a.bits.size();
    assert(size == b.bits.size());
    Polynomial result(size * 2);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result.bits[i + j] = result.bits[i + j] != (a.bits[i] && b.bits[j]);

    return result;
}

// Utilities
unsigned long Polynomial::get_degree() const {
    return this->bits.size() - 1;
}

string Polynomial::to_bit_string() {
    string ret = "";
    for (auto b : bits)
        ret += b ? '1' : '0';
    return ret;
}

string Polynomial::to_expr() {
    string expr = "";
    unsigned long exponent = bits.size() - 1;
    for (auto b : bits) {
        if (exponent == 0)
            expr += b ? "1" : "0";
        else
            expr += (b ? ("x^" + to_string(exponent) + " + ") : "");
        exponent--;
    }
    return expr;
}


