# cmake_minimum_required(VERSION 3.0.0)
# project(cipher VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(cipher Counter.cpp main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

cmake_minimum_required(VERSION 3.10.0)
add_executable(Monte-Carlo-test Counter.h test.cpp)
target_link_libraries(Monte-Carlo-test PUBLIC doctest default)
add_test(NAME Monte-Carlo-test COMMAND Monte-Carlo-test)
add_custom_target(cloud-test COMMAND Monte-Carlo-test)

add_executable(Monte-Carlo Counter.h main.cpp)
target_link_libraries(Monte-Carlo PUBLIC default)