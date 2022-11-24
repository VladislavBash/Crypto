#include <string>
#include <stdexcept>
#include "Substitution_Cipher.hpp"
#include "Galois_field.hpp"
#include "Recurrent_Affine_Cipher.hpp"
#include "Translate.hpp"
#include "toUpperCase.hpp"

std::string Recurrent_Affine_Cipher::Encrypt(std::string opText, int a1, int a2, int b1, int b2, std::string lang) {
    if (a1 == 0) { throw std::invalid_argument("a1 is 0"); }
    if (a2 == 0) { throw std::invalid_argument("a2 is 0"); }
    // a1--;
    // a2--;
    Galois_field g{3,3};
    std::string clText = "";
    std::string x;
    std::string y;
    Polynomial g_a{{Monomial{0,0}}, g.getBase()};
    Polynomial g_b{{Monomial{0,0}}, g.getBase()};
    std::vector<Polynomial> a;
    std::vector<Polynomial> b;
    int k = 0;
    opText = toUpperCase(opText);
    for (auto x1: opText) {
        x = x1;
        int num = translate(x, lang);
        Polynomial g_x = g.group.at(num);// t в многочлен переводим
        switch (k)
        {
        case 0:
            g_a = g.multiGroup.at(a1);
            g_b = g.group.at(b1);
            a.push_back(g_a);
            b.push_back(g_b);
            k++;
            break;
        case 1:
            g_a = g.multiGroup.at(a2);
            g_b = g.group.at(b2);
            a.push_back(g_a);
            b.push_back(g_b);
            k++;
            break;
        default:
            // g_a = a.at(k-1) * a.at(k-2);
            g_a = g.atMultiTable(a.at(k-1), a.at(k-2));
            // g_a = reduce(g_a);
            // g_b = b.at(k-1) + b.at(k-2);
            g_b = g.atMultiTable(b.at(k-1), b.at(k-2));
            // g_b = reduce(g_b);
            a.push_back(g_a);
            b.push_back(g_b);
            k++;
            break;
        }
            // Polynomial g_a = g.group.at();
            // Polynomial g_b = g.group.at();

            auto x2 = g.atSumTable(g.atMultiTable(g_a, g_x), g_b) ; // E(x)
            y = untranslate(x2.getVal(), lang);
            clText += y; // y переводим из многочлена в букву
    }
    return clText;
        // return opText;
}

std::string Recurrent_Affine_Cipher::Decrypt(std::string clText, int a1, int a2, int b1, int b2, std::string lang) {
    // this->opText = "";
    // char x;
    // for (auto y: this->opText) {
    //     y = ;// t в многочлен переводим
    //     x = (y-b)*ra; // E(x)
    //     this->clText += x; // y переводим из многочлена в букву
    // }
    // if (a1 == 0) { throw ERR_A1_is_Zero(); }
    // if (a2 == 0) { throw ERR_A2_is_Zero(); }
    if (a1 == 0) { throw std::invalid_argument("a1 is 0"); }
    if (a2 == 0) { throw std::invalid_argument("a2 is 0"); }
    // a1--;
    // a2--;
    Galois_field g{3,3};
    std::string opText = "";
    std::string x;
    std::string y;
    Polynomial g_ra{{Monomial{0,0}}, g.getBase()};
    Polynomial g_b{{Monomial{0,0}}, g.getBase()};
    std::vector<Polynomial> a;
    std::vector<Polynomial> b;
    int k = 0;
    clText = toUpperCase(clText);
    for (auto y1: clText) {
        y = y1;
        int num = translate(y, lang);
        Polynomial g_y = g.group.at(num);// t в многочлен переводим
        switch (k)
        {
        case 0:
            g_ra = g.atRevVector(g.multiGroup.at(a1));
            g_b = g.group.at(b1);
            a.push_back(g_ra);
            b.push_back(g_b);
            k++;
            break;
        case 1:
            g_ra = g.atRevVector(g.multiGroup.at(a2));
            g_b = g.group.at(b2);
            a.push_back(g_ra);
            b.push_back(g_b);
            k++;
            break;
        default:
            // g_ra = a.at(k-1) * a.at(k-2);
            g_ra = g.atMultiTable(a.at(k-1), a.at(k-2));
            // g_b = b.at(k-1) + b.at(k-2);
            g_b = g.atMultiTable(b.at(k-1), b.at(k-2));
            a.push_back(g_ra);
            b.push_back(g_b);
            k++;
            break;
        }
        // Polynomial g_ra = g.atRevVector(g.group.at());
        // Polynomial g_b = g.group.at();
        g_b = g_b * Polynomial{{Monomial{-1,0}}, g.getBase()};
        g_b = reduce(g_b);
        auto y2 = g.atMultiTable(g.atSumTable(g_y, g_b), g_ra); // E(x) x = (y-b)*ra
        y = untranslate(y2.getVal(), lang);
        opText += y; // y переводим из многочлена в букву
    }
    return opText;
    // return clText;
}