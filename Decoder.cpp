#include <iostream>
#include <algorithm>
#include "Decoder.h"

#define APPEND(v, x) { REV(v); v.push_back(x); REV(v); }

using namespace std;
using P = Polynomial;
using ul = unsigned long;

namespace Decoder {
    vector<P> _SFF(P);

    P SFF(P f) {
        vector<P> factors = _SFF(f);
        P accu = factors[0];
        for (unsigned long i = 1; i < factors.size(); i++)
            accu = accu * factors[i];
        return accu;
    }

    vector<P> _SFF(P f) {
        int i = 1;
        P R = Polynomial("1");
        P g = f.derivative();
        if (!g.is_zero()) {
            P c = gcd(f, g);
            P w = f | c;
            while (!w.is_one()) {
                P y = gcd(w, c);
                P z = w | y;
                P z_exp = z ^ i++;
                R = R * z_exp;
                w = y;
                c = c | y;
            }
            if (!c.is_one()) {
                c = c.sqrt();
                vector<P> result = _SFF(c);
                APPEND(result, R);
                return result;
            } else
                return {R};
        }
        else {
            f = f.sqrt();
            return _SFF(f);
        }
    }
}
