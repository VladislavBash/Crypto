#include <map>
#include <string>
#include "Substitution.h"

void Substitution::setKey(const std::map<char, char>& k) {
    this->key = k;
    for (auto x: k) {
        this->rkey.insert(x.second, x.first);
    }
}
// std::string getKey() {}
void Substitution::setOpText(const std::string& text) {
    this->opText = text;
}
void Substitution::setClText(std::string text) {
    this->clText = text;
}
// std::string getClText() {}
void Substitution::Encrypt() {
    this->clText = "";
    for (auto t: this->opText) {
        this->clText += this->key.at(t);
    }
}
void Substitution::Decrypt() {
    this->opText = "";
    for (auto t: this->clText) {
        this->clText += this->rkey.at(t);
    }
}