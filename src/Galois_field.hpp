#pragma once
#include <vector>
#include <map>
#include "Polynomial.hpp"

// int repeatFun(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += static_cast<int>(power(x, z));
//     }
//     return (x-1)*s;
// }

class  Galois_field { // Поле Галуа
    int base = 0;
    int power = 0;
    std::vector<std::vector<Polynomial>> sumTable;
    std::vector<std::vector<Polynomial>> multiTable;
    // std::vector<Polynomial> revVector;
    std::vector<Polynomial> revVector;
    public:
    Polynomial irrPolynomial{{Monomial{0,0}}, this->base};
    std::vector<int> pole;
    std::vector<Polynomial> group;
    std::vector<Polynomial> xpows;
    std::vector<Polynomial> multiGroup;
    // Galois_field(int y, int x = 2);
    // Galois_field(int y, int x = 2): base(x), power(y) { // base power
    // constructPole();
    // constructGroup();
    // constructMultiGroup();
    // constructSumTable();
    // constructMultiTable();
    // constructRevVector();
    // for (int i=0; i<x; i++) {
    //     this->pole.push_back(i);
    // Counter c{y,x};
    // for (int k=0; k<c.maxInc(); k++) {
    //     Counter c1 = c;
    //     this->group.push_back(Polynomial{c1}); // 000 y = 3   0000 y = 4
    //     ++c;
    // }
    // this->multygroup = this->group;
    // this->multygroup.erase(this->multygroup.begin());
// }
    Galois_field(int y, int x);
    ~Galois_field() {}
    void constructPole();
    void constructGroup();
    void constructIrrPolynomial();
    void constructMultiGroup();
    void constructSumTable();
    void constructMultiTable();
    // void constructRevVector();
    int getBase() const;
    Polynomial atSumTable(Polynomial first, Polynomial second);
    Polynomial atMultiTable(Polynomial first, Polynomial second);
    Polynomial atRevVector(Polynomial first);
    // void inSumTable(Polynomial first, Polynomial second, Polynomial elem);
    // void inMultiTable(Polynomial first, Polynomial second, Polynomial elem);
    Polynomial sum(Polynomial a, Polynomial b);
    Polynomial multi(Polynomial a, Polynomial b);
};

extern int rem(int x, int r);
Polynomial reduce(Polynomial c);