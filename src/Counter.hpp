#pragma once

class ERR {};

class Counter { // pow koefs
  public:
  int p;
  int n;
  int size = n;
//   static int* count[n-1] = {};
  // static int* count;
  int* count = nullptr;
  public:
  // Counter(int x, int y = 2): p(y), n(x) { count = new int[static_cast<size_t>(x-1)]{0}; }
  Counter(int x, int y = 2): p(y), n(x) {
    count = new int[static_cast<size_t>(x)];
    for (int u=0; u<x; u++) {
      count[u] = u+1;}
    }
  ~Counter() { delete[] count; }
  int* getCount();
  int getSize();
  int getVal(int i);
  // int* operator++(int);
  // Counter& operator++();
  Counter& operator++() {
    int k = this->size - 1;
    this->count[k]++;
    while (this->count[k] == this->p) {
        this->count[k] = 0;
        k--;
        if (k == -1)
          throw ERR();
        this->count[k]++;
    }
    return *this;
}
};