#pragma once
#include <vector>
#include <map>
#include "Polynomial.hpp"

// int repeatFun(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += static_cast<int>(pow(x, z));
//     }
//     return (x-1)*s;
// }

class  Galois_field { // Поле Галуа
    int base = 0;
    int pow = 0;
    std::map<Polynomial, std::map<Polynomial, Polynomial>> sumTable;
    std::map<Polynomial, std::map<Polynomial, Polynomial>> multiTable;
    std::map<Polynomial, Polynomial> revVector;
    public:
    // Polynomial irrPolynomial{};
    std::vector<int> pole;
    std::vector<Polynomial> group;
    std::vector<Polynomial> multiGroup;
    // Galois_field(int y, int x = 2);
    // Galois_field(int y, int x = 2): base(x), pow(y) { // base pow
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
    // void constructIrrPolynomial();
    void constructMultiGroup();
    void constructSumTable();
    void constructMultiTable();
    // void constructRevVector();
    Polynomial atSumTable(Polynomial first, Polynomial second);
    Polynomial atMultiTable(Polynomial first, Polynomial second);
    void inSumTable(Polynomial first, Polynomial second, Polynomial elem);
    void inMultiTable(Polynomial first, Polynomial second, Polynomial elem);
    Polynomial sum(Polynomial a, Polynomial b);
    Polynomial multi(Polynomial a, Polynomial b);
};