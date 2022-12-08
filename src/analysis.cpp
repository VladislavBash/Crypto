#include <iostream>
#include <vector>
#include <string> 
#include <math.h>
#include <map> 
#include "Galois_field.hpp"
#include "Polynomial.hpp"
#include "Monomial.hpp"
#include "Recurrent_Affine_Cipher.hpp"
#define MOD 27
#define BASE 3
#define SIZE 3

int fib(int n) {
    auto s = sqrt(5);
    auto a = pow((1+s)/2, n);
    auto b = pow((1-s)/2, n);
    return int((a - b)/s);
}

std::map<std::string, int> count(std::string str) {
    std::string y = "";
    std::map<std::string, int> mp = {{"A",0}, {"B",0}, {"C",0}, {"D",0}, {"E",0}, {"F",0}, {"G",0}, {"H",0}, {"I",0}, {"J",0},
        {"K",0}, {"L",0}, {"M",0}, {"N",0}, {"O",0}, {"P",0}, {"Q",0}, {"R",0}, {"S",0}, {"T",0},
        {"U",0}, {"V",0}, {"W",0}, {"X",0}, {"Y",0}, {"Z",0}, {" ",0}};
        for (auto x: str) {
            y = x;
            mp.at(y) += 1;
        }
    return mp;
}

double get_IC(std::string str) {
    double IC = 0;
    int N = int(str.size());
    auto arr = count(str);
    int n = 0;
    for (auto x: arr) {
        n = x.second;
        IC += (n*(n-1))/(N*(N-1));
    }
    return IC;
}

// void get_a(std::vector<Polynomial>& a1, std::vector<Polynomial>& a2, Galois_field g) {
//     int k = 0;
//     int base = 3;
//     Polynomial g_a{{Monomial{0,0}}, base};
//     for () {
//         switch (k)
//         {
//         case 0:
//             g_a = g.multiGroup.at();
//             a1.push_back(g_a);
//             a2.push_back(Polynomial{{Monomial{0,0}}, base});
//             k++;
//             break;
//         case 1:
//             g_a = g.multiGroup.at();
//             a1.push_back(Polynomial{{Monomial{0,0}}, base});
//             a2.push_back(g_a);
//             k++;
//             break;
//         default:
//             // g_a = a.at(k-1) * a.at(k-2);
//             g_a = g.atMultiTable(a.at(k-1), a.at(k-2));
//             // g_a = reduce(g_a);
//             // g_b = b.at(k-1) + b.at(k-2);
//             // g_b = reduce(g_b);
//             a.push_back(g_a);
//             k++;
//             break;
//         }
//         a1.push_back();
//         a2.push_back();
//     }
// }

// void get_alphas(std::string clText, std::string word, std::vector<int>& a1, std::vector<int>& a2, Galois_field g) {
//     int base = 3;
//     int size = 3;
//     std::vector<Polynomial> aa1;
//     std::vector<Polynomial> aa2;
//     // Polynomial aa1{{Monomial{0,0}}, base};
//     // Polynomial aa2{{Monomial{0,0}}, base};
//     // auto aac2 = Counter(size, base);
//     // auto aac1 = Counter(size, base);
//     // Polynomial g_x{{Monomial{0,0}}, base};
//     Polynomial f1{{Monomial{0,0}}, base};
//     Polynomial f2{{Monomial{0,0}}, base};
//     Polynomial f3{{Monomial{0,0}}, base};
//     Polynomial y{{Monomial{0,0}}, base};
//     get_a(aa1, aa2, g);
//     for (int i =0; i< ; i++) {
//         // aa2 = Polynomial{aac2, base};
//         for (int j =0; j< ; j++) {
//             // aa1 = Polynomial{aac1, base};
//             f3 = g.atMultiTable(aa1.at(i), aa2.at(j));
//             f2 = g.atMultiTable(aa1.at(i), aa2.at(j));
//             f1 = g.atMultiTable(aa1.at(i), aa2.at(j));

//             f3 = g.atMultiTable(f3, g.group.at(word));
//             f2 = g.atMultiTable(f2, g.group.at(word));
//             f1 = g.atMultiTable(f1, g.group.at(word));
//             y = clText.at() - clText.at() - clText.at();
//             if ( ((f3-f2-f1).getVal() % MOD) == (y.getVal() % MOD) ) {
//                 a1.push_back(.getVal());
//                 a2.push_back(.getVal());
//             }
//             // ++aac1;
//         }
//         // ++aac2;
//     }
// }

// void get_bettas(const std::vector<int>& a1, const std::vector<int>& a2, std::vector<int>& b1, std::vector<int>& b2) {
//     bb1;
//     bb2;
// for (int i=0; i < a1.size(); i++) {
//     bb1 = ;
//     bb2 = ;
//     b1.push_back(bb1);
//     b2.push_back(bb2);
// }
// }

void get_bettas(Polynomial& b1, Polynomial& b2, Polynomial y1, Polynomial y2, Polynomial f1, Polynomial f2, int i) {
    Polynomial n{{Monomial{0,0}}, BASE};
    auto t = Polynomial{{Monomial{fib(i+1),0}}, BASE};
    auto tt = Polynomial{{Monomial{fib(i-1),0}}, BASE};
    auto  r = Polynomial{{Monomial{fib(i),0}}, BASE};
    auto q = (y2+f2)*r;
    q = q * Polynomial{{Monomial{-1,0}}, BASE};
    auto qq = (y1+f1)*r;
    qq = qq * Polynomial{{Monomial{-1,0}}, BASE};
    if (i % 2 == 0) {
        n = {{Monomial{1,0}}, BASE};
    } else {
        n = {{Monomial{-1,0}}, BASE};
    }
    // if (i == 0) {
    //     b1 = y1+f1;
    //     b2 = y2+f2;
    //  } else {
    //     b1 = ((y1+f1)*t + q) * Polynomial{{Monomial{pow(-1, i),0}}, BASE};
    //     b2 = (tt*(y2+f2) + qq) * Polynomial{{Monomial{pow(-1, i),0}}, BASE};
    // }
    b1 = ((y1+f1)*t + q) * n;
    b2 = (tt*(y2+f2) + qq) * n;
    b1 = reduce(b1);
    b2 = reduce(b2);
}

// void get_bettas(Polynomial& b1, Polynomial& b2, Polynomial y1, Polynomial y2, Polynomial f1, Polynomial f2, int i) {
//     auto t = Polynomial{{Monomial{fib(i+1),0}}, BASE};
//     auto tt = Polynomial{{Monomial{fib(i-1),0}}, BASE};
//     auto  r = Polynomial{{Monomial{fib(i),0}}, BASE};
//     auto q = (y2+f2)*r;
//     q = q * Polynomial{{Monomial{-1,0}}, BASE};
//     auto qq = (y1+f1)*r;
//     qq = qq * Polynomial{{Monomial{-1,0}}, BASE};
//     if (i == 0) {
//         b1 = y1+f1;
//         b2 = y2+f2;
//      } else {
//         b1 = ((y1+f1)*t + q) * Polynomial{{Monomial{1/(fib(i-1)*fib(i+1)-fib(i)*fib(i)), 0}}, BASE};
//         b2 = (tt*(y2+f2) + qq) * Polynomial{{Monomial{1/(fib(i-1)*fib(i+1)-fib(i)*fib(i)), 0}}, BASE};
//     }
//     b1 = reduce(b1);
//     b2 = reduce(b2);
// }


void get_alphas(const std::string& clText, const std::string& word, std::vector<std::vector<int>>& keys, Galois_field& g, int pos) {
    static const std::string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // std::string sstr = "";
    static std::vector<int> keys_lst;
    std::map<std::vector<int>, int> lst;
    int fordeletevar = 0;
    std::string help_var = "";
    // std::vector<int> vec;
    std::vector<int> addit_list;

    int showvar1 = 0;
    int showvar2 = 0;
    // std::map<std::vector<int>, int> lst;
    // int start_pos = num;
    Polynomial b1{{Monomial{0,0}}, BASE};
    Polynomial b2{{Monomial{0,0}}, BASE};
    Polynomial f1{{Monomial{0,0}}, BASE};
    Polynomial f2{{Monomial{0,0}}, BASE};
    Polynomial f3{{Monomial{0,0}}, BASE};
    Polynomial a1{{Monomial{0,0}}, BASE};
    Polynomial a2{{Monomial{0,0}}, BASE};
    Polynomial a3{{Monomial{0,0}}, BASE};
    Polynomial y{{Monomial{0,0}}, BASE};
    Polynomial y3{{Monomial{0,0}}, BASE};
    Polynomial y2{{Monomial{0,0}}, BASE};
    Polynomial y1{{Monomial{0,0}}, BASE};
    Counter c1{SIZE, BASE};
    ++c1;
    Counter c2{SIZE, BASE};
    ++c2;
    Counter c_start = Counter{SIZE, BASE};
    ++c_start;
    
    // start_pos = k + num;
    for (int i=0; i < MOD-2; i++) { //  i=start_pos
        for (int j=0; j < MOD-2; j++) {
            // keys_lst.push_back(a1.getVal());
            // keys_lst.push_back(a2.getVal());
            for (int k=0; k < int(word.size())-2; k++) { // word.size
                // if (pos == 1 && keys_lst.at(0) == 2 && keys_lst.at(1) == 3) {
                //     fordeletevar = 0;
                // }
                if (k == 0) {
                    // a1 = g.atMultiTable(Polynomial{c1, BASE},
                    // Polynomial{c_start, BASE}); // aa a2 =
                    // g.atMultiTable(Polynomial{c_start, BASE}, Polynomial{c2,
                    // BASE}); // aa
                    a1 = g.atMultiTable(Polynomial{c2, BASE}, Polynomial{c_start, BASE}); // aa
                    a2 = g.atMultiTable(Polynomial{c_start, BASE},  Polynomial{c1, BASE}); // aa
                    a3 = g.atMultiTable(Polynomial{c1, BASE}, Polynomial{c2, BASE}); // aa
                    keys_lst.push_back(a1.getVal());
                    keys_lst.push_back(a2.getVal());
                }
                else {
                        a1 = a2;                     // aa
                        a2 = a3;                     // aa
                        a3 = g.atMultiTable(a1, a2); // aa
                    if (k == 0) {
                        a1 = {Counter{SIZE, BASE}+keys_lst.at(0), BASE};            // aa
                        a2 = {Counter{SIZE, BASE}+keys_lst.at(1), BASE};                     // aa
                        a3 = g.atMultiTable(a1, a2); // aa
                    } else {
                        a1 = a2;                     // aa
                        a2 = a3;                     // aa
                        a3 = g.atMultiTable(a1, a2); // aa
                    }
                }
                showvar1 = a1.getVal();
                showvar2 = a2.getVal();
                if (k ==0 && pos == 1 && showvar1 == 3 && showvar2 == 6) {
                    fordeletevar = 0;
                }
                help_var = word.at(size_t(k));
                f1 = g.atMultiTable(a1, g.group.at(alph.find(help_var))); // aax
                help_var = word.at(size_t(k + 1));
                f2 = g.atMultiTable(a2, g.group.at(alph.find(help_var))); // aax
                help_var = word.at(size_t(k + 2));
                f3 = g.atMultiTable(a3, g.group.at(alph.find(help_var))); // aax
                // y1 = Polynomial{Counter{SIZE,
                // BASE}+alph.find(clText.at(size_t(start_pos))), BASE}; y2 =
                // Polynomial{Counter{SIZE,
                // BASE}+alph.find(clText.at(size_t(start_pos+1))), BASE}; y3 =
                // Polynomial{Counter{SIZE,
                // BASE}+alph.find(clText.at(size_t(start_pos+2))), BASE};
                y1 = Polynomial{Counter{SIZE, BASE} + alph.find(clText.at(size_t(k + pos))), BASE};
                y2 = Polynomial{Counter{SIZE, BASE} + alph.find(clText.at(size_t(k + pos + 1))), BASE};
                y3 = Polynomial{Counter{SIZE, BASE} + alph.find(clText.at(size_t(k + pos + 2))), BASE};
                y1 = y1 * Polynomial{{Monomial{-1, 0}}, BASE};
                y2 = y2 * Polynomial{{Monomial{-1, 0}}, BASE};
                y = y3 + y2 + y1;
                f1 = f1 * Polynomial{{Monomial{-1, 0}}, BASE};
                f2 = f2 * Polynomial{{Monomial{-1, 0}}, BASE};
                auto red_f = (reduce(f3 + f2 + f1)).getVal();
                auto red_y = reduce(y).getVal();
                if (a1.getVal() == 3 && a2.getVal() == 6) {
                    fordeletevar = 1;
                }
                if ((red_f % MOD) == (red_y % MOD)) {
                    // vec.push_back(a1.getVal());
                    // vec.push_back(a2.getVal());
                    // keys.push_back(vec);
                    // f1 = f1 * Polynomial{{Monomial{-1,0}}, BASE};
                    // f2 = f2 * Polynomial{{Monomial{-1,0}}, BASE};
                    y1 = y1 * Polynomial{{Monomial{-1, 0}}, BASE};
                    y2 = y2 * Polynomial{{Monomial{-1, 0}}, BASE};
                    if (i == 1 && j == 2) {
                        fordeletevar = 1;
                    }
                    get_bettas(b1, b2, y1, y2, f1, f2, pos);
                    // addit_list.push_back((a1.getVal(), a2.getVal(),
                    // b1.getVal(), b2.getVal()));
                    addit_list.push_back(keys_lst.at(0));
                    addit_list.push_back(keys_lst.at(1));
                    // addit_list.push_back();
                    // addit_list.push_back();
                    addit_list.push_back(b1.getVal());
                    addit_list.push_back(b2.getVal());
                    lst[addit_list] += 1;
                    addit_list.clear();
                    // vec.clear();
                }
                // ++c1;
            }
            ++c1;
            keys_lst.clear();
        }
        c1 = {SIZE, BASE};
        ++c1;
        ++c2;
        // c1 = {SIZE, BASE};
        // ++c1;
        // ++c2;
    }
    
    // c1 = {SIZE, BASE};
    // c2 = {SIZE, BASE};
    // ++c1;
    // ++c2;
    // lst[] += 1;
    // }
    for (auto x: lst) {
        if (x.second ==  int(word.size())-2) {
            // auto r = x.first;
            // get_bettas();
            // r.push_back(b1);
            // r.push_back(b2);
            keys.push_back(x.first);
        }
    }
}

// void get_bettas(std::vector<std::vector<int>> keys) {
//     for () { // word.size

//     }
// }

// std::vector<std::vector<int>> get_keys(std::string clText, std::string word, Galois_field g, int i) {
//     // std::vector<std::vector<int>> keys;
//     // get_alphas(clText, word, keys, g, i);
//     // get_bettas(keys);
//     // return keys;
//     return 1;
// }

std::string analysis(std::string clText, std::string word) {
    Galois_field g{3,3};
    const auto IC = 0.0667; // for eng
    // std::string clText = "jdnfjfnfdjdnfjdfn";
    // std::string word = "help";
    std::string text = "";
    for (int i=0; i < int(clText.size()-word.size()+1); i++) {
    double buf = 1000;
    std::string str = "";
    std::vector<int> a1;
    std::vector<int> a2;
    std::vector<int> b1;
    std::vector<int> b2;
    std::vector<std::vector<int>> keys;

    // keys = get_keys(clText, word, g, i);
    // get_alphas(clText, word, keys, g, num);
    // get_alphas(clText, word, a1 ,a2, g);
    // get_bettas();
    // get_alphas(clText, word, a1 ,a2, g);
    // get_bettas(a1 ,a2, b1, b2);

    // for (int j=0; j<int(keys.size()); j++) {
    get_alphas(clText, word, keys, g, i); // for one certain position
    // if (keys.size() != 0) {
    //     buf = 121;
    // }
    for (int j=0; j<int(keys.size()); j++) {
        
    // }
    // get_alphas(clText, word, keys, g, j);
    // str = Recurrent_Affine_Cipher::Decrypt(clText, a1.at(j), a2.at(j), b1.at(j), b2.at(j), "eng");
    str = Recurrent_Affine_Cipher::Decrypt(clText, keys.at(j).at(0), keys.at(j).at(1), keys.at(j).at(2), keys.at(j).at(3), "eng");

    if (abs(get_IC(str) - IC) < buf) {
        buf = abs(get_IC(str) - IC);
        text = str;
    }
    if (abs(get_IC(str) - IC) == 0.0001) {
        text = str;
        break;
    }
    }
    }

    std::cout << text << std::endl;
    return text;
}
