#pragma once
#include <map>
#include <string>
class Substitution_Cipher {
    std::map<char, char> key{};
    std::map<char, char> rkey{};
    std::string opText = "";
    std::string clText = "";
    public:
    Substitution_Cipher(std::map<char, char> k) { setKeys(k); }
    ~Substitution_Cipher() {}
    void setKeys(std::map<char, char> k);
    std::map<char, char> getKey();
    std::map<char, char> getRkey();
    void setOpText(std::string text);
    void setClText(std::string text);
    // std::string getClText() {}
    std::string Encrypt();
    std::string Decrypt();
};