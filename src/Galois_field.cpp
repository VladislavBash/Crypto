#include <vector>
#include <map>
#include "Galois_field.hpp"
#include "Polynomial.hpp"


// int times(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += power(x, z);
//     }
//     return (x-1)*s;
// }
int rem(int x, int r) {
    while (x < 0) {
        x += r;
    }
    return x % r;
}

// Polynomial fun(Polynomial c, int base) {
//     int s = c.getSize();
//     for (int i =0; i<c.getSize(); i++) {
//         auto q = c.at(i);
//         auto r = rem(q.getKoef(), base);
//         if (r == 0)
//             s--;
//         c.at(i).setKoef(r);
//     }
//     Monomial* lst = new Monomial[size_t(s)];
//     int j = 0;
//     for (int i=0; i<s; i++) {
//         if (c.at(i).getKoef() == 0) {
//         } else {
//             lst[j].setKoef(c.at(i).getKoef());
//             lst[j].setPow(c.at(i).getPow());
//             j++;
//         }
//     }
//     return Polynomial{lst, s};
// }

int Galois_field::getBase() const { return this->base; }

Polynomial reduce(Polynomial c) {
    int s = c.getSize();
    int j = 0;
    Monomial* lst = new Monomial[size_t(s)];
    for (int i =0; i<c.getSize(); i++) {
        auto q = c.at(i);
        auto r = rem(q.getKoef(), c.getBase());
        if (r == 0) {
            s--;
        } else {
            lst[j].setKoef(r);
            lst[j++].setPow(q.getPow());
        } // можно удалить "хвост"  у lst
    }
    Monomial* lst1 = new Monomial[size_t(j)];
        for (int z=0; z<j; z++) {
            lst1[z] = lst[z];
        }
    return Polynomial{lst1, s, c.getBase()};
}

Galois_field::Galois_field(int y, int x = 2): base(y), power(x) { // base power
    constructPole();
    constructGroup();
    constructIrrPolynomial();
    constructMultiGroup();
    this->revVector = std::vector<Polynomial>((this->multiGroup.size()), Polynomial{{Monomial{0,0}},this->base});
    constructSumTable();
    constructMultiTable();
}

void Galois_field::constructPole() {
    for (int i=0; i<this->base; i++) {
        this->pole.push_back(i);
    }
}

void Galois_field::constructGroup() {
    Counter c{this->power,this->base};
    for (int k=0; k<c.maxInc(); k++) {
        this->group.push_back(Polynomial{c, this->base}); // 000 y = 3   0000 y = 4
        ++c;
    }
    this->group.push_back(Polynomial{c, this->base});
}

void Galois_field::constructIrrPolynomial() {
    Counter c{this->power, this->base};
    Counter d{this->power+1, this->base};
    d = d + c.maxInc() ;
    int cont = 0;
    for (int i=0; i<=c.maxInc(); i++) {
        ++d;
        auto y = Polynomial{d, this->base};
        for (auto x: this->pole) {
            auto cac = y.calc(x, this->base);
            if (y.calc(x, this->base) != 0)
                cont++;
        }
        if (cont == this->base) {
            this->irrPolynomial = reduce(y);
            break;
        }
        cont = 0;
    }
}

void Galois_field::constructMultiGroup() {
    this->multiGroup = this->group;
    this->multiGroup.erase(this->multiGroup.begin());
}

void Galois_field::constructSumTable() {
    std::vector<Polynomial> v;
    int cont1 = 0;
    int cont2 = 0;
    for (auto j: this->group) {
        // sumTable.push_back();
        // auto y = std::map<Polynomial, Polynomial> {j,j};
        // sumTable.insert({j, y});
        // sumTable.insert({j, std::map<Polynomial,Polynomial>()});
        // sumTable[j].insert(std::make_pair(j,j));
        // sumTable.insert(std::make_pair(j,std::map<Polynomial, Polynomial>(j,j)));
        for (auto i: this->group) {
            if (cont1 < cont2) {
                v.push_back(sumTable.at(i.getVal()).at(j.getVal()));
                cont1++;
            } else {
                v.push_back(sum(j, i));
            }
            // sumTable[j] = {i, i};
            // sumTable[j].insert(std::make_pair(i,i));
            // auto elem = sum(j, i);
            // inSumTable(j, i, elem);
        }
        sumTable.push_back(v);
        v.clear();
        cont2++;
    }
}

void Galois_field::constructMultiTable() {
    // for (auto j: this->group) {
    //     for (auto i: this->group) {
    //         auto elem = multi(j, i);
    //         if (elem == Polynomial{Monomial{1,0}})
    //             this->revVector.insert({i,j});
    //         inMultiTable(j, i, elem);
    //     }
    // }
    std::vector<Polynomial> v;
    int cont1 = 0;
    int cont2 = 0;
    for (auto j: this->group) {
        // sumTable.push_back();
        // auto y = std::map<Polynomial, Polynomial> {j,j};
        // sumTable.insert({j, y});
        // sumTable.insert({j, std::map<Polynomial,Polynomial>()});
        // sumTable[j].insert(std::make_pair(j,j));
        // sumTable.insert(std::make_pair(j,std::map<Polynomial, Polynomial>(j,j)));
        for (auto i: this->group) {
            if (cont1 < cont2) {
                v.push_back(multiTable.at(i.getVal()).at(j.getVal()));
                cont1++;
            } else {
                if (i.getVal() == 18) {

                }
                auto y = multi(j, i);
                v.push_back(y);
                // if (y == Polynomial{{Monomial{1,0}}, this->base})
                //     this->revVector.push_back(y);
            }
            // sumTable[j] = {i, i};
            // sumTable[j].insert(std::make_pair(i,i));
            // auto elem = sum(j, i);
            // inSumTable(j, i, elem);
        }
        multiTable.push_back(v);
        v.clear();
        cont1 = 0;
        cont2++;
    }
}

// void Galois_field::constructRevVector() {

// }

Polynomial Galois_field::atSumTable(Polynomial first, Polynomial second) {
    // auto &a = this->sumTable.at(first);
    // return a.at(second);
    return sumTable.at(first.getVal()).at(second.getVal());
}

Polynomial Galois_field::atMultiTable(Polynomial first, Polynomial second) {
    // auto &a = this->multiTable.at(first);
    // return a.at(second);
    return multiTable.at(first.getVal()).at(second.getVal());
}

Polynomial Galois_field::atRevVector(Polynomial first) {
    return this->revVector.at(first.getVal()-2);
}
// void Galois_field::inSumTable(Polynomial first, Polynomial second, Polynomial elem) {
//     // auto &a = this->sumTable.at(first);
//     // a.insert({second, elem});

//     // this->sumTable[first][second] = elem;
// }

// void Galois_field::inMultiTable(Polynomial first, Polynomial second, Polynomial elem) {
//     // auto &a = this->multiTable.at(first);
//     // a.insert({second, elem});

//     // this->multiTable[first][second] = elem;
// }

Polynomial Galois_field::sum(Polynomial a, Polynomial b) {
    Polynomial c = a + b;
    // int s = c.getSize();
    // for (int i =0; i<c.getSize(); i++) {
    //     auto q = c.at(i);
    //     auto r = rem(q.getKoef(), this->base);
    //     if (r == 0)
    //         s--;
    //     q.setKoef(r);
    // }
    // Monomial* lst = new Monomial[size_t(s)];
    // int j = 0;
    // for (int i=0; i<s; i++) {
    //     if (c.at(i).getKoef() == 0) {
    //     } else {
    //         lst[j].setKoef(c.at(i).getKoef());
    //         lst[j].setPow(c.at(i).getPow());
    //         j++;
    //     }
    // }
    // return Polynomial{lst, s};
    return reduce(c);
}

Polynomial Galois_field::multi(Polynomial a, Polynomial b) {
    Polynomial c = a * b;
    if (reduce(c) == Polynomial{{Monomial{1,0}}, this->base}) {
        // this->revVector.push_back(b);
        this->revVector[b.getVal()-1] = a;
        this->revVector[a.getVal()-1] = b;
    }
    c = reduce(c);
    if (c.getSize() == 1 && c.at(0).getPow() >= this->power && this->xpows.size() == (c.at(0).getPow()-this->power+1) && c.at(0).getKoef() == 1) {
        return this->xpows.at(c.at(0).getPow()-this->power);
    }
    if (c.getVal() == pow(this->base, this->power)) {
        int s = 0;
        Monomial* lst = new Monomial[this->irrPolynomial.getSize()-1];
        for (int j=0; j<this->irrPolynomial.getSize()-1; j++) {
            auto aa1 = (-1)*this->irrPolynomial.at(j).getKoef();
            auto bb1 = this->irrPolynomial.at(j).getPow();
            // lst[s].setKoef((-1)*c.at(j).getKoef());
            // lst[s].setKoef(c.at(j).getPow());
            lst[s].setKoef(aa1);
            lst[s].setPow(bb1);
            s++;
        }
        c = Polynomial{lst, s, this->base};
        auto mem = reduce(c);
        this->xpows.push_back(mem);
        return mem;
    }
    if (c.getVal() >= pow(this->base, this->power) && c.getSize() == 1  && c.at(0).getKoef() == 1) {
        Polynomial mem = this->xpows.at(c.at(0).getPow()-this->power-1);
        mem = mem * Polynomial{{Monomial{1,1}}, this->base};
        this->xpows.push_back(mem);
        return mem;
    }
    if (c.getVal() > pow(this->base, this->power)) {
        // c = ;
        Polynomial d{{Monomial{0,0}}, this->base};
        Polynomial f{{Monomial{0,0}}, this->base};
        Polynomial z{{Monomial{0,0}}, this->base};
        for (int i=0; i<c.getSize(); i++) {
            if (c.at(i).getPow() >= this->power) {
                z = this->xpows.at(c.at(i).getPow()-this->power);
                // this->xpows.push_back(z);
            } else {
                z = Polynomial{{Monomial{1,c.at(i).getPow()}}, this->base};
            }
            f = Polynomial{{Monomial{c.at(i).getKoef(), 0}}, this->base} * z;
            d = d + f;
        }
        // auto test = reduce(d);
        // bool b1 = reduce(d) == Polynomial{{Monomial{1,0}}, this->base};
        // int test1 = a.getVal()-1;
        // int test2 = this->revVector.size();
        // bool b2 = test1 == test2;
        // if (reduce(d) == Polynomial{{Monomial{1,0}}, this->base} && a.getVal()-1 == this->revVector.size()) {
        //     this->revVector.push_back(a);
        // }
        // if (reduce(d) == Polynomial{{Monomial{1,0}}, this->base})
        //             this->revVector.push_back(b);
        if (reduce(d) == Polynomial{{Monomial{1,0}}, this->base})
            this->revVector[b.getVal()-1] = a;
        if (reduce(d) == Polynomial{{Monomial{1,0}}, this->base})
            this->revVector[a.getVal()-1] = b;
        return reduce(d);
    }
    return c;
}
// Galois_field::Galois_field(int y, int x = 2) {
//     for (int i=0; i<x; i++) {
//         this->pole.push_back(i);
//     }
//     Counter c{y,x};
//     for (int k=0; k<times(x,y); k++) {
//         this->group.push_back(Polynomial{c}); // 000 y = 3   0000 y = 4
//         ++c;
//     }
// }