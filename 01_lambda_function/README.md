# Lambda Function Evolution in Modern C++ (C++11/14/17/20)

> **📖 For comprehensive documentation, see the [`documentation/`](documentation/) folder:**
> - **[`LAMBDA_GUIDE.md`](documentation/LAMBDA_GUIDE.md)** - Concise feature tables and quick reference across all C++ standards
> - **[`LAMBDA_VS_BIND.md`](documentation/LAMBDA_VS_BIND.md)** - Complete analysis of why lambdas replaced `std::bind` (C++ Core Guidelines C.36)

This project demonstrates the evolution of lambda functions across C++11, C++14, C++17, and C++20 through **practical, educational examples**.

---

## 📚 Quick Start

### 🎯 Recommended Learning Path

**New to lambdas? Start here:**

1. **Check your compiler** → Run [`00_cpp_version_check.cpp`](00_cpp_version_check.cpp)
2. **Learn syntax basics** → Study [`01_simple_lambda_comparison.cpp`](01_simple_lambda_comparison.cpp) (beginner-friendly!)
3. **Understand limitations** → Reference [`02_lambda_feature_comparison.cpp`](02_lambda_feature_comparison.cpp)
4. **See practical usage** → Explore [`03_lambda_evolution_demo.cpp`](03_lambda_evolution_demo.cpp)
5. **Why replace std::bind?** → Read [`04_lambda_replace_bind.cpp`](04_lambda_replace_bind.cpp) + [`documentation/LAMBDA_VS_BIND.md`](documentation/LAMBDA_VS_BIND.md)

**Need quick reference?**
- 📊 **Feature tables** → [`documentation/LAMBDA_GUIDE.md`](documentation/LAMBDA_GUIDE.md)
- 🔍 **What's legal in C++X?** → [`02_lambda_feature_comparison.cpp`](02_lambda_feature_comparison.cpp)

---

## 📂 Project Structure

```
01_lambda_function/
├── 00_cpp_version_check.cpp           # Check compiler C++ standard support
├── 01_simple_lambda_comparison.cpp    # Pure syntax evolution (⭐ Start here!)
├── 02_lambda_feature_comparison.cpp   # Legal vs illegal features per standard
├── 03_lambda_evolution_demo.cpp       # Real-world data processing examples
├── 04_lambda_replace_bind.cpp         # Why lambdas replaced std::bind
├── CMakeLists.txt                     # Build configuration
├── README.md                          # This file
├── documentation/
│   ├── LAMBDA_GUIDE.md               # 📖 Concise feature reference tables
│   └── LAMBDA_VS_BIND.md             # 📖 Complete lambda vs std::bind analysis
└── output_record/
    ├── 00_cpp_version_check_cpp20.txt
    ├── 01_simple_lambda_comparison_cpp20.txt
    ├── 02_lambda_feature_comparison_cpp20.txt
    ├── 03_lambda_evolution_demo_cpp20.txt
    └── 04_lambda_replace_bind.txt
```

---

## 📖 Comprehensive Documentation

### 🌟 Featured Documentation Files

#### [`documentation/LAMBDA_GUIDE.md`](documentation/LAMBDA_GUIDE.md)
**The ultimate quick reference for lambda features**

Contains:
- ✅ **Feature matrix table** - What's available in C++11/14/17/20 at a glance
- 📋 **"What you CAN/CANNOT do"** sections for each standard
- 🎓 **Evolution timeline** - Visual progression of capabilities
- 💡 **Practical use cases** - Code examples for each C++ version
- 🚀 **Migration guide** - How to upgrade from C++11 → C++14 → C++17 → C++20
- 📊 **Quick decision table** - "Need feature X? Use C++ standard Y"

**Perfect for:** Quick lookups, feature checking, understanding limitations

---

#### [`documentation/LAMBDA_VS_BIND.md`](documentation/LAMBDA_VS_BIND.md)
**Complete analysis of the lambda vs std::bind evolution**

Contains:
- 🔄 **The evolution chain:** Manual Functors → `std::bind` → Lambdas
- 📜 **Historical timeline:** C++11 → C++14 (tipping point) → C++17 (official guideline)
- 🧠 **Technical deep dive:** Function objects vs function pointers vs polymorphism
- ⚔️ **Feature comparison:** Detailed tables comparing all approaches
- 🎯 **Why lambdas won:** Readability, type safety, performance, modern features
- 📊 **Assembly comparison:** All three compile to identical machine code
- 🔍 **Core Guidelines C.36:** Why it was officially codified in C++17
- 🚀 **Migration patterns:** Before/after code examples

**Perfect for:** Understanding design decisions, historical context, advanced topics

---

## 🎓 Educational Progression Overview

This project provides a **systematic, progressive learning path** with each file serving a distinct pedagogical purpose:

### Demo Files at a Glance

| File | Purpose | Best For | Educational Value |
|------|---------|----------|-------------------|
| **`00_cpp_version_check.cpp`** | Quick version detection | Everyone | ⭐⭐⭐⭐⭐ Simple, essential first step |
| **`01_simple_lambda_comparison.cpp`** | Pure syntax evolution | Beginners | ⭐⭐⭐⭐⭐ No STL complexity, clear progression |
| **`02_lambda_feature_comparison.cpp`** | Comprehensive feature reference | Intermediate | ⭐⭐⭐⭐ Legal vs illegal per standard |
| **`03_lambda_evolution_demo.cpp`** | Real-world practical applications | Advanced | ⭐⭐⭐⭐ Data processing pipeline |
| **`04_lambda_replace_bind.cpp`** | std::bind vs lambda comparison | Intermediate+ | ⭐⭐⭐⭐ Historical context |

### Quality Assessment

- **`00_cpp_version_check.cpp`**: ⭐⭐⭐⭐⭐ **EXCELLENT**
  - Minimal code (45 lines), does one thing perfectly
  - Quick verification of compiler support
  
- **`01_simple_lambda_comparison.cpp`**: ⭐⭐⭐⭐⭐ **EXCELLENT** 
  - Best for beginners: Pure syntax focus
  - Shows same task (doubling) evolving across standards
  - Uses simple loops instead of confusing STL algorithms
  
- **`02_lambda_feature_comparison.cpp`**: ⭐⭐⭐⭐ **VERY GOOD**
  - Comprehensive: Shows what's ILLEGAL vs LEGAL in each version
  - Clear C++11 → C++14 → C++17 → C++20 progression
  - Perfect reference guide (slightly dense for true beginners)
  
- **`03_lambda_evolution_demo.cpp`**: ⭐⭐⭐⭐ **GOOD**
  - Practical focus: Real data processing pipeline
  - Demonstrates why evolution matters (verbosity → elegance)
  - Fixed structure: Compiles cleanly across all standards

- **`04_lambda_replace_bind.cpp`**: ⭐⭐⭐⭐ **EXCELLENT**
  - Shows evolution: Manual functors → std::bind → lambdas
  - Explains polymorphism and function objects
  - Demonstrates C++ Core Guidelines C.36 reasoning

---

## 🚀 Quick Feature Reference by C++ Standard

### C++11 - The Foundation

**What You CAN Do:**
- ✅ Basic captures: `[x]`, `[&x]`, `[=]`, `[&]`
- ✅ Explicit return types: `[](int x) -> int { ... }`
- ✅ Type-specific parameters: `[](int x, double y)`
- ✅ Simple return type deduction (single return)

**What You CANNOT Do:**
- ❌ Auto parameters (generic lambdas)
- ❌ Init capture (`[y = expr]`)
- ❌ Move capture
- ❌ Auto return type deduction (complex)
- ❌ Constexpr lambdas

**Example:**
```cpp
auto mean_calculator = [](const std::vector<double>& vec) -> double {
    double sum = 0.0;
    for (const auto& val : vec) {
        sum += val;
    }
    return sum / vec.size();
};
```

---

### C++14 - Generic Power

**NEW Features:**
- ✅ **Auto parameters** (generic lambdas): `[](auto x)`
- ✅ **Auto return type deduction**
- ✅ **Init capture**: `[y = expr]`
- ✅ **Move capture**: `[v = std::move(x)]`

**Example:**
```cpp
// Generic lambda - works with any type!
auto generic_accumulator = [](auto container, auto init_val, auto op) {
    return std::accumulate(container.begin(), container.end(), init_val, op);
};

// Init capture with move semantics
auto variance_calculator = [data_moved = std::move(data_copy)](const auto& vec) {
    // Use moved data here
};
```

---

### C++17 - Compile-Time Power

**NEW Features:**
- ✅ **Constexpr lambdas**: Can be evaluated at compile-time
- ✅ **Lambdas in constant expressions**
- ✅ **Structured bindings** (not lambda-specific, but works well together)

**Example:**
```cpp
// Constexpr lambda
constexpr auto square = [](auto x) constexpr { return x * x; };
constexpr int compile_time_result = square(5);  // Computed at compile-time!

// Used for array sizing
std::array<int, square(4)> arr;  // Array of 16 elements
```

---

### C++20 - Template Meta-Programming

**NEW Features:**
- ✅ **Template lambdas**: `[]<typename T>(T x)`
- ✅ **Concepts integration**: `[](std::integral auto x)`
- ✅ **Pack expansion in captures**

**Example:**
```cpp
// Template lambda with concepts
auto generic_statistical_op = []<typename T>(const std::vector<T>& vec, auto operation)
    requires std::is_arithmetic_v<T>
{
    return operation(vec);
};

// Concept-constrained lambda
auto safe_add = [](std::integral auto x) { return x + 1; };
```

> 📖 **For detailed feature tables and examples, see [`documentation/LAMBDA_GUIDE.md`](documentation/LAMBDA_GUIDE.md)**

---

## 🔨 Building and Running

### Using CMake (Recommended)

```bash
# Set up build directory (one-time)
cmake -S . -B build

# Build all demos
cmake --build build

# Run recommended learning sequence
build/00_version_check_cpp17                    # Check compiler support
build/01_simple_lambda_comparison_cpp11         # Start with beginner-friendly syntax
build/02_lambda_feature_comparison_cpp14        # Learn what's legal/illegal
build/03_lambda_evolution_demo_cpp17            # Real-world practical demo
build/04_lambda_replace_bind_cpp14              # Historical evolution context
```

### Convenience Targets

```bash
# Build all simple comparison binaries
cmake --build build --target all-simple

# Build all feature comparison binaries  
cmake --build build --target all-comparison

# Run all simple demos
cmake --build build --target run-simple-cpp14

# Run all comparison demos
cmake --build build --target run-comparison-cpp17
```

### Manual Compilation Examples

```bash
# Version check
g++ -std=c++17 -Wall -O2 00_cpp_version_check.cpp -o version_check

# Simple comparison (beginner-friendly)
g++ -std=c++11 -Wall -O2 01_simple_lambda_comparison.cpp -o simple_cpp11
g++ -std=c++14 -Wall -O2 01_simple_lambda_comparison.cpp -o simple_cpp14

# Feature comparison (reference guide)
g++ -std=c++14 -Wall -O2 02_lambda_feature_comparison.cpp -o comparison_cpp14
g++ -std=c++17 -Wall -O2 02_lambda_feature_comparison.cpp -o comparison_cpp17

# Evolution demo (practical applications)
g++ -std=c++17 -Wall -O2 03_lambda_evolution_demo.cpp -o demo_cpp17
g++ -std=c++20 -Wall -O2 03_lambda_evolution_demo.cpp -o demo_cpp20

# std::bind replacement (historical context)
g++ -std=c++14 -Wall -O2 04_lambda_replace_bind.cpp -o bind_demo_cpp14
```

---

## 📊 Performance Insights

| Version | Key Features | Performance | Code Clarity |
|---------|--------------|-------------|--------------|
| **C++11** | Basic lambdas | ⭐⭐⭐⭐ Good | Verbose, explicit types |
| **C++14** | Generic lambdas, init capture | ⭐⭐⭐⭐⭐ Better | Much cleaner |
| **C++17** | Constexpr, parallel execution | ⭐⭐⭐⭐⭐ Excellent | Very clean |
| **C++20** | Template lambdas, concepts | ⭐⭐⭐⭐⭐ Optimal | Extremely clean |

> 💡 **Note:** Performance differences are primarily in **compile-time** and **code maintainability**. Runtime performance is nearly identical across standards when optimizations are enabled.

---

## 🎯 Key Takeaways

1. **C++11**: 🏗️ Foundation for lambda expressions - basic syntax, explicit types
2. **C++14**: 🚀 Made lambdas generic and flexible - auto parameters, init capture  
3. **C++17**: ⚡ Performance optimizations - constexpr lambdas, parallel execution
4. **C++20**: 🎨 Template-level programming - concepts, template parameters

Each version builds upon the previous, making code more expressive, performant, and maintainable.

---

## 📚 Further Reading

### Essential Documentation
- 📖 **[`documentation/LAMBDA_GUIDE.md`](documentation/LAMBDA_GUIDE.md)** - Quick reference with feature tables for C++11/14/17/20
- 📖 **[`documentation/LAMBDA_VS_BIND.md`](documentation/LAMBDA_VS_BIND.md)** - Complete historical evolution from functors → std::bind → lambdas

### External Resources
- [C++ Lambda Expressions (cppreference)](https://en.cppreference.com/w/cpp/language/lambda)
- [Effective Modern C++ by Scott Meyers](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/) - Items 31-34 cover lambdas extensively
- [C++20 Lambda Improvements](https://www.modernescpp.com/index.php/c-20-lambdas-improvements)
- [C++ Core Guidelines: C.36 - Prefer lambdas to std::bind](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c36-a-lambda-may-be-a-better-choice-than-stdfunction-or-stdbind)

---