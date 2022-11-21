// #include <string>
#include "Monomial.hpp"

int Monomial::getKoef() { return this->koef; }
int Monomial::getPow() { return this->power; }
void Monomial::setKoef(int x) { this->koef=x; }
void Monomial::setPow(int x) { this->power=x;}
int Monomial::calc(int x, int base) {
    return (this->getKoef() * int(pow(x, this->power))) % base;
}

bool operator== (Monomial a, Monomial b) {
    if (a.getKoef() == b.getKoef() && a.getPow() == b.getPow())
        return true;
    return false;
}

Monomial operator* (Monomial a, Monomial b) {
    int k = a.getKoef() * b.getKoef();
    int p = a.getPow() + b.getPow();
    return Monomial(k, p);
}

// Monomial operator+ (Monomial a, Monomial b) {
//     // int k = a.getKoef() * b.getKoef();
//     // int p = a.getPow() + b.getPow();
//     // return Galois_field::Monomial(k, p);
// }

// Monomial operator- (Monomial a, Monomial b) {
//     // int k = a.getKoef() * b.getKoef();
//     // int p = a.getPow() + b.getPow();
//     // return Galois_field::Monomial(k, p);
// }