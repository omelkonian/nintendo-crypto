
#include <iostream>
#include <ctime>
#include <chrono>

#include "Polynomial.h"
#include "Decoder.h"
#include "nintendo.h"

static int test_count = 1;
#define EQ(x, y) \
if (!(x == y)) \
{ \
    cout << endl << RED << "Assertion failed" << endl;\
    cout << " on line " << __LINE__  << endl;\
    cout << " in file " <<  __FILE__  << endl; \
    cout << x << " != " << y << RESET << endl; \
    exit(1); \
} \
else cout << test_count++ << " ";

#define IN(x, min, max) \
if ((x < min) || (x > max)) \
{ \
    cout << endl << RED << "Assertion failed" << endl;\
    cout << " on line " << __LINE__  << endl;\
    cout << " in file " <<  __FILE__  << endl; \
    cout << x << " not in " << '[' << min << ", " << max << ']' << RESET << endl; \
    exit(1); \
} \
else cout << test_count++ << " ";

#define DIV(x, y, q, r) { EQ((P(x) | P(y))._b(), q); EQ((P(x) % P(y))._b(), r) }

#define LOOP_COUNT 100
#define LOOP for (int i = 0; i < LOOP_COUNT; i++)

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#define TEST(x, y, s) { cout << "OUT\n " << encode(P(x)._b(), P(y)._b()) << endl; cout << "[" << (P(x) * P(y))._bW(s) << "]" << endl; }

using namespace std;
using P = Polynomial;

void random_tests();
void tests();

int main() {


    LOOP {
        P r1 = P::generate_random(1, 64);
        P r2 = P::generate_random(1, 64);
        TEST(r1, r2, 128);
    }


    /*TEST("1", "1111");
    TEST("1", "111111111111111111111111111111111111111");
    TEST("1", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("1", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    cout << endl << "====================================================================================================================================================" << endl;

    TEST("10", "1111");
    TEST("10", "111111111111111111111111111111111111111");
    TEST("10", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("10", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    cout << endl << "====================================================================================================================================================" << endl;

    TEST("100", "1111");
    TEST("100", "111111111111111111111111111111111111111");
    TEST("100", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("100", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    cout << endl << "====================================================================================================================================================" << endl;

    TEST("1000", "1111");
    TEST("1000", "111111111111111111111111111111111111111");
    TEST("1000", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("1000", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    cout << endl << "====================================================================================================================================================" << endl;

    TEST("10000000000000000000000000000000", "1111");
    TEST("10000000000000000000000000000000", "111111111111111111111111111111111111111");
    TEST("10000000000000000000000000000000", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("10000000000000000000000000000000", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

    cout << endl << "====================================================================================================================================================" << endl;

    TEST("1000000000000000000000000000000000", "1111");
    TEST("1000000000000000000000000000000000", "111111111111111111111111111111111111111");
    TEST("1000000000000000000000000000000000", "1111111111111111111111111111111111111111111111111111111111111111111");
    TEST("1000000000000000000000000000000000", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");*/

//    cout << endl << endl << GREEN << "Encoding (64-bit): " << RESET;
//    cout << endl;
//    LOOP {
//        P r1 = P::generate_random(50, 63);
//        P r2 = P::generate_random(50, 63);
//        cout << "R1: " << r1._b() << endl;
//        cout << "R2: " << r2._b() << endl;
////        EQ(r2._b(), encode("1", r2._b()));
//        EQ((r1 * r2)._b(), encode(r1._b(), r2._b()));
//    }
    /*tests();

    srand(time(NULL));
    random_tests();*/

    return 0;

    /*srand(666);
    int count = 0, total = 0;
    LOOP {
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();

//        cout << Decoder::EDF(P("110011001110111111000100000000101000110010100001000111110110111"), 31).to_string() << endl;
        cout << Decoder::EDF(P("111001110101111"), 7).to_string() << endl;
        cout << Decoder::EDF(P("1110011100000110111011111000001"), 15).to_string() << endl;

        chrono::steady_clock::time_point end= chrono::steady_clock::now();

        total += chrono::duration_cast<chrono::milliseconds>(end - begin).count();
        count++;
    }
    cout << "TIME: " << total/count << endl;

    return 0;*/
}

void tests() {

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
    //                         x^62 + x^61 + x^58 + x^57 + x^54 + x^53 + x^52 + x^50 + x^49 + x^48 + x^47 + x^46 + x^45 + x^41 + x^32 + x^30 + x^26 + x^25 + x^22 + x^20 + x^15 + x^11 + x^10 + x^9 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
    /*string x("10110000110000010101001011111001");
    string y("11101011111100101000001100011111");
    string actual = (P(x) * P(y))._b();
    string expected = encode(x, y);
    EQ(actual, expected);*/

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
    EQ(gcd(P("101101111"), P("10101"))._b(), "10101");

    cout << endl << endl << GREEN << "Derivative: " << RESET;
    EQ(P("101101111").derivative()._b(), "10101");
    EQ(P("1011").derivative()._b(), "101");

    cout << endl << endl << GREEN << "Square-Sqrt: " << RESET;
    EQ(P("110").square()._b(), "10100");
    EQ(P("110").square().square()._b(), "100010000");
    EQ(P("10100").sqrt()._b(), "110");

    cout << endl << endl << GREEN << "SFF: " << RESET;
    Factors fs = Decoder::SFF(P("101101111"));
    EQ(fs[1]._b(), "10011");
    EQ(fs[2]._b(), "111");

    cout << endl << endl << GREEN << "DDF: " << RESET;
    /*auto akdfj = P(vector<bool>{true});
    auto abc = Decoder::DDF(P("1110110111110001000010100110001010000000010001111110111001100110"));
    auto def = P("1010") / P("110");
    auto aaa = P("101") * P("101");*/

    /*cout << endl << endl << GREEN << "EDF: " << RESET;
    srand(1);
    auto fss = Decoder::EDF(P("10100010000101011"), 8);
    EQ(fss[0]._b(), "101011111");
    EQ(fss[1]._b(), "100011101");*/

    cout << endl << endl << "================================================================================================" << RESET << endl;
    cout << "\t\t\t PASSED" << endl;
    cout << "================================================================================================" << endl;
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
    /*LOOP {
        P r1 = P::generate_random(31, 31), r2 = P::generate_random(31, 31);
        EQ((r1 * r2)._b(), encode(r1._b(), r2._b()));
    }*/

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
    /*LOOP {
        P r = P::generate_random(3, 3);
        P A = r.square();
        auto res = Decoder::SFF(A);
        EQ(res[1]._b(), "1");
        EQ(res[2]._b(), r._b());
    }*/

    cout << endl << endl << GREEN << "DDF: " << RESET;

    cout << endl << endl << GREEN << "EDF: " << RESET;

    cout << endl << endl << GREEN << "Encoding (64-bit): " << RESET;
    cout << endl;
    LOOP {
        P r1 = P::generate_random(50, 63), r2 = P::generate_random(50, 63);
        cout << "R1: " << r1._b() << endl;
        cout << "R2: " << r2._b() << endl;
        EQ((r1 * r2)._b(), encode(r1._b(), r2._b()));
    }

    cout << endl << endl << GREEN << "================================================================================================" << RESET << endl;
    cout << "\t\t\t PASSED (Random)" << endl;
    cout << "================================================================================================" << endl;
}