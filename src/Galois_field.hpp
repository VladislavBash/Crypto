#pragma once
#include <vector>
#include "Polynomial.hpp"
class  Galois_field { // Поле Галуа
    int p;
    int n;
    std::vector<int> pole;
    std::vector<Polynomial> group;
    public:
    Galois_field(int y, int x = 2);
    ~Galois_field();
};