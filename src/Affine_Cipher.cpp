#include <string>
#include <stdexcept>
#include "Substitution_Cipher.hpp"
#include "Galois_field.hpp"
#include "Affine_Cipher.hpp"
#include "Translate.hpp"
#include "toUpperCase.hpp"
    // class ERR_A_is_Zero {};
    std::string Affine_Cipher::Encrypt(std::string opText, int a, int b, std::string lang) {
        if (a == 0) { throw std::invalid_argument("a is 0"); }
        a--;
        Galois_field g{3,3};
        Polynomial g_a = g.multiGroup.at(a);
        Polynomial g_b = g.group.at(b);
        std::string clText = "";
        std::string x;
        std::string y;
        opText = toUpperCase(opText);
        for (auto x1: opText) {
            x = x1;
            int num = translate(x, lang);
            Polynomial g_x = g.group.at(num);// t в многочлен переводим
            auto ml = g.atMultiTable(g_a, g_x);
            auto x2 = g.atSumTable(g.atMultiTable(g_a, g_x), g_b) ; // E(x)
            y = untranslate(x2.getVal(), lang);
            clText += y; // y переводим из многочлена в букву
        }
        return clText;

        // return opText;
    }
    
    std::string Affine_Cipher::Decrypt(std::string clText, int a, int b, std::string lang) {
        // this->opText = "";
        // char x;
        // for (auto y: this->opText) {
        //     y = ;// t в многочлен переводим
        //     x = (y-b)*ra; // E(x)
        //     this->clText += x; // y переводим из многочлена в букву
        // }
        if (a == 0) { throw std::invalid_argument("a is 0"); }
        // a--;
        Galois_field g{3,3};
        Polynomial g_ra = g.atRevVector(g.multiGroup.at(a));
        Polynomial g_b = g.group.at(b);
        g_b = g_b * Polynomial{{Monomial{-1,0}}, g.getBase()}; // NEED TO FIX!!!!
        g_b = reduce(g_b);
        std::string opText = "";
        std::string x;
        std::string y;
        clText = toUpperCase(clText);
        for (auto y1: clText) {
            y = y1;
            int num = translate(y, lang);
            Polynomial g_y = g.group.at(num);// t в многочлен переводим
            auto q1 = g.atSumTable(g_y, g_b);
            auto x2 = g.atMultiTable(q1, g_ra);
            // auto x2 = g.atMultiTable(g.atSumTable(g_y, g_b), g_ra); // E(x) x = (y-b)*ra
            y = untranslate(x2.getVal(), lang);
            opText += y; // y переводим из многочлена в букву
        }
        return opText;

        // return clText;
    }