#include <iostream>
#include <algorithm>
#include <cassert>

#include "Decoder.h"

#define APPEND(a, b) { a.insert(a.end(), b.begin(), b.end()); }

using namespace std;
using P = Polynomial;
using ul = unsigned long;

namespace Decoder {
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
                result.insert(result.begin(), R);
                return result;
            } else
                return {R};
        }
        else {
            f = f.sqrt();
            return _SFF(f);
        }
    }
    P SFF(P f) {
        vector<P> factors = _SFF(f);
        P accu = factors[0];
        for (unsigned long i = 1; i < factors.size(); i++)
            accu = accu * factors[i];
        return accu;
    }
    FactorsWithDegree DDF(Polynomial A) {
        FactorsWithDegree fs;
        P p("100");
        int d = 1;
        while (A.degree() > 0) {
            P T = gcd(p + Polynomial("10"), A);
            if (!T.is_one())
                fs.push_back(PolynomialWithDegree(T, d));
            A = A | T;
            d++;
            p = p.square() % A;
        }
        return fs;
    }
//    FactorsWithDegree DDF(P f) {
//        FactorsWithDegree result = {};
//        P fs = f.copy();
//        int i = 1;
//        P x = P(vector<bool>{1, 0});
//        while (fs.degree() >= 2*i) {
//            P rotx = P(vector<bool>{1});
//            for (int j = 0; j < (1 << i); j++)
//                rotx.bits.push_back(0);
//            auto aa = rotx + x;
//            P g = gcd(fs, aa % fs);
//            if (!(g == string("1"))) {
//                result.push_back({g, i});
//                auto div = fs / g;
//                assert(div.second == "0");
//                fs = div.first;
//            }
//            i++;
//        }
//        result.push_back({NULL, 1});
//        return result;
//    }

    Factors _EDF(P A, int d) {
        if (A.degree() == d)
            return {A};
        for (;;) {
            P T = P::generate_random(1, 2 * d + 1);
            P W = T;
            for (int i = 0; i < d -1; i++) {
                T = T.square() % A;
                W += T;
            }
            P U = gcd(A, W);
            if (U.degree() > 0 && U.degree() < A.degree()) {
                Factors f1 = _EDF(U, d);
                Factors f2 = _EDF(A | U, d);
                APPEND(f1, f2);
                return f1;
            }
        }
    }
    Factors EDF(FactorsWithDegree fs) {
        Factors ret;
        for (PolynomialWithDegree f : fs)
            for (P ff: _EDF(f.first, f.second))
                ret.push_back(ff);
        return ret;
    }

    Factors FF(Polynomial p) {
        return EDF(DDF(SFF(p)));
    }
}
