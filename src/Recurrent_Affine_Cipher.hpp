#pragma once
#include <vector>
#include <string>
#include "Substitution_Cipher.hpp"
#include "Galois_field.hpp"
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