#include <iostream>
#include <ctime>

#include "Polynomial.h"
#include "Decoder.h"
#include "nintendo.h"

static int test_count = 1;
#define EQ(x, y) \
if (!(x == y)) \
{ \
    cerr << endl << RED << "Assertion failed" << endl;\
    cerr << " on line " << __LINE__  << endl;\
    cerr << " in file " <<  __FILE__  << endl; \
    cerr << x << " != " << y << RESET << endl; \
    exit(1); \
} \
else cout << test_count++ << " ";

#define IN(x, min, max) \
if ((x < min) || (x > max)) \
{ \
    cerr << endl << RED << "Assertion failed" << endl;\
    cerr << " on line " << __LINE__  << endl;\
    cerr << " in file " <<  __FILE__  << endl; \
    cerr << x << " not in " << '[' << min << ", " << max << ']' << RESET << endl; \
    exit(1); \
} \
else cout << test_count++ << " ";

#define DIV(x, y, q, r) { EQ((P(x) | P(y))._b(), q); EQ((P(x) % P(y))._b(), r) }

#define LOOP_COUNT 500
#define LOOP for (int i = 0; i < LOOP_COUNT; i++)

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

using namespace std;
using P = Polynomial;

void random_tests();

int main() {

    cout << endl << endl << GREEN << "Basic utilities: " << RESET;
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

    cout << endl << endl << GREEN << "Multiplication: " << RESET;
    P a("000001"), b("101011");
    P mul = a * b;
    EQ(mul._b(), "101011");

    P a2("110"), b2("110");
    P mul2 = a2 * b2;
    EQ(mul2._b(), "10100");

    cout << endl << endl << GREEN << "Encoding: " << RESET;
    //    b0c152f9           => 10110000110000010101001011111001
    //  x ebf2831f           => 11101011111100101000001100011111
    //  = 46508fb7 6677e201  => 01000110010100001000111110110111 01100110011101111110001000000001
    //                         [01100110011101111110001000000001 01000110010100001000111110110111]
    string x("10110000110000010101001011111001");
    string y("11101011111100101000001100011111");
    string actual = (P(x) * P(y))._b();
    string expected = encode({x, y});
    EQ(actual, expected);

    cout << endl << endl << GREEN << "Division: " << RESET;
    DIV("110011011", "101011", "1111", "10010");
    DIV("101101", "1010", "100", "101");
    DIV("101101111", "10101", "10011", "0");
    DIV("101011", "11", "11001", "0");
    DIV("101101111", "111", "1111001", "0");
    DIV("10100010000101011", "10001000000", "1010100", "100101011");

    cout << endl << endl << GREEN << "GCD: " << RESET;
    EQ(gcd(P("101101"), P("1010"))._b(), "101");
    EQ(gcd(P("101011"), P("1010"))._b(), "11");

    cout << endl << endl << GREEN << "Derivative: " << RESET;
    EQ(P("101101111").derivative()._b(), "10101");
    EQ(P("1011").derivative()._b(), "101");

    cout << endl << endl << GREEN << "Square-Sqrt: " << RESET;
    EQ(P("110").square()._b(), "10100");
    EQ(P("110").square().square()._b(), "100010000");
    EQ(P("10100").sqrt()._b(), "110");

    cout << endl << endl << GREEN << "SFF: " << RESET;
    EQ(gcd(P("101101111"), P("10101"))._b(), "10101");
    EQ(Decoder::SFF(P("101101111"))._b(), "1111001");

    cout << endl << endl << GREEN << "DDF: " << RESET;
    /*auto akdfj = P(vector<bool>{true});
    auto abc = Decoder::DDF(P("1110110111110001000010100110001010000000010001111110111001100110"));
    auto def = P("1010") / P("110");
    auto aaa = P("101") * P("101");*/

    cout << endl << endl << GREEN << "EDF: " << RESET;
    srand(1);
    auto fs = Decoder::EDF({pair<P, int>(P("10100010000101011"), 8)});
    EQ(fs[0]._b(), "101011111");
    EQ(fs[1]._b(), "100011101");

    cout << endl << endl << "================================================================================================" << RESET << endl;
    cout << "\t\t\t PASSED" << endl;
    cout << "================================================================================================" << endl;

    srand(time(NULL));
    random_tests();

    cout << endl << endl << GREEN << "================================================================================================" << RESET << endl;
    cout << "\t\t\t PASSED (Random)" << endl;
    cout << "================================================================================================" << endl;

    return 0;
}

void random_tests() {

    cout << endl << endl << GREEN << "Rand: " << RESET;
    LOOP {
        IN(P::generate_random(10, 20).degree(), 10, 20);
        IN(P::generate_random(10, 10).degree(), 10, 10);
    }

    cout << endl << endl << GREEN << "Multiplication: " << RESET;
    LOOP {
        P r = P::generate_random(1, 60);
        EQ((r * P("1"))._b(), r._b());
    }

    cout << endl << endl << GREEN << "Division: " << RESET;
    LOOP {
        P d = P::generate_random(20, 32);
        P q = P::generate_random(5, 15);
        P r = P::generate_random(1, 10);
        P D = (d * q) + r;
        auto div = D / d;
        EQ(div.first._b(), q._b());
        EQ(div.second._b(), r._b());
    }

    cout << endl << endl << GREEN << "Encoding (32-bit): " << RESET;
    LOOP {
        P r1 = P::generate_random(31, 31), r2 = P::generate_random(31, 31);
        EQ((r1 * r2)._b(), encode({r1._b(), r2._b()}));
    }

    cout << endl << endl << GREEN << "GCD: " << RESET;
    LOOP {
        P r1 = P::generate_random(30, 60), r2 = P::generate_random(15, 30);
        P g = gcd(r1, r2);
        EQ((r1 % g)._b(), "0");
        EQ((r2 % g)._b(), "0");
    }

    cout << endl << endl << GREEN << "Square-Sqrt: " << RESET;
    LOOP {
        P r = P::generate_random(10, 50);
        EQ(r.square().size(), r.size() * 2 - 1);
        IN(r.sqrt().size(), r.size() / 2, r.size() / 2 + 1);
        EQ(r.square().sqrt().square().sqrt()._b(), r._b());
        EQ(r.square().square().sqrt().square().sqrt().sqrt()._b(), r._b());
    }

    cout << endl << endl << GREEN << "SFF: " << RESET;

    cout << endl << endl << GREEN << "DDF: " << RESET;

    cout << endl << endl << GREEN << "EDF: " << RESET;

    cout << endl << endl << GREEN << "Encoding (64-bit): " << RESET;
    LOOP {
        P r1 = P::generate_random(63, 63), r2 = P::generate_random(63, 63);
        EQ((r1 * r2)._b(), encode({r1._b(), r2._b()}));
    }

}