#include <vector>
#include <math.h>
#include "Polynomial.hpp"
#include "Galois_field.hpp"

// int times(int x, int y) {
//     int s = 0;
//     for (int z=0; z<y-1; z++) {
//         s += pow(x, z);
//     }
//     return (x-1)*s;
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