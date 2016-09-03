#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

string encode(vector<string> inputs)
{
    int size = (int) (inputs.size() * 16);

    unsigned int* a = new unsigned int[size / 16]; // <- input tab to encrypt
    unsigned int* b = new unsigned int[size / 16]; // <- output tab

    for (int i = 0; i < size / 16; i++) {   // Read size / 16 integers to a
        stringstream ss;
        ss << hex << bitset<32>(inputs[i]).to_ulong();
        ss >> a[i];
    }

    for (int i = 0; i < size / 16; i++) {   // Write size / 16 zeros to b
        b[i] = 0;
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            b[(i + j) / 32] ^= ( (a[i / 32] >> (i % 32)) &
                                 (a[j / 32 + size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation
        }

    // Un-permutate
    string ret = "";
    for(int i = 0; i < size / 16; i++) {
        string s = bitset<32>(b[i]).to_string();
        reverse(s.begin(), s.end());
        ret += s;
    }

    return ret;
}