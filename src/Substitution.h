#pragma once
#include <map>
#include <string>
class Substitution {
    std::map<char, char> key{};
    std::map<char, char> rkey{};
    std::string opText = "";
    std::string clText = "";
    public:
    Substitution(std::map<char, char> k) { setKey(k); }
    ~Substitution();
    void setKey(const std::map<char, char>& k);
    // std::string getKey() {}
    void setOpText(const std::string& text);
    void setClText(std::string text);
    // std::string getClText() {}
    void Encrypt();
    void Decrypt();
};