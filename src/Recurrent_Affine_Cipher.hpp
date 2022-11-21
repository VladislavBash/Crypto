#pragma once
// #include <vector>
#include <string>
class Recurrent_Affine_Cipher {
    // std::vector<Galois_field> a;
    // std::vector<Galois_field> ra;
    // std::vector<Galois_field> b;
    // std::string opText = "";
    // std::string clText = "";
    // // Substitution cont{}; // ключи {A}: {1+x+x^2}
    // public:
    // void compNewA();
    // void compNewB();
    // void Encrypt();
    // void Decrypt();
    public:
    static std::string Encrypt(std::string opText, int a1, int a2, int b1, int b2, std::string lang);
    static std::string Decrypt(std::string clText, int a1, int a2, int b1, int b2, std::string lang);
};