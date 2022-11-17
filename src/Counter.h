#pragma once
class Counter { // n p
  public:
  int p;
  int n;
  int size = n - 1;
//   static int* count[n-1] = {};
  // static int* count;
  int* count = nullptr;
  public:
  Counter(int x, int y = 2): p(y), n(x) { count = new int[static_cast<unsigned long long>(x-1)]{0}; }
  ~Counter() { delete[] count; }
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
        this->count[k]++;
    }
    return *this;
}
};