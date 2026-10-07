#pragma once

#include <string>
#include <string_view>

namespace cpp_starter {

/// 杩斿洖涓€鍙ラ棶鍊欒銆?///
/// greet("涓栫晫")  -> "浣犲ソ锛屼笘鐣岋紒"
/// greet("")      -> "浣犲ソ锛岄檶鐢熶汉锛?
[[nodiscard]] std::string greet(std::string_view name);

}  // namespace cpp_starter


