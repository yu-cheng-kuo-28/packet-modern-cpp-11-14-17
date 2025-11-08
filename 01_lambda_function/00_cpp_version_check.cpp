/*
$ g++ -std=c++20 00_cpp_version_check.cpp -o 00_cpp_version_check

$ ./00_cpp_version_check
__cplusplus value: 202002
C++11 support: YES
C++14 support: YES
C++17 support: YES
C++20 support: YES
*/

#include <iostream>

int main() {
    std::cout << "__cplusplus value: " << __cplusplus << std::endl;
    
#if __cplusplus >= 201103L
    std::cout << "C++11 support: YES" << std::endl;
#else
    std::cout << "C++11 support: NO" << std::endl;
#endif

#if __cplusplus >= 201402L
    std::cout << "C++14 support: YES" << std::endl;
#else
    std::cout << "C++14 support: NO" << std::endl;
#endif

#if __cplusplus >= 201703L
    std::cout << "C++17 support: YES" << std::endl;
#else
    std::cout << "C++17 support: NO" << std::endl;
#endif

#if __cplusplus >= 202002L
    std::cout << "C++20 support: YES" << std::endl;
#else
    std::cout << "C++20 support: NO" << std::endl;
#endif

    return 0;
}