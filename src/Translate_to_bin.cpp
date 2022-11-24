#include <vector>
#include <string>
#include <bitset>
#include "Translate.hpp"
#include "Translate_to_bin.hpp"

std::vector<int> bit_trans(std::string opText, std::string lang, int n) {
    std::string x;
    std::string str;
    std::vector<int> result;
    for (auto x1: opText) {
        x = x1;
        int num = translate(x, lang);
        auto bitnum = std::bitset<8>(num);
        str += bitnum.to_string();
    }
    for (int i=0; i<str.size(); i+=n) {
        auto z = std::bitset<8>(str.substr(i, n));
        auto t = (z).to_ulong();
        result.push_back(int(t));
    }
    return result;
}
std::string collapse(std::string col, int n) {
    return col.substr(col.size()-n, n);
}
std::string bit_untrans(std::string clText, std::string lang, int n) {
    std::string x;
    std::string str;
    std::string result;
    for (auto x1: clText) {
        x = x1;
        int num = translate(x, lang);
        auto bitnum = std::bitset<8>(num);
        auto col = bitnum.to_string();
        str += collapse(col, n);
    }
    for (int i=0; i<str.size(); i+=8) {
        auto z = std::bitset<8>(str.substr(i, 8));
        auto t = (z).to_ulong();
        result += untranslate(t, lang);
    }
    return result;
}