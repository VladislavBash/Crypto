#include <map>
#include <string>
#include <locale>
#include <stdexcept>
#include "Substitution_Cipher.hpp"
#include "toUpperCase.hpp"

void Substitution_Cipher::setKeys(std::map<char, char> k) {
    this->key = k;
    for (auto x: k) {
        this->rkey.insert({x.second, x.first});
    }
}

void Substitution_Cipher::setKeys(std::string k) {
    // this->key = k;
    // for (auto x: k) {
    //     this->rkey.insert({x.second, x.first});
    // }
    if (k.size() != 26)
        throw std::invalid_argument("key`s length isn`t 26");
    static const std::string text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::map<char,char> m;
    std::map<char,char> rm;
    k = toUpperCase(k);
    for (int i =0 ; i<k.size(); i++) {
        m.insert({text[i], k[i]});
        rm.insert({k[i], text[i]});
    }
    this->key = m;
    this->rkey = rm;
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