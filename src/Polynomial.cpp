#include <vector>
#include "Monomial.h"
#include "Counter.h"
#include "Polynomial.h"


    int Polynomial::getSize() const { 
        return this->size;
        }
    Monomial Polynomial::at(int num) {
        return this->elem[num];
    }

Polynomial operator* (Polynomial a, Polynomial b) {
    Monomial* arr = new Monomial[a.getSize()*b.getSize()]; // утечка памяти будет: ФИКСИТЬ!
    int y = 0;
    for (int i=0; i<a.getSize(); i++) {
        for (int j=0; j<b.getSize();j++) {
            arr[y++] = a.at(i)*b.at(j);
        }
    }
    return Polynomial(arr, a.getSize()*b.getSize());
}



Polynomial operator+ (Polynomial a, Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
}


Polynomial operator- (Polynomial a, Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
}