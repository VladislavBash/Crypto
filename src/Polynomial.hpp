#pragma once
#include <vector>
#include "Monomial.hpp"
#include "Counter.hpp"
class Polynomial { // Многочлен, по сути массив одночленов
    private:
    int size = 0;
    int val = 0;
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
    Polynomial(Counter& lst): size(lst.getSize()) {
        this->elem = new Monomial[static_cast<unsigned long long>(lst.getSize())];
        int kof = 0;
        int pw = 0;
        for (int i =0; i<lst.getSize(); i++) {
            kof = lst.at(lst.getSize()-1-i);
            pw = i;
            this->elem[i].setKoef(kof);
            this->elem[i].setPow(pw);
        }
        val = this->getVal();
    }
    Polynomial(std::initializer_list<Monomial> lst): size(static_cast<int>(lst.size())), elem(new Monomial[static_cast<unsigned long long>(size)])  {
        std::copy(lst.begin(), lst.end(), elem);
        this->sort();
        val = this->getVal();
    }
    Polynomial(Monomial*& lst, int s): size(s), elem(lst) {
        this->sort();
        val = this->getVal();
    }
    ~Polynomial() { 
        // if (this->size == 1) {
            elem = nullptr;
        // } else {
        //     delete[] elem;
        // }
    }
    int getSize() const;
    Monomial at(int num) const;
    void sort();
    int getVal();
    int calc(int x, int base);
};

bool operator== (const Polynomial& a, const Polynomial& b);
Polynomial operator* (Polynomial a, Polynomial b);
Polynomial operator+ (Polynomial a, Polynomial b);
// extern Polynomial operator- (Polynomial a, Polynomial b);