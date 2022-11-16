#include <iostream>
#include "crypto.hpp"
int main(int, char**) {
    // Big arr{X{1,4}, X{2,3}, X{6,2}, X{9,1}};
    // std::cout << arr.at(2).getKoef();
    Galois_field::Polynomial a{Galois_field::Monomial{3, 2}, Galois_field::Monomial{1, 0}};
    Galois_field::Polynomial b{Galois_field::Monomial{1, 2}};
    Galois_field::Polynomial c = a*b;
    std::cout << c.at(0).getKoef() << std::endl;
    std::cout << c.at(0).getPow() << std::endl;
    std::cout << c.at(1).getKoef() << std::endl;
    std::cout << c.at(1).getPow() << std::endl;
}