#include "Counter.hpp"
#include <vector>

std::vector<int> Counter::getCount() { return this->count; }
int Counter::getSize() { return this->size; }
int Counter::getVal(int i) { return this->count[size_t(i)]; }
int Counter::maxInc() { return int(pow(this->n, this->p)-1); }
// Counter& Counter::operator++() {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == this->p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return *this;
// }
// int* Counter::operator++(int) {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return this->count;
// }

// int*& Counter::operator++() {
//     int k = this->size - 1;
//     this->count[k]++;
//     while (this->count[k] == p) {
//         this->count[k] = 0;
//         k--;
//         this->count[k]++;
//     }
//     return this->count;
// }