// int main {
//     const wchar_t CLASS_NAME[]  = L"Sample Window Class";

//     WNDCLASS wc = { };

//     wc.lpfnWndProc   = WindowProc;
//     wc.hInstance     = hInstance;
//     wc.lpszClassName = CLASS_NAME;

//     RegisterClass(&wc);

//     // Create the window.

//     HWND hwnd = CreateWindowEx(
//     0,                              // Optional window styles.
//     CLASS_NAME,                     // Window class
//     L"Learn to Program Windows",    // Window text
//     WS_OVERLAPPEDWINDOW,            // Window style

//     // Size and position
//     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

//     NULL,       // Parent window    
//     NULL,       // Menu
//     hInstance,  // Instance handle
//     NULL        // Additional application data
//     );

//     if (hwnd == NULL)
//     {
//        return 0;
//     }

//     ShowWindow(hwnd, nCmdShow);    
//     return 0;
// }
// #include <iostream>
// #include "crypto.hpp"
// int main() {
//     std::cout << "Hello wordl!" << std::endl;
//     return 0;
// }

// class Big {
//     int size = 0;
//     X* elem = nullptr;
//     Big(std::initializer_list<X> lst): size(lst.size()), elem(new X[size]) {
//         std::copy(lst.begin(), lst.end(), elem);
//     }
// };

// class X {
//     int koef = 1;
//     int pow = 0;
//     int size = 1;
//     X *next = nullptr;
//     public:
//     X() {}
//     X(std::string str) {
//         auto loc = this;
//         while (loc->next) {
//             loc = loc->next;
//         }
//     }
//     ~X() {}
//     auto getSize();
// };

// auto X::getSize() {
//     X* a;
//     int s = 1;
//     while (a->next)  {
//         a = a->next;
//         s++;
//     }
//     return s;
// }

// X operator* (X a, X b) {
//     for (int i=0; i<; i++) {
//         for (int j=0; j<;j++) {

//         }
//     }
// }

#include <iostream>
#include <string>
#include <map>
#include <vector>

// int getSizeInt(int k) {
//     int s = 0;
//     while (k != 0) {
//         k /= 10;
//         s++;
//     }
//     return s;
// }

class Counter {
  int p;
  int n;
  int size = n - 1;
//   static int* count[n-1] = {};
  static int* count;
  public:
  Counter(int x, int y = 2): n(x), p(y) { count = new int[x-1]; }
  int getSize() { return this->size; }
  int getVal(int i) { return this->count[i]; }
  int* operator++ (int) {
      int k = this->size - 1;
      this->count[k]++;
      while (this->count[k] == p) {
          this->count[k] = 0;
          k--;
          this->count[k]++;
      }
      return this->count;
  }
};

class  Galois_field { // Поле Галуа
    int p;
    int n;
    std::vector<int> pole;
    public:
    class Polynomial;
    private:
    std::vector<Polynomial> group;
    public:
    Galois_field(int y, int x = 2): p(x), n(y) {
        Monomial* lst = new Monomial[n-1];
        for (int i=0; i<p; i++) { pole.push_back(i); }
        for () { // группа поля галуа создание
            for () {
                group.push_back(Polynomial(0000));
            }
        };
    } // задаётся сначала p, потом n
    ~Galois_field() {}
    class Monomial { // Одночлен
    int koef = 0;
    int pow = 0;
    public:
    Monomial() {}
    Monomial(int k, int p): koef(k), pow(p) {}
    Monomial(std::string str) {
        if (str.find('x') == 0) { // 15*x^42
            this->koef = 1;
        } else {
            std::string k = str.substr(0, str.find('x')-1);
            this->koef = std::stoi(k); // k = '60'
        }
        if (str.find('x') == str.size()-1) { // 15*x^42
            this->pow = 1;
        } else {
            std::string p = str.substr(str.find('x')+2, str.size()-1);
            this->pow = std::stoi(p); // k = '60'
        }
    }
    ~Monomial() {}
    int getKoef() { return this->koef; }
    int getPow() { return this->pow; }
};

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
    Polynomial(Counter lst): size(lst.getSize()), elem(new Monomial[size]) { // Создаем 
        std::vector<Monomial> a;
        int k = 0;
        int l = 0;
        for (int i=0; i<this->size; i++) {
            k = lst.getVal(size-i);
            a.push_back(Monomial(k, i));
        }
        std::copy(a.begin(), a.end(), elem);
    }
    Polynomial(std::initializer_list<Monomial> lst): size(lst.size()), elem(new Monomial[size]) { // Создаем 
        std::copy(lst.begin(), lst.end(), elem);
    }
    Polynomial(Monomial* lst, int s): size(s), elem(lst) {}
    int getSize() const { return this->size; }
    Monomial at(int num) {
        return this->elem[num];
    }
};
};

Galois_field::Monomial operator* (Galois_field::Monomial a, Galois_field::Monomial b) {
    int k = a.getKoef() * b.getKoef();
    int p = a.getPow() + b.getPow();
    return Galois_field::Monomial(k, p);
}

Galois_field::Polynomial operator* (Galois_field::Polynomial a, Galois_field::Polynomial b) {
    Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()]; // утечка памяти будет: ФИКСИТЬ!
    int y = 0;
    for (int i=0; i<a.getSize(); i++) {
        for (int j=0; j<b.getSize();j++) {
            arr[y++] = a.at(i)*b.at(j);
        }
    }
    return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
}

Galois_field::Monomial operator+ (Galois_field::Monomial a, Galois_field::Monomial b) {
    // int k = a.getKoef() * b.getKoef();
    // int p = a.getPow() + b.getPow();
    // return Galois_field::Monomial(k, p);
}

Galois_field::Polynomial operator+ (Galois_field::Polynomial a, Galois_field::Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
}

Galois_field::Monomial operator- (Galois_field::Monomial a, Galois_field::Monomial b) {
    // int k = a.getKoef() * b.getKoef();
    // int p = a.getPow() + b.getPow();
    // return Galois_field::Monomial(k, p);
}

Galois_field::Polynomial operator- (Galois_field::Polynomial a, Galois_field::Polynomial b) {
    // Galois_field::Monomial* arr = new Galois_field::Monomial[a.getSize()*b.getSize()];
    // int y = 0;
    // for (int i=0; i<a.getSize(); i++) {
    //     for (int j=0; j<b.getSize();j++) {
    //         arr[y++] = a.at(i)*b.at(j);
    //     }
    // }
    // return Galois_field::Polynomial(arr, a.getSize()*b.getSize());
}

class Substitution {
    std::map<char, char> key{};
    std::map<char, char> rkey{};
    std::string opText = "";
    std::string clText = "";
    public:
    Substitution(std::map<char, char> k) { setKey(k); }
    ~Substitution() {}
    void setKey(const std::map<char, char>& k) {
        this->key = k;
        for (auto x: k) {
            this->rkey.insert(x.second, x.first);
        }
    }
    // std::string getKey() {}
    void setOpText(const std::string& text) {
        this->opText = text;
    }
    void setClText(std::string text) {
        this->clText = text;
    }
    // std::string getClText() {}
    void Encrypt() {
        this->clText = "";
        for (auto t: this->opText) {
            this->clText += this->key.at(t);
        }
    }
    void Decrypt() {
        this->opText = "";
        for (auto t: this->clText) {
            this->clText += this->rkey.at(t);
        }
    }
};

class Affine_Cipher {
    Galois_field a;
    Galois_field b;
    std::string opText = "";
    std::string clText = "";
    Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    void Encrypt() {
        this->clText = "";
        char y;
        for (auto x: this->opText) {
            x = ;// t в многочлен переводим
            y = a*x+b; // E(x)
            this->clText += y; // y переводим из многочлена в букву
        }
    }
    void Decrypt() {
        this->opText = "";
        char x;
        for (auto y: this->opText) {
            y = ;// t в многочлен переводим
            x = (y-b)*ra; // E(x)
            this->clText += x; // y переводим из многочлена в букву
        }
    }
    }
};

class Recurrent_Affine_Cipher {
    std::vector<Galois_field> a;
    std::vector<Galois_field> ra;
    std::vector<Galois_field> b;
    std::string opText = "";
    std::string clText = "";
    Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    void compNewA() {
        this->a.push_back( (this->a.at(a.size()-1)) * (this->a.at(a.size()-2)) );
    }
    void compNewB() {
        this->b.push_back( (this->b.at(b.size()-1)) + (this->b.at(b.size()-2)) );
    }
    void Encrypt() {
        this->clText = "";
        char y;
        int i = 0;
        for (auto x: this->opText) {
            x = ;// t в многочлен переводим
            y = a.at(i)*x+b.at(i); // E(x)
            i++;
            this->clText += y; // y переводим из многочлена в букву
        }
    }
    void Decrypt() {
        this->opText = "";
        char x;
        int i = 0;
        for (auto y: this->opText) {
            y = ;// t в многочлен переводим
            x = (y-b.at(i))*ra.at(i); // E(x)
            i++;
            this->clText += x; // y переводим из многочлена в букву
        }
    }
};