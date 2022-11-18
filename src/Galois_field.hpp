#pragma once
#include <vector>
#include <math.h>
#include "Polynomial.hpp"

// int repeatFun(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += static_cast<int>(pow(x, z));
//     }
//     return (x-1)*s;
// }

class  Galois_field { // Поле Галуа
    // int p = 0;
    // int n = 0;
    // sumTable;
    // mulTable;
    // revVector;
    public:
    std::vector<int> pole;
    std::vector<Polynomial> group;
    // Galois_field(int y, int x = 2);
    Galois_field(int y, int x = 2) {
    for (int i=0; i<x; i++) {
        this->pole.push_back(i);
    }
    Counter c{y,x};
    int s = 0;
    for (int z=0; z<y; z++) {
        s += static_cast<int>(pow(x, z));
    }
    int l = (x-1)*s;
    for (int k=0; k<l; k++) {
        Counter c1 = c;
        this->group.push_back(Polynomial{c1}); // 000 y = 3   0000 y = 4
        ++c;
    }
}
    ~Galois_field() {}
};