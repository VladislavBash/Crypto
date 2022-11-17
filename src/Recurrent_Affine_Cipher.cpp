#include <vector>
#include <string>
#include "Substitution.h"
#include "Galois_field.h"
#include "Recurrent_Affine_Cipher.h"

    // void Recurrent_Affine_Cipher::compNewA() {
    //     this->a.push_back( (this->a.at(a.size()-1)) * (this->a.at(a.size()-2)) );
    // }
    // void Recurrent_Affine_Cipher::compNewB() {
    //     this->b.push_back( (this->b.at(b.size()-1)) + (this->b.at(b.size()-2)) );
    // }
    // void Recurrent_Affine_Cipher::Encrypt() {
    //     this->clText = "";
    //     char y;
    //     int i = 0;
    //     for (auto x: this->opText) {
    //         x = ;// t в многочлен переводим
    //         y = a.at(i)*x+b.at(i); // E(x)
    //         i++;
    //         this->clText += y; // y переводим из многочлена в букву
    //     }
    // }
    // void Recurrent_Affine_Cipher::Decrypt() {
    //     this->opText = "";
    //     char x;
    //     int i = 0;
    //     for (auto y: this->opText) {
    //         y = ;// t в многочлен переводим
    //         x = (y-b.at(i))*ra.at(i); // E(x)
    //         i++;
    //         this->clText += x; // y переводим из многочлена в букву
    //     }
    // }