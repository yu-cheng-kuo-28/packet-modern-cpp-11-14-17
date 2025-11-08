# 🥣 Overview of packet-modern-cpp-11-14-17
- From [Complete Modern C++ (C++11/14/17) Specialization](https://www.coursera.org/specializations/packt-complete-modern-c-c-11-14-17) by Packet on Coursera [including 3 courses]

## 🚀 Lambda Function Evolution Demo

This repository includes **systematic educational examples** demonstrating how lambda functions evolved across different C++ standards. The examples are organized for **progressive learning**:

### 📁 Organized Learning Path (`01_lambda_function/`)
- `00_cpp_version_check.cpp` - **Start here**: Check compiler C++ standard support  
- `01_lambda_feature_comparison.cpp` - **Core concepts**: What's illegal vs legal in each version
- `02_simple_lambda_comparison.cpp` - **Syntax evolution**: Same task across C++ versions
- `03_lambda_evolution_demo.cpp` - **Practical applications**: Real-world data processing examples
- `CMAKE_README.md` - **Modern build system**: CMake instructions and targets
- `LAMBDA_GUIDE.md` - **Comprehensive guide**: Detailed explanations and learning path

### Key Features Demonstrated

#### C++11 Lambdas
```cpp
auto lambda = [](int x) -> int { return x * 2; };
```
- Explicit return types
- Basic capture modes
- Simple syntax

#### C++14 Lambdas
```cpp
auto lambda = [](auto x) { return x * 2; };
```
- Generic parameters (auto)
- Auto return type deduction  
- Generalized capture (init capture)

#### C++17 Lambdas
```cpp
constexpr auto lambda = [](auto x) constexpr { return x * 2; };
```
- Constexpr lambdas
- Structured bindings support
- Better algorithm integration

#### C++20 Lambdas
```cpp
auto lambda = []<typename T>(T x) requires std::is_arithmetic_v<T> { return x * 2; };
```
- Template parameters
- Concepts integration
- Pack expansion in captures

### 🎯 Quick Start (Recommended Learning Path)

#### Using CMake (Modern Approach)
```bash
cd 01_lambda_function
mkdir build && cd build
cmake ..

# Follow the learning progression:
cmake --build . --target version_check_cpp17      # 1. Check compiler support
cmake --build . --target run-comparison_cpp11     # 2. Learn what's illegal/legal  
cmake --build . --target run-all-simple          # 3. See syntax evolution
cmake --build . --target run-all-full            # 4. Explore practical applications
```

#### Manual Compilation
```bash
cd 01_lambda_function

# Check your compiler first
g++ -std=c++17 00_cpp_version_check.cpp -o version_check && ./version_check

# Learn the progression
g++ -std=c++11 01_lambda_feature_comparison.cpp -o features && ./features
g++ -std=c++17 02_simple_lambda_comparison.cpp -o simple && ./simple  
g++ -std=c++17 03_lambda_evolution_demo.cpp -o practical && ./practical
```

### 📚 Educational Benefits
- **Systematic progression**: From basic syntax to advanced applications
- **Clear illegal vs legal examples**: Understand what compiles in each version
- **Practical focus**: Real-world data processing scenarios
- **Modern build system**: CMake integration for professional development