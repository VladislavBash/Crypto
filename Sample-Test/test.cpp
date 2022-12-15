#include "pch.h"
/*#include <string>
#include <clocale>
#include <iostream>
#include <bitset>
#include "../Affine_Cipher.hpp"
#include "../Counter.hpp"
#include "../Galois_field.hpp"
#include "../Monomial.hpp"
#include "../Polynomial.hpp"
#include "../Recurrent_Affine_Cipher.hpp"
#include "../Substitution_Cipher.hpp"*/
#include "../src/Translate.hpp"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestCaseNameTRANSLATE, TestCaseNameTRANSLATE) {
    std::string o = "kUKUSHKA";
    std::string q = "k";
    EXPECT_TRUE(o.at(0) == q.at(0));
    EXPECT_TRUE(translate("A", "eng") == 0);
    EXPECT_TRUE(translate("V", "eng") == 21);
}
