#include <vector>
#include <map>
#include "Monomial.hpp"
#include "Counter.hpp"
#include "Polynomial.hpp"


int Polynomial::getSize() const { 
    return this->size;
}

Monomial Polynomial::at(int num) const {
    return this->elem[num];
}

void Polynomial::sort() { // increase-sort
    std::map<int, int> m;
    for (int i=0; i<this->getSize(); i++) {
        Monomial el = this->at(i);
        m.insert({el.getPow(), el.getKoef()});
    }
    int i = 0;
    for (auto [x,y]: m) {
        this->elem[i].setPow(x);
        this->elem[i++].setKoef(y);
    }
}

int Polynomial::getVal() {
    int v = 0;
    int k = 0;
    int p = 0;
    for (int i =0; i<this->size; i++) {
        k = this->at(i).getKoef();
        p = this->at(i).getPow();
        v += int(k*pow(2,p));
    }
    return v;
}

bool operator== (const Polynomial& a, const Polynomial& b) {
if (a.getSize() != b.getSize())
    return false;
int y = 0;
for (int i =0; i< a.getSize(); i++) {
    if (a.at(i) == b.at(i))
        y++;
}
if (y == a.getSize())
    return true;
return false;
}

Polynomial operator* (Polynomial a, Polynomial b) {
    std::map<int, int> m; // pow koef
    // int y = 0;
    for (int i=0; i<a.getSize(); i++) {
        for (int j=0; j<b.getSize();j++) {
            // arr[y++] = a.at(i)*b.at(j);
            int pow = a.at(i).getPow()+b.at(j).getPow();
            int koef = a.at(i).getKoef()*b.at(j).getKoef();
            if (m.contains(pow)) {
                m[pow] += koef;
            } else {
                m.insert({a.at(i).getPow()+b.at(j).getPow(), a.at(i).getKoef()*b.at(j).getKoef()});

            }
        }
    }
    Monomial* arr = new Monomial[size_t(m.size())];
    int q = 0;
    for (const auto& [first, second]: m) {
        Monomial{second, first};
        arr[q].setPow(first);
        arr[q++].setKoef(second);
    }
    // Monomial* arr = new Monomial[size_t()];
    return Polynomial(arr, q);
}



Polynomial operator+ (Polynomial a, Polynomial b) {
    std::map<int, int> m; // pow koef
    // int y = 0;
    for (int i=0; i<a.getSize(); i++) {
        // m.insert({a.at(i).getPow(), a.at(i).getKoef()});
        int pow = a.at(i).getPow();
        int koef = a.at(i).getKoef();
        if (m.contains(pow)) {
                m[pow] += koef;
            } else {
                m.insert({pow, koef});
            }
    }
    for (int j=0; j<b.getSize();j++) {
        int pow = b.at(j).getPow();
        int koef = b.at(j).getKoef();
        if (m.contains(pow)) {
                m[pow] += koef;
            } else {
                m.insert({pow, koef});
            }
    }
    Monomial* arr = new Monomial[size_t(m.size())];
    int q = 0;
    for (const auto& [first, second]: m) {
        Monomial{second, first};
        arr[q].setPow(first);
        arr[q++].setKoef(second);
    }
    // Monomial* arr = new Monomial[size_t()];
    return Polynomial(arr, q);
}


// Polynomial operator- (Polynomial a, Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
// }