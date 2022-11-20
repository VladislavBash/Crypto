#include <vector>
#include <map>
#include "Galois_field.hpp"
#include "Polynomial.hpp"


// int times(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += pow(x, z);
//     }
//     return (x-1)*s;
// }

Galois_field::Galois_field(int y, int x = 2): base(x), pow(y) { // base pow
    constructPole();
    constructGroup();
    constructMultiGroup();
    constructSumTable();
    constructMultiTable();
}

void Galois_field::constructPole() {
    for (int i=0; i<this->base; i++) {
        this->pole.push_back(i);
    }
}

void Galois_field::constructGroup() {
    Counter c{this->pow,this->base};
    for (int k=0; k<c.maxInc(); k++) {
        Counter c1 = c;
        this->group.push_back(Polynomial{c1}); // 000 y = 3   0000 y = 4
        ++c;
    }
}

// void Galois_field::constructIrrPolynomial() {
//     Counter c{this->pow, this->base};
//     c + 1;
// }

void Galois_field::constructMultiGroup() {
    this->multiGroup = this->group;
    this->multiGroup.erase(this->multiGroup.begin());
}

void Galois_field::constructSumTable() {
    for (auto j: this->group) {
        // auto y = std::map<Polynomial, Polynomial> {j,j};
        // sumTable.insert({j, y});
        sumTable.insert({j, std::map<Polynomial,Polynomial>()});
        sumTable[j].insert(std::make_pair(j,j));
        // sumTable.insert(std::make_pair(j,std::map<Polynomial, Polynomial>(j,j)));
        for (auto i: this->group) {
            // sumTable[j] = {i, i};
            // sumTable[j].insert(std::make_pair(i,i));
            // auto elem = sum(j, i);
            // inSumTable(j, i, elem);
        }
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
}

// void Galois_field::constructRevVector() {

// }

Polynomial Galois_field::atSumTable(Polynomial first, Polynomial second) {
    // auto &a = this->sumTable.at(first);
    // return a.at(second);
}

Polynomial Galois_field::atMultiTable(Polynomial first, Polynomial second) {
    // auto &a = this->multiTable.at(first);
    // return a.at(second);
}

void Galois_field::inSumTable(Polynomial first, Polynomial second, Polynomial elem) {
    // auto &a = this->sumTable.at(first);
    // a.insert({second, elem});

    // this->sumTable[first][second] = elem;
}

void Galois_field::inMultiTable(Polynomial first, Polynomial second, Polynomial elem) {
    // auto &a = this->multiTable.at(first);
    // a.insert({second, elem});

    // this->multiTable[first][second] = elem;
}

// Polynomial Galois_field::sum(Polynomial a, Polynomial b) {

// }

// Polynomial Galois_field::multi(Polynomial a, Polynomial b) {

// }
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