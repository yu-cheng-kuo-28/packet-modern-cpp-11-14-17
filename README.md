# 🥣 Overview of packet-modern-cpp-11-14-17

> From [Complete Modern C++ (C++11/14/17) Specialization](https://www.coursera.org/specializations/packt-complete-modern-c-c-11-14-17) by Packt on Coursera [including 3 courses]

This repository contains comprehensive demonstrations and educational materials for modern C++ features across C++11, C++14, C++17, and C++20 standards.

---

## 📚 Projects

### 🚀 [1] Lambda Function Evolution (`01_lambda_function/`)

**A complete educational resource for learning lambda expressions in modern C++**

#### 🎯 What's Inside

**5 Progressive Demo Files:**
- `00_cpp_version_check.cpp` - Compiler standard support detection
- `01_simple_lambda_comparison.cpp` - Beginner-friendly syntax evolution
- `02_lambda_feature_comparison.cpp` - Comprehensive feature reference (legal vs illegal)
- `03_lambda_evolution_demo.cpp` - Real-world data processing pipeline
- `04_lambda_replace_bind.cpp` - Why lambdas replaced `std::bind` (C++ Core Guidelines C.36)

**📖 Comprehensive Documentation:**
- **[`LAMBDA_GUIDE.md`](01_lambda_function/documentation/LAMBDA_GUIDE.md)** (712 lines)
  - Feature matrix tables for C++11/14/17/20
  - "What you CAN/CANNOT do" sections
  - Evolution timeline and migration guide
  - Quick decision tables
  
- **[`LAMBDA_VS_BIND.md`](01_lambda_function/documentation/LAMBDA_VS_BIND.md)** (1,122 lines)
  - Complete historical evolution: Manual Functors → `std::bind` → Lambdas
  - Technical deep dive with assembly comparisons
  - C++ Core Guidelines C.36 explanation
  - Before/after migration patterns

#### 🎓 Educational Design

This project is designed as a **systematic learning path**:

1. **Version Check** → Verify compiler support
2. **Simple Syntax** → Learn basic lambda syntax evolution (no complex STL)
3. **Feature Reference** → Understand what's legal/illegal in each standard
4. **Practical Demo** → See real-world applications
5. **Historical Context** → Understand *why* lambdas replaced older patterns

**Educational Assessment:**
- ⭐⭐⭐⭐⭐ Beginner-friendly (starts simple, builds systematically)
- ⭐⭐⭐⭐⭐ Comprehensive coverage (all C++11/14/17/20 features)
- ⭐⭐⭐⭐⭐ Practical focus (real-world examples, not toy code)
- ⭐⭐⭐⭐⭐ Well-documented (1,800+ lines of curated documentation)

#### 🔨 Building & Running

```bash
# Build all demos
cd 01_lambda_function
cmake -S . -B build
cmake --build build

# Run recommended learning sequence
build/00_version_check_cpp17
build/01_simple_lambda_comparison_cpp11
build/02_lambda_feature_comparison_cpp14
build/03_lambda_evolution_demo_cpp17
build/04_lambda_replace_bind_cpp14
```

**Quick Targets:**
```bash
cmake --build build --target all-simple       # Build all simple demos
cmake --build build --target run-simple-cpp14 # Run simple demos with C++14
```

#### 📊 Key Features Covered

| C++ Standard | Key Innovations | Documentation |
|--------------|-----------------|---------------|
| **C++11** | Basic lambdas, explicit captures, return types | ✅ Full coverage |
| **C++14** | Auto parameters, init capture, generic lambdas | ✅ Full coverage |
| **C++17** | Constexpr lambdas, parallel execution | ✅ Full coverage |
| **C++20** | Template lambdas, concepts integration | ✅ Full coverage |

#### 🔗 Getting Started

**👉 [Start with the Lambda Function README](01_lambda_function/README.md)**

This provides:
- Detailed learning path
- Build instructions
- Feature breakdowns by C++ standard
- Links to comprehensive documentation

---

## 🎯 Coming Soon

- **02_OOP_runtime_cost**

---

## 📖 Documentation Philosophy

This repository emphasizes **high-quality, educational documentation** that:

- ✅ Provides clear, progressive learning paths
- ✅ Explains *why* features evolved, not just *how* to use them
- ✅ Includes comprehensive feature comparison tables
- ✅ Offers practical, real-world examples
- ✅ Covers historical context and design decisions
- ✅ References C++ Core Guidelines and best practices

---

## 🤝 Contributing

This is an educational repository based on Coursera course materials. Contributions that enhance educational value are welcome:

- Bug fixes in demo code
- Improved documentation clarity
- Additional practical examples
- Better explanations of complex concepts

---

## 📄 License

Educational materials based on the Packt Coursera specialization.

---

## 🙏 Acknowledgments

- **Packt Publishing** - Original course content
- **Coursera** - Platform and distribution
- **C++ Community** - Core Guidelines and best practices
