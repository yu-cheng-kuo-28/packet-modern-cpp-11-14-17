# Lambda Function Evolution Guide (C++11/14/17/20)

## 📚 Quick Reference

This guide provides a concise overview of lambda function features across C++ standards, extracted from practical demonstrations in the `01_lambda_function` directory.

---

## 🎯 Feature Matrix by C++ Standard

### Complete Feature Comparison

| Feature | C++11 | C++14 | C++17 | C++20 | Description |
|---------|:-----:|:-----:|:-----:|:-----:|-------------|
| **Basic Captures** | ✅ | ✅ | ✅ | ✅ | `[x]`, `[&x]`, `[=]`, `[&]` |
| **Explicit Return Type** | ✅ | ✅ | ✅ | ✅ | `[](int x) -> int { ... }` |
| **Type-Specific Parameters** | ✅ | ✅ | ✅ | ✅ | `[](int x, double y)` |
| **Simple Return Deduction** | ✅ | ✅ | ✅ | ✅ | Single return statement |
| **Auto Parameters (Generic)** | ❌ | ✅ | ✅ | ✅ | `[](auto x) { ... }` |
| **Init Capture** | ❌ | ✅ | ✅ | ✅ | `[y = expr](int x)` |
| **Move Capture** | ❌ | ✅ | ✅ | ✅ | `[v = std::move(x)]` |
| **Auto Return Deduction** | ❌ | ✅ | ✅ | ✅ | Complex multi-return |
| **Constexpr Lambdas** | ❌ | ❌ | ✅ | ✅ | `constexpr auto f = []() constexpr` |
| **Compile-Time Evaluation** | ❌ | ❌ | ✅ | ✅ | Use in `constexpr` contexts |
| **Template Parameters** | ❌ | ❌ | ❌ | ✅ | `[]<typename T>(T x)` |
| **Concepts Integration** | ❌ | ❌ | ❌ | ✅ | `[](std::integral auto x)` |
| **Pack Expansion in Captures** | ❌ | ❌ | ❌ | ✅ | `[...args = std::move(args)]` |

---

## 📖 Detailed Feature Guide

### C++11 - The Foundation

**What You CAN Do:**

```cpp
// ✅ Basic capture modes
auto lambda1 = [multiplier](int x) -> int { return x * multiplier; };      // By value
auto lambda2 = [&multiplier](int x) -> int { return x * multiplier; };     // By reference  
auto lambda3 = [=](int x) -> int { return x * multiplier; };               // All by value
auto lambda4 = [&](int x) -> int { return x * multiplier; };               // All by reference

// ✅ Explicit return types (required for complex cases)
auto lambda5 = [](int x) -> double {
    if (x > 0) return 3.14;
    return 2.71;
};

// ✅ Simple return type deduction (single return statement)
auto lambda6 = [](int x) { return x * 2; };  // Deduces int
```

**What You CANNOT Do:**

```cpp
// ❌ Init capture - ILLEGAL
// auto lambda = [y = multiplier * 2](int x) { return x * y; };  // ERROR!

// ❌ Move capture - ILLEGAL
// auto lambda = [v = std::move(data)](int x) { return v[0] * x; };  // ERROR!

// ❌ Auto parameters - ILLEGAL
// auto lambda = [](auto x) { return x * 2; };  // ERROR!

// ❌ Complex auto return type - ILLEGAL
// auto lambda = [](bool flag) { if (flag) return 3.14; return 42; };  // ERROR!
```

**Summary:**
- ✅ Basic captures: `[x]`, `[&x]`, `[=]`, `[&]`
- ✅ Explicit return types: `[](int x) -> int`
- ✅ Simple type-specific lambdas
- ❌ No auto parameters
- ❌ No init capture
- ❌ No move capture
- ❌ No auto return type deduction
- ❌ No constexpr

---

### C++14 - Generic Power

**NEW Features Introduced:**

```cpp
// ✅ NEW: Generalized capture (init capture)
auto lambda1 = [y = multiplier * 2](int x) { return x * y; };  // Init capture
auto lambda2 = [doubled = multiplier * 2, tripled = multiplier * 3](int x) {
    return x * doubled + tripled; 
};  // Multiple init captures

// ✅ NEW: Move capture
auto lambda3 = [v = std::move(data_copy)](int x) { return v[0] * x; };  // Move

// ✅ NEW: Auto parameters (generic lambdas)
auto lambda4 = [](auto x) { return x * 2; };  // Works with ANY type
auto lambda5 = [](auto x, auto y) { return x + y; };  // Multiple auto params

// ✅ NEW: Auto return type deduction
auto lambda6 = [](bool flag) {
    if (flag) return 3.14;  // double
    return 3.14;            // Must be same type, but auto deduced
};

// ✅ NEW: Complex generic operations
auto lambda7 = [](auto container, auto init, auto op) {
    return std::accumulate(container.begin(), container.end(), init, op);
};
```

**What You Still CANNOT Do:**

```cpp
// ❌ Constexpr lambdas - ILLEGAL
// constexpr auto lambda = [](auto x) constexpr { return x * 2; };  // ERROR!

// ❌ Structured bindings with lambdas - ILLEGAL
// auto [min, max] = some_lambda_returning_pair();  // ERROR!
```

**Summary:**
- ✅ All C++11 features
- ✅ **NEW:** Auto parameters: `[](auto x)`
- ✅ **NEW:** Init capture: `[y = expr]`
- ✅ **NEW:** Move capture: `[v = std::move(x)]`
- ✅ **NEW:** Auto return type deduction
- ❌ No constexpr lambdas

---

### C++17 - Compile-Time Power

**NEW Features Introduced:**

```cpp
// ✅ NEW: Constexpr lambdas
constexpr auto lambda1 = [](auto x) constexpr { return x * x; };  // Constexpr lambda
constexpr int compile_time_result = lambda1(5);  // Computed at compile-time

// ✅ NEW: Constexpr can be used in constant expressions
constexpr auto square_if_even = [](int n) constexpr {
    return (n % 2 == 0) ? n * n : n;
};
constexpr int array_size = square_if_even(4);  // Used for array size
std::array<int, array_size> compile_time_array{};  // Size = 16, known at compile-time

// ✅ NEW: Lambdas in constant expressions
constexpr auto get_array_size = [](int base) constexpr { return base * base; };
std::array<int, get_array_size(3)> const_array{};  // Array size = 9, compile-time

// ✅ NEW: Constexpr lambdas in algorithms
auto transform_result = std::accumulate(data.begin(), data.end(), 0,
    [](auto sum, auto val) constexpr {
        return sum + val * val;
    });
```

**What You Still CANNOT Do:**

```cpp
// ❌ Template parameters on lambdas - ILLEGAL
// auto lambda = []<typename T>(T x) { return x * 2; };  // ERROR!

// ❌ Concepts with lambdas - ILLEGAL
// auto lambda = [](auto x) requires std::integral<decltype(x)> { ... };  // ERROR!

// ❌ Pack expansion in captures - ILLEGAL
// auto lambda = [...args = std::move(args)]() { ... };  // ERROR!
```

**Summary:**
- ✅ All C++14 features
- ✅ **NEW:** Constexpr lambdas
- ✅ **NEW:** Lambdas in constant expressions
- ✅ **NEW:** Structured bindings (not lambda-specific)
- ❌ No template parameters

---

### C++20 - Template Meta-Programming

**NEW Features Introduced:**

```cpp
// ✅ NEW: Template lambdas
auto lambda1 = []<typename T>(T x) { return x * x; };  // Template parameter
auto lambda2 = []<typename T, typename U>(T x, U y) { return x + y; };  // Multiple

// ✅ NEW: Concepts with lambdas
auto lambda3 = []<typename T>(T x) requires std::is_arithmetic_v<T> {
    return x * 2;
};  // Requires clause

// ✅ NEW: Concepts in auto parameters
auto lambda4 = [](std::integral auto x) { return x + 1; };  // Concept constraint

// ✅ NEW: Advanced template lambda with concepts
auto generic_container_op = []<typename Container>
    (const Container& c, auto operation) 
    requires requires(typename Container::value_type v) { 
        { operation(v) } -> std::same_as<typename Container::value_type>; 
    }
{
    Container result;
    std::transform(c.begin(), c.end(), std::back_inserter(result), operation);
    return result;
};

// ✅ NEW: Pack expansion in captures (variadic)
auto make_tuple_lambda = [](auto... args) {
    return std::make_tuple(args...);
};
```

**Summary:**
- ✅ All C++17 features
- ✅ **NEW:** Template parameters: `[]<typename T>(T x)`
- ✅ **NEW:** Concepts integration
- ✅ **NEW:** Pack expansion in captures
- ✅ **NEW:** Advanced type constraints

---

## 🎓 Evolution Timeline

```
C++11 (2011)
  └─► Foundation: Basic lambdas with captures and explicit types
       ├─ [x], [&x], [=], [&]
       ├─ [](int x) -> int { ... }
       └─ Enabled functional programming patterns

C++14 (2014)
  └─► Generic Lambdas: Auto parameters and init capture
       ├─ [](auto x) { ... }
       ├─ [y = expr](int x) { ... }
       ├─ [v = std::move(x)]() { ... }
       └─ Made lambdas truly generic and flexible

C++17 (2017)
  └─► Compile-Time: Constexpr lambdas
       ├─ constexpr auto f = [](auto x) constexpr { ... }
       ├─ Used in array sizes, template parameters
       └─ Enabled compile-time functional programming

C++20 (2020)
  └─► Template Power: Explicit templates and concepts
       ├─ []<typename T>(T x) { ... }
       ├─ [](std::integral auto x) { ... }
       ├─ []<typename T>(T x) requires std::is_arithmetic_v<T> { ... }
       └─ Full template meta-programming capabilities
```

---

## 🔍 Practical Use Cases by Standard

### C++11 Use Cases

**Best for:**
- Algorithm customization with STL
- Callback functions with simple state
- RAII-style cleanup with captures

```cpp
// Algorithm customization
std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });

// Callback with state
int threshold = 10;
auto predicate = [threshold](int x){ return x > threshold; };
std::count_if(v.begin(), v.end(), predicate);

// RAII cleanup
auto cleanup = [&resource](){ resource.close(); };
// Use cleanup() when needed
```

---

### C++14 Use Cases

**Best for:**
- Generic algorithms
- Move-only types (unique_ptr, etc.)
- Creating callable objects with computed state

```cpp
// Generic algorithm
auto generic_sum = [](auto container) {
    using T = typename decltype(container)::value_type;
    return std::accumulate(container.begin(), container.end(), T{});
};

// Move capture for unique_ptr
auto process = [ptr = std::make_unique<Data>()](int x) {
    return ptr->compute(x);
};

// Init capture with computation
auto processor = [multiplier = compute_multiplier()](int x) {
    return x * multiplier;
};
```

---

### C++17 Use Cases

**Best for:**
- Compile-time computations
- Constant expressions in templates
- Zero-overhead abstractions

```cpp
// Compile-time array sizing
constexpr auto compute_size = [](int n) constexpr { return n * n; };
std::array<int, compute_size(10)> arr;  // Array of 100 elements

// Compile-time validation
constexpr auto is_valid = [](int x) constexpr { return x > 0 && x < 100; };
static_assert(is_valid(50), "Value must be in range");

// Constexpr algorithm
constexpr auto sum_squares = [](const auto& v) constexpr {
    int sum = 0;
    for (auto x : v) sum += x * x;
    return sum;
};
```

---

### C++20 Use Cases

**Best for:**
- Type-safe generic programming
- Concept-constrained algorithms
- Advanced template meta-programming

```cpp
// Type-safe generic processing
auto safe_add = []<typename T>(T a, T b) requires std::is_arithmetic_v<T> {
    return a + b;
};

// Concept-constrained algorithm
auto process_integers = [](std::integral auto x) {
    return x * 2;
};

// Advanced container operations
auto transform_container = []<typename Container>(Container& c, auto op)
    requires requires(typename Container::value_type v) {
        { op(v) } -> std::convertible_to<typename Container::value_type>;
    }
{
    std::transform(c.begin(), c.end(), c.begin(), op);
};
```

---

## 📊 Quick Decision Guide

### "Which C++ Standard Should I Use?"

```
┌─────────────────────────────────────────────────────────┐
│ Need...                          │ Minimum C++ Standard │
├──────────────────────────────────┼──────────────────────┤
│ Basic lambdas                    │ C++11                │
│ Simple algorithm customization   │ C++11                │
│ Capture by value/reference       │ C++11                │
│ Generic lambdas (auto params)    │ C++14                │
│ Init capture                     │ C++14                │
│ Move semantics in capture        │ C++14                │
│ Constexpr lambdas                │ C++17                │
│ Compile-time computations        │ C++17                │
│ Template parameters              │ C++20                │
│ Concepts with lambdas            │ C++20                │
│ Type-safe generic programming    │ C++20                │
└──────────────────────────────────┴──────────────────────┘
```

---

## 🚀 Migration Guide

### From C++11 to C++14

**Before (C++11):**
```cpp
auto multiplier = [](int x) -> int { return x * 2; };  // Explicit type
```

**After (C++14):**
```cpp
auto multiplier = [](auto x) { return x * 2; };  // Generic!
```

---

### From C++14 to C++17

**Before (C++14):**
```cpp
auto square = [](auto x) { return x * x; };  // Runtime only
```

**After (C++17):**
```cpp
constexpr auto square = [](auto x) constexpr { return x * x; };  // Compile-time!
constexpr int result = square(10);  // Computed at compile-time
```

---

### From C++17 to C++20

**Before (C++17):**
```cpp
auto process = [](auto x) { return x * 2; };  // Works but not type-safe
```

**After (C++20):**
```cpp
auto process = []<typename T>(T x) requires std::is_arithmetic_v<T> {
    return x * 2;
};  // Type-safe with concepts!
```

---

## 📚 Related Files

- **`00_cpp_version_check.cpp`** - Check your compiler's C++ standard support
- **`01_simple_lambda_comparison.cpp`** - Pure syntax evolution (beginner-friendly)
- **`02_lambda_feature_comparison.cpp`** - What's legal vs illegal per standard
- **`03_lambda_evolution_demo.cpp`** - Real-world practical applications
- **`04_lambda_replace_bind.cpp`** - Why lambdas replaced `std::bind`

---

## 🔗 Further Reading

- **C++ Core Guidelines:** https://isocpp.github.io/CppCoreGuidelines/
- **cppreference Lambda:** https://en.cppreference.com/w/cpp/language/lambda
- **Effective Modern C++ (Scott Meyers):** Items 31-34 on lambdas
- **`LAMBDA_VS_BIND.md`:** Complete analysis of lambda vs std::bind evolution

---

**Document Version:** 1.0  
**Last Updated:** November 2025  
**Standards Covered:** C++11, C++14, C++17, C++20  
**Source:** Extracted from practical demonstrations in `01_lambda_function/`
