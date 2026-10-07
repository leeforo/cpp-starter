# cpp-starter

一个最小、无第三方依赖的 C++23 起步项目，用来验证工具链和作为新项目的骨架。

## 目录结构

```
cpp-starter/
├── .clang-format          # 代码格式化规则
├── .gitignore             # 已排除 build/ 等产物，不会误提交
├── CMakeLists.txt
├── README.md
├── include/cpp_starter/
│   └── greet.hpp          # 公开头文件
├── src/
│   ├── greet.cpp          # 库实现
│   └── main.cpp           # 命令行程序
└── tests/
    └── test_greet.cpp     # 最小测试，由 ctest 驱动
```

产物分三层：静态库 `cpp_starter`、可执行文件 `cpp_starter_app`、测试 `cpp_starter_tests`。

## 环境要求

- CMake ≥ 3.20
- 支持 C++23 的编译器（GCC ≥ 13 / MSVC ≥ 19.3x）
- `std::format`（GCC 13+ / MSVC 19.29+ 均已支持）

本项目在以下环境实测通过：

| 工具链 | 版本 |
|---|---|
| GCC (MinGW-w64) + Ninja | GCC 15.2.0 / CMake 4.3.1 / Ninja 1.13.2 |
| MSVC + Ninja | MSVC 14.51 (VS 2026) |

## 构建与运行

### 用 GCC（MinGW-w64）

```powershell
cmake -S . -B build-gcc -G Ninja -DCMAKE_BUILD_TYPE=Debug `
      -DCMAKE_CXX_COMPILER=D:/Dev/01_Tools/mingw64/bin/g++.exe
cmake --build build-gcc
.\build-gcc\cpp_starter_app.exe
```

### 用 MSVC

MSVC 需要先加载编译环境。本机已配好 `Enter-Msvc`（见 PowerShell profile）：

```powershell
Enter-Msvc
cmake -S . -B build-msvc -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-msvc
.\build-msvc\cpp_starter_app.exe
```

> 若改为 `-G "Visual Studio 18 2026"`，则用
> `cmake --build build-msvc --config Debug`，产物在
> `build-msvc\Debug\cpp_starter_app.exe`。

### 运行测试

```powershell
ctest --test-dir build-gcc --output-on-failure
```

## 输出示例

```powershell
.\build-gcc\cpp_starter_app.exe          # 你好，世界！
.\build-gcc\cpp_starter_app.exe Alice    # 你好，Alice！
```

> **已知限制 1（终端显示）**：终端若显示乱码，先执行 `chcp 65001` 切到 UTF-8。
> 本机 PowerShell profile 已自动设置。
>
> **已知限制 2（中文参数）**：从 PowerShell 给 .exe 传**非 ASCII 参数**时，
> 参数可能在到达程序之前就被按 ANSI 代码页转码而乱掉
> （实测 `... 李非凡` 会输出乱码）。
> 这是 Windows 命令行参数传递的限制，**与程序逻辑无关**——
> 程序内部的字符串全部是 UTF-8，测试用例可证明。
> 若真需要在命令行可靠处理中文参数，需改用 `wmain` + `CommandLineToArgvW`。

## 可选的编译加速

`sccache` 已在本机安装。**但注意一个禁用组合**：
`MSVC + Ninja + sccache` 会导致头文件依赖跟踪失效，改头文件不重编译。

安全的用法：

```powershell
# GCC 可以放心加
cmake -S . -B build-gcc -G Ninja -DCMAKE_CXX_COMPILER_LAUNCHER=sccache ...

# MSVC 请改用 Visual Studio 生成器
cmake -S . -B build-msvc -G "Visual Studio 18 2026" -DCMAKE_CXX_COMPILER_LAUNCHER=sccache ...
```

验证脚本：`D:\Dev\01_Tools\setup\dep-matrix.ps1`

## 许可证

未指定。自行按需添加。
