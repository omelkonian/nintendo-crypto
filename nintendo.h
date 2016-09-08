#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;
using ul = unsigned long;

string bring_to_size(string s, int size) {
    ul fill = size - s.size();
    return string(fill, '0').append(s);
}

string encode(string s1, string s2)
{
    ul siz = max(s1.size(), s2.size());
    int size = (siz <= 32) ? 32 : ((siz <= 64) ? 64 : (siz <= 128) ? 128 : 256);

    // Bring strings to <size>
    s1 = bring_to_size(s1, size);
    s2 = bring_to_size(s2, size);

    vector<string> inputs;
    for (ul i = 0; i < size / 32; i++)
        inputs.push_back(s1.substr(i * 32, 32));
    for (ul i = 0; i < size / 32; i++)
        inputs.push_back(s2.substr(i * 32, 32));

    cout << "\nIN\n"; for (string s : inputs) cout << s << " "; cout << endl;

    unsigned int* a = new unsigned int[size / 16];
    unsigned int* b = new unsigned int[size / 16];

    for (int i = 0; i < size / 16; i++) {
        stringstream ss;
        ss << hex << bitset<32>(inputs[i]).to_ulong();
        ss >> a[i];
    }

    for (int i = 0; i < size / 16; i++)
        b[i] = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            b[(i + j) / 32] ^= ((a[i / 32] >> (i % 32)) & (a[j / 32 + size / 32] >> (j % 32)) & 1) << ((i + j) % 32);   // Magic centaurian operation

    // Un-permutate
    vector<string> accu;
    for(int i = 0; i < size / 16/* - 1*/; i++)
        accu.push_back(bitset<32>(b[i]).to_string());
//    for (int i = 0; i < accu.size(); i += 2)
//        iter_swap(accu.begin() + i, accu.begin() + i + 1);
    string ret = "";
    int count = 1;
    for (string s : accu) {
        ret += s + " ";
        count++;
        if (count > 4) {
            ret += "\n ";
            count = 1;
        }
    }
//    ret.erase(0, min(ret.find_first_of('1'), ret.size()-1));

    return ret;
}