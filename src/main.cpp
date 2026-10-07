#include <cstdlib>
#include <iostream>
#include <string>

#include "cpp_starter/greet.hpp"

int main(int argc, char** argv) {
    const std::string name = (argc > 1) ? argv[1] : "世界";
    std::cout << cpp_starter::greet(name) << '\n';
    return EXIT_SUCCESS;
}
