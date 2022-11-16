#include "doctest.h"
#include "crypto.hpp"
// #include <math.h>
// #include <iomanip>
// #define pi 3.1415926535897932
// #define e  2.7182818284590452

// bool compare(double const &a, double const &b, int const &sampling) { // необходимо для double и float
//     if (std::ceil(a*sampling)/sampling == std::ceil(b*sampling)/sampling) {
//         return true;
//     }
//     return false;
// }

TEST_CASE("CHECK_COUNTER") {
    Counter a(5,2); //0000
    int* lst = new int[4]{0,0,0,1};
    REQUIRE(a++ == lst); // 0001
    // REQUIRE(getRatio(2) == 31.599);
    // REQUIRE(getRatio(11) == 4.436);
    // REQUIRE(getRatio(22) == 3.792);
    // REQUIRE(getRatio(30) == 3.645);
    // REQUIRE(getRatio(60) == 3.460);
    // REQUIRE(getRatio(120) == 3.373);
    // REQUIRE(getRatio(12000000) == 3.373);
    // REQUIRE(getRatio(1147483646) == 3.290);
}