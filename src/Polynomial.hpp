#pragma once
#include <vector>
#include "Monomial.hpp"
#include "Counter.hpp"
class Polynomial { // Многочлен, по сути массив одночленов
    int size = 0;
    Monomial* elem = nullptr;
    public:
    // Polynomial(int lst): size(getSizeInt(lst)), elem(new Monomial[size]) { // Создаем 
    //     std::vector<Monomial> a;
    //     int k = 0;
    //     int l = 0;
    //     for (int i=0; i<this->size; i++) {
    //         l = lst / 10 * 10;
    //         k = lst % l;
    //         lst = l; 
    //         a.push_back(Monomial(k, i));
    //     }
    //     std::copy(a.begin(), a.end(), elem);
    // }
    Polynomial(Counter lst);
    Polynomial(std::initializer_list<Monomial> lst);
    Polynomial(Monomial* lst, int s);
    int getSize() const;
    Monomial at(int num);
};

// extern Polynomial operator* (Polynomial a, Polynomial b);
// extern Polynomial operator+ (Polynomial a, Polynomial b);
// extern Polynomial operator- (Polynomial a, Polynomial b);