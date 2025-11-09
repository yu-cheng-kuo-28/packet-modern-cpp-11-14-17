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
| **Single Return Deduction** | ✅ | ✅ | ✅ | ✅ | One `return` statement only (C++11) |
| **Multiple Return Deduction** | ❌ | ✅ | ✅ | ✅ | Multiple `return` statements (same type) |
| **Auto Parameters (Generic)** | ❌ | ✅ | ✅ | ✅ | `[](auto x) { ... }` |
| **Init Capture** | ❌ | ✅ | ✅ | ✅ | `[y = expr](int x)` |
| **Move Capture** | ❌ | ✅ | ✅ | ✅ | `[v = std::move(x)]` |
| **Constexpr Lambdas** | ❌ | ❌ | ✅ | ✅ | `constexpr auto f = []() constexpr` |
| **Compile-Time Evaluation** | ❌ | ❌ | ✅ | ✅ | Use in `constexpr` contexts |
| **Structured Bindings** | ❌ | ❌ | ✅ | ✅ | `auto [x, y] = lambda()` |
| **Capture `*this` by Value** | ❌ | ❌ | ✅ | ✅ | `[*this]() { ... }` |
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

// ✅ Simple return type deduction (single return statement ONLY)
auto lambda6 = [](int x) { return x * 2; };  // Deduces int

// ❌ Multiple return statements - MUST specify return type
auto lambda7 = [](int x) -> int {  // Explicit return type required!
    if (x > 0) return x;
    else return -x;
};
// Without `-> int`, this would ERROR in C++11!
```

**What You CANNOT Do:**

```cpp
// ❌ Multiple return statements without explicit type - ILLEGAL
// auto lambda = [](int x) {  // ERROR in C++11!
//     if (x > 0) return x;
//     else return -x;
// };

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
- ✅ **Single-return** type deduction only
- ✅ Simple type-specific lambdas
- ❌ No **multiple-return** type deduction (must use explicit `-> T`)
- ❌ No auto parameters
- ❌ No init capture
- ❌ No move capture
- ❌ No constexpr
- ❌ No structured bindings

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

// ✅ NEW: Auto return type deduction (multiple returns!)
auto lambda6 = [](int x) {
    if (x > 0) return x;      // Now works!
    else return -x;           // Multiple returns, same type - OK in C++14!
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

// ❌ Structured bindings with lambdas - ILLEGAL (C++17 feature)
// auto [min, max] = some_lambda_returning_pair();  // ERROR!

// ❌ Capture *this by value - ILLEGAL (C++17 feature)
// auto lambda = [*this]() { return value; };  // ERROR!
```

**Key Improvement:**

**C++11 limitation removed:**
```cpp
// C++11: ERROR - must specify return type for multiple returns
// auto f = [](int x) { if (x > 0) return x; return -x; };  // ❌

// C++14: Works! Return type auto-deduced
auto f = [](int x) { if (x > 0) return x; return -x; };  // ✅
```

**Summary:**
- ✅ All C++11 features
- ✅ **NEW:** Auto parameters: `[](auto x)`
- ✅ **NEW:** Init capture: `[y = expr]`
- ✅ **NEW:** Move capture: `[v = std::move(x)]`
- ✅ **NEW:** Multiple-return type deduction (same type)
- ❌ No constexpr lambdas
- ❌ No structured bindings

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

// ✅ NEW: Structured bindings with lambda returns (C++17 general feature)
auto make_pair_lambda = [](int x) { return std::make_pair(x, x * 2); };
auto [a, b] = make_pair_lambda(10);  // Structured binding unpacks pair
std::cout << a << ", " << b;  // 10, 20

// ✅ NEW: Lambda returning tuple with structured binding
auto split_lambda = [](std::string_view s) {
    return std::tuple{s.substr(0, 3), s.substr(3), s.length()};
};
auto [head, tail, len] = split_lambda("abcdef");  // Unpack tuple

// ✅ NEW: Capture *this by value (thread-safe copy)
struct Widget {
    int value = 42;
    auto get_lambda() {
        return [*this]() { return value; };  // Copies entire object
    }
};

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
- ✅ **NEW:** Structured bindings with lambda returns
- ✅ **NEW:** Capture `*this` by value
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

## � Deep Dive: Return Type Deduction Evolution

### Understanding Return Type Deduction Across Standards

One of the most important (and often misunderstood) differences between C++11 and C++14 is how **return type deduction** works in lambdas.

#### C++11: Single-Return Deduction Only

**Rule:** In C++11, the compiler can **only** deduce the return type if the lambda body contains **exactly ONE return statement**.

```cpp
// ✅ OK in C++11 - single return statement
auto f1 = [](int x) { return x * 2; };  // Deduces: int

// ❌ ERROR in C++11 - multiple return statements
auto f2 = [](int x) {
    if (x > 0) return x;   // Both return int...
    else return -x;        // ...but TWO statements = ERROR!
};

// ✅ OK in C++11 - explicit return type required
auto f3 = [](int x) -> int {
    if (x > 0) return x;
    else return -x;
};  // Works with explicit `-> int`
```

**Why the limitation?**  
C++11's type deduction rules were conservative. Without an explicit return type, the compiler could only safely deduce from a single `return` statement.

---

#### C++14: Multiple-Return Deduction

**Rule:** C++14 **removed this restriction**. Now the compiler can deduce return types even with **multiple return statements**, as long as they all return the **same type**.

```cpp
// ✅ OK in C++14 - multiple returns, same type
auto f2 = [](int x) {
    if (x > 0) return x;
    else return -x;
};  // Deduces: int (no explicit type needed!)

// ✅ OK in C++14 - complex control flow
auto abs_diff = [](int a, int b) {
    if (a > b) return a - b;
    else if (b > a) return b - a;
    else return 0;
};  // All return int - type deduced

// ❌ Still ERROR - mixed types
auto bad = [](bool flag) {
    if (flag) return 3.14;  // double
    else return 42;         // int - ERROR! Types must match
};
```

---

### Comparison Table: Return Type Deduction

| Scenario | C++11 | C++14 | C++17+ |
|----------|-------|-------|--------|
| Single `return` statement | ✅ Type deduced | ✅ Type deduced | ✅ Type deduced |
| Multiple `return` (same type) | ❌ Must use `-> T` | ✅ Type deduced | ✅ Type deduced |
| Multiple `return` (mixed types) | ❌ Error | ❌ Error | ❌ Error |
| Explicit `-> T` always works | ✅ Yes | ✅ Yes | ✅ Yes |

---

### Structured Bindings with Lambda Returns (C++17+)

C++17 introduced **structured bindings**, which allow you to unpack tuple-like objects (including lambda returns).

#### Pre-C++17: Manual Unpacking

```cpp
// C++11/C++14: Return pair, unpack manually
auto make_pair_lambda = [](int x) {
    return std::make_pair(x, x * 2);
};

auto p = make_pair_lambda(10);
std::cout << p.first << ", " << p.second;  // 10, 20
```

#### C++17+: Structured Binding

```cpp
// C++17: Return pair, unpack with structured binding
auto make_pair_lambda = [](int x) {
    return std::make_pair(x, x * 2);
};

auto [a, b] = make_pair_lambda(10);  // ✨ Structured binding!
std::cout << a << ", " << b;  // 10, 20

// Works with tuples too
auto make_triple = [](int x) {
    return std::tuple{x, x * 2, x * 3};
};

auto [first, second, third] = make_triple(5);
std::cout << first << ", " << second << ", " << third;  // 5, 10, 15
```

**How it works:**
1. Lambda returns a tuple-like type (`std::pair`, `std::tuple`, array, or custom struct)
2. C++14 deduces the return type
3. C++17 structured binding unpacks it automatically

---

### Complete Example: Evolution of Same Function

```cpp
// ========================================
// Task: Return absolute value and original sign
// ========================================

// C++11: Must specify return type for multiple returns
auto process_cpp11 = [](int x) -> std::pair<int, int> {
    if (x >= 0) return std::make_pair(x, 1);
    else return std::make_pair(-x, -1);
};

auto p = process_cpp11(-5);
int abs_val = p.first;   // 5
int sign = p.second;     // -1

// ----------------------------------------

// C++14: Return type deduced (but still manual unpack)
auto process_cpp14 = [](int x) {
    if (x >= 0) return std::make_pair(x, 1);
    else return std::make_pair(-x, -1);
};  // Return type deduced: std::pair<int, int>

auto p = process_cpp14(-5);
int abs_val = p.first;
int sign = p.second;

// ----------------------------------------

// C++17: Deduced return + structured binding
auto process_cpp17 = [](int x) {
    if (x >= 0) return std::make_pair(x, 1);
    else return std::make_pair(-x, -1);
};

auto [abs_val, sign] = process_cpp17(-5);  // ✨ Clean unpacking!
std::cout << abs_val << ", " << sign;  // 5, -1

// ----------------------------------------

// C++20: Add type safety with concepts
auto process_cpp20 = []<std::integral T>(T x) {
    if (x >= 0) return std::make_pair(x, 1);
    else return std::make_pair(-x, -1);
};

auto [abs_val, sign] = process_cpp20(-5);  // Type-safe!
```

---

### Summary: Return Type Deduction + Structured Bindings

| Feature | C++11 | C++14 | C++17 | C++20 |
|---------|-------|-------|-------|-------|
| Single-return deduction | ✅ | ✅ | ✅ | ✅ |
| Multi-return deduction | ❌ | ✅ | ✅ | ✅ |
| Return `std::pair`/`std::tuple` | ✅ | ✅ | ✅ | ✅ |
| Structured binding unpack | ❌ | ❌ | ✅ | ✅ |
| Type-safe with concepts | ❌ | ❌ | ❌ | ✅ |

---

## �🔍 Practical Use Cases by Standard

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
