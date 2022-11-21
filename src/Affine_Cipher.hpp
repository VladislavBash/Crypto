#pragma once
#include <string>
// #include "Substitution_Cipher.hpp"
// #include "Galois_field.hpp"
class Affine_Cipher {
    // Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    static std::string Encrypt(std::string opText, int a, int b, std::string lang);
    static std::string Decrypt(std::string clText, int a, int b, std::string lang);
};