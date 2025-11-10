# 🥣 packet-modern-cpp-11-14-17

- This repo and the article below were greatly helped by ChatGPT/Copilot.

- The corresponding article: [C++ 02 | Lambda Evolution: From C++11 to C++17 (and Why You Should Abandon std::bind())](https://yc-kuo.medium.com/c-02-lambda-evolution-from-c-11-to-c-20-and-why-you-should-abandon-std-bind-2896cb80f7e5)

> Inspired by the online courses [Complete Modern C++ (C++11/14/17) Specialization](https://www.coursera.org/specializations/packt-complete-modern-c-c-11-14-17) by Packt on Coursera

Educational demonstrations for modern C++ features across C++11/14/17/20 standards.

### 📁 Organized Learning Path (`01_lambda_function/`)
- `00_cpp_version_check.cpp` - **Start here**: Check compiler C++ standard support  
- `01_lambda_feature_comparison.cpp` - **Core concepts**: What's illegal vs legal in each version
- `02_simple_lambda_comparison.cpp` - **Syntax evolution**: Same task across C++ versions
- `03_lambda_evolution_demo.cpp` - **Practical applications**: Real-world data processing examples
- `CMAKE_README.md` - **Modern build system**: CMake instructions and targets
- `LAMBDA_GUIDE.md` - **Comprehensive guide**: Detailed explanations and learning path

### Key Features Demonstrated

### 🚀 [1] Lambda Function Evolution ([`01_lambda_function/`](01_lambda_function/))

Complete educational resource for learning lambda expressions in modern C++.

**Demo Files:**
- `00_cpp_version_check.cpp` - Compiler support detection
- `01_simple_lambda_comparison.cpp` - Beginner-friendly syntax evolution  
- `02_lambda_feature_comparison.cpp` - Feature reference (legal vs illegal)
- `03_lambda_evolution_demo.cpp` - Real-world data processing examples
- `04_lambda_replace_bind.cpp` - Why lambdas replaced `std::bind`

**Documentation:**
- **[`LAMBDA_GUIDE.md`](01_lambda_function/documentation/LAMBDA_GUIDE.md)** - Feature tables, migration guide, quick reference
- **[`LAMBDA_VS_BIND.md`](01_lambda_function/documentation/LAMBDA_VS_BIND.md)** - Historical evolution: Functors → `std::bind` → Lambdas

**Quick Start:**
```bash
$ cd 01_lambda_function
$ mkdir build && cd build && cmake .. && make
$ ./01_simple_lambda_comparison_cpp20
```

� **[Full documentation](01_lambda_function/README.md)**

---

### 🎯 [2] Coming Soon: OOP Runtime Cost

---

## References

[1] [Complete Modern C++ (C++11/14/17) Specialization](https://www.coursera.org/specializations/packt-complete-modern-c-c-11-14-17)

[2] [What's New in Modern C++](https://www.coursera.org/learn/pearson-whats-new-in-modern-c-video-course-iehyz)
