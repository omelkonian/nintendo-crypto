#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Polynomial.h"
#include "Decoder.h"
#include "nintendo.h"

static int i = 1;
#define EQ(x, y) \
if (!(x == y)) \
{ \
    cerr << "Assertion failed" << endl;\
    cerr << " on line " << __LINE__  << endl;\
    cerr << " in file " <<  __FILE__  << endl; \
    cerr << x << " != " << y << endl; \
    exit(1); \
} \
else cout << i++ << ": pass" << endl;
#define DIV(x, y, q, r) { EQ((P(x) | P(y))._b(), q); EQ((P(x) % P(y))._b(), r) }

using namespace std;
using P = Polynomial;


int main() {
    EQ(P("00011001010").monic().degree(), 7);
    EQ(P("00011001010").monic().size(), 8);
    EQ(P("00011001010").monic()._b(), "11001010");
    EQ(P("1010").degree(), 3);
    EQ(P("101101").degree(), 5);
    EQ(P("101101").degree(), 5);
    EQ(P("001").is_one(), true);
    EQ(P("1").is_one(), true);
    EQ(P("00101011").is_one(), false);
    EQ(P("0").is_zero(), true);
    EQ(P("00000").is_zero(), true);
    EQ(P("1101010").is_zero(), false);

    //    b0c152f9           => 10110000110000010101001011111001 [10011111010010101000001100001101]
    //  x ebf2831f           => 11101011111100101000001100011111 [11111000110000010100111111010111]
    //  = 46508fb7 6677e201  => 01000110010100001000111110110111 01100110011101111110001000000001
    //                         [11101101111100010000101001100010 10000000010001111110111001100110]
    string actual = (P("10011111010010101000001100001101") * P("11111000110000010100111111010111"))._b();
    string expected = encode({"10110000110000010101001011111001", "11101011111100101000001100011111"});
    EQ(actual, expected);

    srand(time(NULL));
    auto ffs = Decoder::EFF({pair<P, int>(P("1110110111110001000010100110001010000000010001111110111001100110"), 8)});
    EQ(ffs[0]._b(), "101011111");
    EQ(ffs[1]._b(), "100011101");

    // Multiplication
    P a("000001"), b("101011");
    P mul = a * b;
    EQ(mul._b(), "101011");

    P a2("110"), b2("110");
    P mul2 = a2 * b2;
    EQ(mul2._b(), "10100");

    // Division
    DIV("110011011", "101011", "1111", "10010");
    DIV("101101", "1010", "100", "101");
    DIV("101101111", "10101", "10011", "0");
    DIV("101011", "11", "11001", "0");
    DIV("101101111", "111", "1111001", "0");
    DIV("10100010000101011", "10001000000", "1010100", "100101011");

    // GCD
    EQ(gcd(P("101101"), P("1010"))._b(), "101");
    EQ(gcd(P("101011"), P("1010"))._b(), "11");

    // Derivative
    EQ(P("101101111").derivative()._b(), "10101");
    EQ(P("1011").derivative()._b(), "101");

    // Square-Sqrt
    EQ(P("110").square()._b(), "10100");
    EQ(P("110").square().square()._b(), "100010000");
    EQ(P("10100").sqrt()._b(), "110");

    EQ(gcd(P("101101111"), P("10101"))._b(), "10101");

    EQ(Decoder::SFF(P("101101111"))._b(), "1111001");

    auto fs = Decoder::EFF({pair<P, int>(P("10100010000101011"), 8)});
    EQ(fs[0]._b(), "101011111");
    EQ(fs[1]._b(), "100011101");

    cout << "================= PASSED =================" << endl;

    return 0;
}