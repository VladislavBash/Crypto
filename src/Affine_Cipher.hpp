#pragma once
#include <string>
#include <vector>
// #include "Substitution_Cipher.hpp"
// #include "Galois_field.hpp"
class Affine_Cipher {
    // Substitution cont{}; // ключи {A}: {1+x+x^2}
    public:
    static std::string Encrypt(std::string opText, int a, int b, std::string lang, int n = 0);
    static std::string Decrypt(std::string clText, int a, int b, std::string lang, int n = 0);
};

// extern std::vector<int> bit_trans(std::string text, std::string lang, int n);