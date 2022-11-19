#pragma once
#include <string>
class Monomial { // koef pow
    int koef = 0;
    int pow = 0;
    public:
    Monomial() {}
    Monomial(int k, int p): koef(k), pow(p) {}
    Monomial(std::string str) {
        if (str.find('x') == 0) { // 15*x^42
            this->koef = 1;
        } else {
            std::string k = str.substr(0, str.find('x')-1);
            this->koef = std::stoi(k); // k = '60'
        }
        if (str.find('x') == str.size()-1) { // 15*x^42
            this->pow = 1;
        } else {
            std::string p = str.substr(str.find('x')+2, str.size()-1);
            this->pow = std::stoi(p); // k = '60'
        }
    }
    // Monomial(int k, int p);
    // Monomial(std::string str);
    ~Monomial() {}
    int getKoef();
    int getPow();
    void setKoef(int x);
    void setPow(int x);
};

// extern bool operator== (Monomial a, Monomial b);
bool operator== (Monomial a, Monomial b);
Monomial operator* (Monomial a, Monomial b);
// extern Monomial operator+ (Monomial a, Monomial b);
// extern Monomial operator- (Monomial a, Monomial b);