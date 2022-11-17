#include <string>
#include "Substitution.h"
#include "Galois_field.h"
#include "Affine_Cipher.h"

    // void Affine_Cipher::Encrypt() {
    //     this->clText = "";
    //     char y;
    //     for (auto x: this->opText) {
    //         x = ;// t в многочлен переводим
    //         y = a*x+b; // E(x)
    //         this->clText += y; // y переводим из многочлена в букву
    //     }
    // }
    // void Affine_Cipher::Decrypt() {
    //     this->opText = "";
    //     char x;
    //     for (auto y: this->opText) {
    //         y = ;// t в многочлен переводим
    //         x = (y-b)*ra; // E(x)
    //         this->clText += x; // y переводим из многочлена в букву
    //     }
    // }