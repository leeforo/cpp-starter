# cpp-starter

一个最小、无第三方依赖的 C++23 起步项目，用来验证工具链和作为新项目的骨架。

## 目录结构

```
cpp-starter/
├── .clang-format              # 代码格式化规则
├── .gitignore                 # 已排除 build/ 等产物，不会误提交
├── CMakeLists.txt
├── CMakePresets.json          # 预置的 4 套构建配置
├── README.md
├── .github/workflows/ci.yml   # GitHub Actions（推到 GitHub 才生效）
├── include/cpp_starter/
│   └── greet.hpp              # 公开头文件
├── src/
│   ├── greet.cpp              # 库实现
│   └── main.cpp               # 命令行程序
└── tests/
    └── test_greet.cpp         # 最小测试，由 ctest 驱动
```

产物分三层：静态库 `cpp_starter`、可执行文件 `cpp_starter_app`、测试 `cpp_starter_tests`。

## 环境要求

- CMake ≥ 3.25（使用 presets 需要）
- 支持 C++23 的编译器（GCC ≥ 13 / MSVC ≥ 19.3x）
- `std::format`（GCC 13+ / MSVC 19.29+ 均已支持）

本项目在以下环境实测通过：

| 工具链 | 版本 |
|---|---|
| GCC (MinGW-w64) + Ninja | GCC 15.2.0 / CMake 4.3.1 / Ninja 1.13.2 |
| MSVC + Visual Studio 生成器 | MSVC 14.51 (VS 2026) |

## 构建与运行（推荐用 CMake Presets）

```powershell
cmake --list-presets          # 看有哪些 preset

# GCC（要求 g++.exe 在 PATH 上）
cmake --preset gcc-debug
cmake --build --preset gcc-debug
ctest --preset gcc-debug
.\build\gcc-debug\cpp_starter_app.exe

# MSVC（用 Visual Studio 生成器，不需要先跑 vcvars）
cmake --preset msvc-debug
cmake --build --preset msvc-debug
ctest --preset msvc-debug
.\build\msvc-debug\Debug\cpp_starter_app.exe
```

把 `debug` 换成 `release` 即 Release 构建。共 4 个 preset：
`gcc-debug` / `gcc-release` / `msvc-debug` / `msvc-release`。

> **为什么 MSVC 用 VS 生成器而不是 Ninja？**
> 两个原因：① VS 生成器自带完整环境，不需要先执行 `Enter-Msvc`；
> ② 本机 **MSVC + Ninja + sccache** 会导致头文件依赖跟踪失效
> （改头文件不重编译），VS 生成器没有这个问题。
> 若确实想用 MSVC + Ninja，手动 `-G Ninja` 配置即可，但**不要**加 sccache。

### 不用 Presets 的手动写法

```powershell
# GCC
cmake -S . -B build-gcc -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++.exe
cmake --build build-gcc

# MSVC + Ninja（需先 Enter-Msvc）
Enter-Msvc
cmake -S . -B build-msvc -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-msvc
```

## 输出示例

```powershell
.\build\gcc-debug\cpp_starter_app.exe          # 你好，世界！
.\build\gcc-debug\cpp_starter_app.exe Alice    # 你好，Alice！
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

## 持续集成

`.github/workflows/ci.yml` 在 **GitHub** 上运行（推到 Gitee 不会触发）：

| Job | 内容 |
|---|---|
| `linux` | ubuntu-latest，GCC 与 Clang 双矩阵，Debug 构建 + ctest |
| `linux-release` | Release 构建，额外加 `-Werror`（警告即失败） |
| `windows-msvc` | windows-latest，MSVC + VS 2022 生成器 |

> **两点说明：**
> 1. 这些 workflow 只有代码推到 **GitHub** 后才会执行。Gitee 用的是
>    Gitee Go，语法不同，此文件不会被识别。
> 2. GitHub Actions 无法在本地运行，所以首次推送后请留意 CI 结果。
>    最可能失败的是 `-Werror` 那条（不同 GCC 版本的警告集合略有差异）。

## 可选的编译加速

`sccache` 已在本机安装。**但注意一个禁用组合**：
`MSVC + Ninja + sccache` 会导致头文件依赖跟踪失效，改头文件不重编译。

安全的用法：

```powershell
# GCC 可以放心加
cmake -S . -B build-gcc -G Ninja -DCMAKE_CXX_COMPILER_LAUNCHER=sccache `
      -DCMAKE_CXX_COMPILER=g++.exe

# MSVC 请改用 Visual Studio 生成器
cmake -S . -B build-msvc -G "Visual Studio 18 2026" -A x64 `
      -DCMAKE_CXX_COMPILER_LAUNCHER=sccache
```

验证脚本：`D:\Dev\01_Tools\setup\dep-matrix.ps1`

## 许可证

未指定。自行按需添加。
