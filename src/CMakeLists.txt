# cmake_minimum_required(VERSION 3.0.0)
# project(cipher VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(cipher Counter.cpp main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

cmake_minimum_required(VERSION 3.10.0)
add_executable(Cryptography-test Counter.h test.cpp)
target_link_libraries(Cryptography-test PUBLIC doctest default)
add_test(NAME Cryptography-test COMMAND Cryptography-test)
add_custom_target(cloud-test COMMAND Cryptography-test)

add_executable(Cryptography Counter.h main.cpp)
target_link_libraries(Cryptography PUBLIC default)