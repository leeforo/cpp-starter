#include "cpp_starter/greet.hpp"

#include <format>

namespace cpp_starter {

std::string greet(std::string_view name) {
    if (name.empty()) {
        return "你好，陌生人！";
    }
    return std::format("你好，{}！", name);
}

}  // namespace cpp_starter
