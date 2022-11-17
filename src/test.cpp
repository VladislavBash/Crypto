#include "doctest.h"
#include "Affine_Cipher.h"
#include "Counter.h"
#include "Galois_field.h"
#include "Monomial.h"
#include "Polynomial.h"
#include "Recurrent_Affine_Cipher.h"
#include "Substitution.h"

TEST_CASE("CHECK_AFFINE_CIPHER") {
    // REQUIRE();
}

TEST_CASE("CHECK_COUNTER") {
    Counter a(5,2); //0000
    // int* lst = new int[4]{0,0,0,1};
    // REQUIRE(a.count[0] == 0); // 0001
    // REQUIRE(a.count[1] == 0); // 0001
    // REQUIRE(a.count[2] == 0); // 0001
    // //a++;
    // REQUIRE((++a).count[3] == 1); // 0001
    // // ++a;
    // REQUIRE((++a).count[3] == 0); // 0001
    // REQUIRE(a.count[2] == 1); // 0001
    REQUIRE(a.count[5-2] == 0);
    REQUIRE((++a).count[5-2] == 1);
    REQUIRE((++a).count[5-3] == 1);
    REQUIRE(a.count[5-2] == 0);
    REQUIRE((++a).count[5-3] == 1);
    REQUIRE(a.count[5-2] == 1);
    REQUIRE((++a).count[5-4] == 1);
    // for (int i = 5-2; i>=0; i--) {
    //     REQUIRE((++a).count[i] == 1);
    // }

    // REQUIRE(getRatio(2) == 31.599);
    // REQUIRE(getRatio(11) == 4.436);
    // REQUIRE(getRatio(22) == 3.792);
    // REQUIRE(getRatio(30) == 3.645);
    // REQUIRE(getRatio(60) == 3.460);
    // REQUIRE(getRatio(120) == 3.373);
    // REQUIRE(getRatio(12000000) == 3.373);
    // REQUIRE(getRatio(1147483646) == 3.290);
}

TEST_CASE("CHECK_GALOIS_FIELD") {
    // REQUIRE();
}

TEST_CASE("CHECK_MONOMIAL") {
    // REQUIRE();
}

TEST_CASE("CHECK_POLYNOMIAL") {
    // REQUIRE();
}

TEST_CASE("CHECK_RECCURENT_AFFINE_CIPHER") {
    // REQUIRE();
}

TEST_CASE("CHECK_SUBSTIOTUTION") {
    // REQUIRE();
}