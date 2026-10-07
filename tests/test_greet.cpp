// 一个不依赖任何第三方框架的最小测试，直接由 ctest 驱动。
// 这样项目不需要联网拉 GoogleTest 就能跑起来。

#include <cstdlib>
#include <iostream>
#include <string>

#include "cpp_starter/greet.hpp"

namespace {

int failures = 0;

void check(bool condition, const std::string& what) {
    if (condition) {
        std::cout << "[PASS] " << what << '\n';
    } else {
        std::cout << "[FAIL] " << what << '\n';
        ++failures;
    }
}

}  // namespace

int main() {
    check(cpp_starter::greet("世界") == "你好，世界！", R"(greet("世界"))");
    check(cpp_starter::greet("").find("陌生人") != std::string::npos, R"(greet("") 返回默认问候)");
    check(!cpp_starter::greet("C++").empty(), R"(greet("C++") 非空)");
    check(cpp_starter::greet("C++") == "你好，C++！", R"(greet("C++") 内容正确)");

    if (failures != 0) {
        std::cout << failures << " 项失败\n";
        return EXIT_FAILURE;
    }
    std::cout << "全部通过\n";
    return EXIT_SUCCESS;
}
