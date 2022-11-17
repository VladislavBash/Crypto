#pragma once
#include <vector>
#include <string>
#include "Substitution.h"
#include "Galois_field.h"
class Recurrent_Affine_Cipher {
    std::vector<Galois_field> a;
    std::vector<Galois_field> ra;
    std::vector<Galois_field> b;
    std::string opText = "";
    std::string clText = "";
    // Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    void compNewA();
    void compNewB();
    void Encrypt();
    void Decrypt();
};