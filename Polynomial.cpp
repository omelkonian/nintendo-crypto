#include <iostream>
#include <assert.h>
#include <algorithm>

#include "Polynomial.h"

using namespace std;
using P = Polynomial;
using ul = unsigned long;
using V = vector<bool>;

// Constructors
Polynomial::Polynomial() {
}
Polynomial::Polynomial(ul size) : bits(V(size)) {}

Polynomial::Polynomial(V bits) : bits(bits) {}

Polynomial::Polynomial(string bitstring) {
    for (auto c : bitstring)
        bits.push_back(c == '1');
}

// GF operations
void Polynomial::operator=(const Polynomial &other) {
    this->bits = other.bits;
}

Polynomial Polynomial::operator<<(int offset) {
    rotate(bits.begin(), bits.begin() + offset, bits.end());
    for (ul i = 0; i < offset; i++)
        bits[bits.size() - 1 - i] = false;
    return *this;
}

Polynomial Polynomial::operator>>(int offset) {
    REV(bits);
    *this << offset;
    REV(bits);
    return *this;
}

P operator+(P &p1, const P &p2) {
    return p1 += p2;
}

P Polynomial::operator+=(const P &other) {
    ul size = bits.size();
    assert(size == other.size());
    for (int i = 0; i < size; i++)
        bits[i] = bits[i] != other.bits[i];
    return *this;
}

P operator*(const P &_a, const P &_b) {
    P a = _a.copy(), b = _b.copy();
    P::bring_to_same_size(&a, &b);
    ul size = a.size();
    assert(size == b.size());

    P result(size * 2);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result.bits[i + j + 1] = result.bits[i + j + 1] != (a.bits[i] && b.bits[j]);

    return result.trim();
}

P Polynomial::square() const {
    auto accu = V();
    for (auto b : bits) {
        accu.push_back(0);
        accu.push_back(b);
    }
    return P(accu);
}

P Polynomial::sqrt() const {
    auto accu = V();
    for (ul i = 0; i < bits.size(); i+=2)
        accu.push_back(bits[i]);
    return P(accu);
}

pair<P, P> operator/(const P &_a, const P &_b) {
    P a = _a.copy(), b = _b.copy();
    ul m = a.degree(), n = b.degree();
    V u = a.bits, v = b.bits, q(m - n + 1);
    auto monic = v[0];
    for (ul k = 0; k < m - n + 1; k++) {
        q[k] = u[k] && monic;
        if (!q[k]) continue;
        for (ul j = k; j < k + n + 1; j++)
            u[j] = (u[j] != (q[k] && v[j - k]));
    }
    V r(n);
    for (ul i = 0; i < r.size(); i++)
        r[i] = u[m - r.size() + 1 + i];

    return pair<P, P>(P(q), P(r));
}

P operator|(const P &a, const P &b) {
    return (a / b).first;
};

P operator%(const P &a, const P &b) {
    return (a / b).second;
};

P gcd(const P &a, const P &b) {
    P u = a.trim(), v = b.trim();
    if (v.is_zero()) return u;
    return gcd(v, u % v);
}

P Polynomial::derivative() {
    P ret = this->copy();
    for (ul i = (bits.size() % 2 == 0) ? 1 : 0; i < bits.size(); i += 2)
        ret.bits[i] = 0;
    return ret >> 1;
}

// Utilities
ul Polynomial::degree() const {
    for (ul i = 0; i < bits.size(); i++)
        if (bits[i]) return bits.size() - 1 - i;
    return 0;
}

bool Polynomial::is_zero() const {
    for (auto b : bits)
        if (b) return false;
    return true;
}

bool Polynomial::is_one() const {
    for (ul i = 0; i < bits.size() - 1; i++)
        if (bits[i]) return false;
    return bits[bits.size() - 1];
}

bool operator==(const P &a, const P &b) {
    if (a.degree() != b.degree())
        return false;
    for (int i = 0; i < a.size(); i++)
        if (a.bits[i] != b.bits[i])
            return false;
    return true;
}

P Polynomial::copy() const {
    P ret(bits.size());
    std::copy(bits.begin(), bits.end(), ret.bits.begin());
    return ret;
}

string Polynomial::_b() const {
    string ret = "";
    for (auto b : bits)
        ret += b ? '1' : '0';
    ret.erase(0, min(ret.find_first_not_of('0'), ret.size()-1));
    return ret;
}

string Polynomial::to_expr() const {
    string expr = "";
    ul exponent = bits.size() - 1;
    for (auto b : bits) {
        if (exponent == 0)
            expr += b;
        else
            expr += (b ? ("x^" + to_string(exponent) + " + ") : "");
        exponent--;
    }
    return expr;
}

P Polynomial::trim() const {
    ul start = 0;
    for (; start < bits.size(); start++) if (bits[start]) break;
    V new_bits(bits.begin() + start, bits.end());
    return P(new_bits);
}

P Polynomial::ones(ul n) {
    string accu = "";
    for (int i = 0; i < n; i++)
        accu += '1';
    return P(accu);
}

P operator^(const P &p, int exponent) {
    P ret = p.copy();
    if (exponent == 0)
        return P::ones(p.degree());
    for (int i = 1; i < exponent; i++)
        ret = ret * ret;
    return ret;
}

void Polynomial::bring_to_same_size(P *a, P *b) {
    if (a->size() < b->size())
        bring_to_same_size(b, a);
    else if (a->size() > b->size()) {
        ul offset = a->size() - b->size();
        REV(b->bits);
        for (ul i = 0; i < offset; i++)
            b->bits.push_back(0);
        REV(b->bits);
    }
}


