#include <string>
#include <vector>
#include <stdexcept>
#include <bitset>
#include "Substitution_Cipher.hpp"
#include "Galois_field.hpp"
#include "Affine_Cipher.hpp"
#include "Translate.hpp"
#include "Translate_to_bin.hpp"
#include "toUpperCase.hpp"

    // class ERR_A_is_Zero {};

    // std::vector<int> bit_trans(std::string opText, std::string lang, int n) {
    //     std::string x;
    //     std::string str;
    //     std::vector<int> result;
    //     for (auto x1: opText) {
    //         x = x1;
    //         int num = translate(x, lang);
    //         auto bitnum = std::bitset<8>(num);
    //         str += bitnum.to_string();
    //     }
    //     for (int i=0; i<str.size(); i+=n) {
    //         auto z = std::bitset<8>(str.substr(i, n));
    //         auto t = (z).to_ulong();
    //         result.push_back(int(t));
    //     }
    //     return result;
    // }

    // std::string collapse(std::string col, int n) {

    //     return col.substr(col.size()-n, n);
    // }

    // std::string bit_untrans(std::string clText, std::string lang, int n) {
    //     std::string x;
    //     std::string str;
    //     std::string result;
    //     for (auto x1: clText) {
    //         x = x1;
    //         int num = translate(x, lang);
    //         auto bitnum = std::bitset<8>(num);
    //         auto col = bitnum.to_string();
    //         str += collapse(col, n);
    //     }
    //     for (int i=0; i<str.size(); i+=8) {
    //         auto z = std::bitset<8>(str.substr(i, 8));
    //         auto t = (z).to_ulong();
    //         result += untranslate(t, lang);
    //     }
    //     return result;
    // }

    std::string Affine_Cipher::Encrypt(std::string opText, int a, int b, std::string lang, int n) {
        if (a == 0) { throw std::invalid_argument("a is 0"); }
        if (n < 0) { throw std::invalid_argument("n below 0"); }
        if ( n != 0 && 8*opText.size() % n != 0) { throw std::invalid_argument("text isn`t divisible by n"); }
        // a--;
        Galois_field g{2,2};
        if (n > 0) {
            g = {2,n};
        } else {
            g = {3,3};
            // g = {2,8};
        }
        Polynomial g_a = g.multiGroup.at(a-1);
        Polynomial g_b = g.group.at(b);
        std::string clText = "";
        std::string y;
        std::vector<int> vec;
        opText = toUpperCase(opText);
        if (n > 0) {
            vec = bit_trans(opText, lang, n);        
        } else {
            std::string x;
            for (auto x1: opText) {
                x = x1;
                vec.push_back(translate(x, lang));
            }
        }
        for (auto num: vec) {
            Polynomial g_x = g.group.at(num);// t в многочлен переводим
            auto ml = g.atMultiTable(g_a, g_x);
            auto x2 = g.atSumTable(g.atMultiTable(g_a, g_x), g_b) ; // E(x)
            // x2 = reduce(x2);
            y = untranslate(x2.getVal(), lang);
            clText += y; // y переводим из многочлена в букву
        }
        return clText;

        // return opText;
    }
    
    std::string Affine_Cipher::Decrypt(std::string clText, int a, int b, std::string lang, int n) {
        // this->opText = "";
        // char x;
        // for (auto y: this->opText) {
        //     y = ;// t в многочлен переводим
        //     x = (y-b)*ra; // E(x)
        //     this->clText += x; // y переводим из многочлена в букву
        // }
        if (a == 0) { throw std::invalid_argument("a is 0"); }
        if (n < 0) { throw std::invalid_argument("n below 0"); }
        if ( n != 0 && 8*clText.size() % n != 0) { throw std::invalid_argument("text isn`t divisible by n"); }
        // a--;
        // Galois_field g{3,3};
        Galois_field g{2,2};
        if (n > 0) {
            g = {2,n};
        } else {
            g = {3,3};
            // g = {2,8};
        }
        Polynomial g_ra = g.atRevVector(g.multiGroup.at(a-1));
        Polynomial g_b = g.group.at(size_t(b));
        g_b = g_b * Polynomial{{Monomial{-1,0}}, g.getBase()}; // NEED TO FIX!!!!
        g_b = reduce(g_b);
        std::string opText = "";
        std::string y;
        std::vector<int> vec;
        clText = toUpperCase(clText);
        // if (n > 0) {
        //     vec = bit_untrans(clText, lang, n);        
        // } else {
        //     std::string x;
        //     for (auto x1: clText) {
        //         x = x1;
        //         vec.push_back(translate(x, lang));
        //     }
        // }
        std::string x;
        for (auto x1: clText) {
            x = x1;
            vec.push_back(translate(x, lang));
        }
        for (auto num: vec) {
            Polynomial g_y = g.group.at(size_t(num));// t в многочлен переводим
            auto q1 = g.atSumTable(g_y, g_b);
            auto x2 = g.atMultiTable(q1, g_ra);
            // auto x2 = g.atMultiTable(g.atSumTable(g_y, g_b), g_ra); // E(x) x = (y-b)*ra
            y = untranslate(x2.getVal(), lang);
            opText += y; // y переводим из многочлена в букву
        }
        if (n > 0) {
            opText = bit_untrans(opText, lang, n);        
        }
        return opText;

        // return clText;
    }