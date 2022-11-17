#pragma once
#include <string>
#include "Substitution_Cipher.hpp"
#include "Galois_field.hpp"
class Affine_Cipher {
    Galois_field a;
    Galois_field b;
    std::string opText = "";
    std::string clText = "";
    // Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    void Encrypt();
    void Decrypt();
};