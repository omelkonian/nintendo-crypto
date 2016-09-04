#include <iostream>
#include "Polynomial.h"
#include "Decoder.h"
#include "nintendo.h"

#define ASS(x, y) \
if (!(x == y)) \
{ \
    cerr << "Assertion failed" << endl;\
    cerr << " on line " << __LINE__  << endl;\
    cerr << " in file " <<  __FILE__  << endl; \
    cerr << x << " != " << y << endl; \
    exit(1); \
}

using namespace std;
using P = Polynomial;

int main() {
    ASS(P("00011001010").trim().degree(), 7);
    ASS(P("00011001010").trim().size(), 8);
    ASS(P("00011001010").trim()._b(), "11001010");
    ASS(P("1010").degree(), 3);
    ASS(P("101101").degree(), 5);
    ASS(P("101101").degree(), 5);
    ASS(P("001").is_one(), true);
    ASS(P("1").is_one(), true);
    ASS(P("00101011").is_one(), false);
    ASS(P("0").is_zero(), true);
    ASS(P("00000").is_zero(), true);
    ASS(P("1101010").is_zero(), false);

    //    b0c152f9           => 10110000110000010101001011111001 [10011111010010101000001100001101]
    //  x ebf2831f           => 11101011111100101000001100011111 [11111000110000010100111111010111]
    //  = 46508fb7 6677e201  => 01000110010100001000111110110111 01100110011101111110001000000001
    //                         [11101101111100010000101001100010 10000000010001111110111001100110]
    string actual = (P("10011111010010101000001100001101") * P("11111000110000010100111111010111"))._b();
    string expected = encode({"10110000110000010101001011111001", "11101011111100101000001100011111"});
    ASS(actual, expected);

    // Multiplication
    P a("000001"), b("101011");
    P mul = a * b;
    ASS(mul._b(), "101011");

    P a2("110"), b2("110");
    P mul2 = a2 * b2;
    ASS(mul2._b(), "10100");

    // Division
    P d1("110011011"), d2("101011");
    auto div = d1 / d2;
    ASS(div.first._b(), "1111");
    ASS(div.second._b(), "10010");

    P d3("101101"), d4("1010");
    auto div2 = d3 / d4;
    ASS(div2.first._b(), "100");
    ASS(div2.second._b(), "101");

    P d5("101101111"), d6("10101");
    auto div3 = d5 / d6;
    ASS(div3.first._b(), "10011");
    ASS(div3.second._b(), "0");

    P d7("101011"), d8("11");
    auto div4 = d7 / d8;
    ASS(div4.first._b(), "11001");
    ASS(div4.second._b(), "0");

    P d9("101101111"), d10("111");
    auto div5 = d9 / d10;
    ASS(div5.first._b(), "1111001");
    ASS(div5.second._b(), "0");

    // GCD
    ASS(gcd(P("101101"), P("1010"))._b(), "101");
    ASS(gcd(P("101011"), P("1010"))._b(), "11");

    // Derivative
    ASS(P("101101111").derivative()._b(), "10101");
    ASS(P("1011").derivative()._b(), "101");

    // Square-Sqrt
    ASS(P("110").square()._b(), "10100");
    ASS(P("10100").sqrt()._b(), "110");

    ASS(gcd(P("101101111"), P("10101"))._b(), "10101");

    ASS(Decoder::SFF(P("101101111"))._b(), "1111001");

    cout << "================= PASSED =================" << endl;

    return 0;
}