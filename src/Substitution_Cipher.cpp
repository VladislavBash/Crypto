#include <map>
#include <string>
#include <locale>
#include "Substitution_Cipher.hpp"
#include <algorithm>

std::string toUpperCase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

void Substitution_Cipher::setKeys(std::map<char, char> k) {
    this->key = k;
    for (auto x: k) {
        this->rkey.insert({x.second, x.first});
    }
}

std::map<char, char> Substitution_Cipher::getKey() { return this->key; }
std::map<char, char> Substitution_Cipher::getRkey() { return this->rkey; }

void Substitution_Cipher::setOpText(std::string text) {
    this->opText = toUpperCase(text);
    // this->opText = text;
}
void Substitution_Cipher::setClText(std::string text) {
    this->clText = toUpperCase(text);
    // this->clText = text;
}
// std::string getClText() {}
std::string Substitution_Cipher::Encrypt() {
    this->clText = "";
    for (auto t: this->opText) {
        this->clText += this->key.at(t);
    }
    return this->clText;
}
std::string Substitution_Cipher::Decrypt() {
    this->opText = "";
    for (auto t: this->clText) {
        this->opText += this->rkey.at(t);
    }
    return this->opText;
}