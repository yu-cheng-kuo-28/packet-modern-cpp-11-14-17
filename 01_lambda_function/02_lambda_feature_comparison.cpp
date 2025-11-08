#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <type_traits>

/**
 * Lambda Function Feature Comparison Across C++ Standards
 * 
 * This file demonstrates what's ILLEGAL vs LEGAL in each C++ version
 * and shows the evolution of lambda capabilities step by step.
 */

void demonstrate_cpp11_vs_cpp14_comparison() {
    std::cout << "=== C++11 vs C++14 Lambda Comparison ===\n\n";
    
    std::vector<int> data = {1, 2, 3, 4, 5};
    int multiplier = 2;
    
    std::cout << "--- C++11: What you CAN do ---\n";
    {
        // ✅ C++11: Basic capture modes
        auto lambda1 = [multiplier](int x) -> int { return x * multiplier; };        // Capture by value
        auto lambda2 = [&multiplier](int x) -> int { return x * multiplier; };       // Capture by reference  
        auto lambda3 = [=](int x) -> int { return x * multiplier; };                 // Capture all by value
        auto lambda4 = [&](int x) -> int { return x * multiplier; };                 // Capture all by reference
        
        // ✅ C++11: Explicit return types (required for complex cases)
        auto lambda5 = [](int x) -> double {                                         // Must specify -> double
            if (x > 0) return 3.14;
            return 2.71;
        };
        
        // ✅ C++11: Simple return type deduction (single return statement)
        auto lambda6 = [](int x) { return x * 2; };                                 // Can deduce int
        
        std::cout << "  Basic captures work: " << lambda1(5) << std::endl;
        std::cout << "  Explicit return types work: " << lambda5(1) << std::endl;
        // Silence unused-variable warnings for the examples we don't call below
        (void)lambda2; (void)lambda3; (void)lambda4; (void)lambda6;
    }
    
    std::cout << "\n--- C++11: What you CANNOT do (will cause compile errors) ---\n";
    {
        std::cout << "  // ❌ C++11: Init capture - ILLEGAL\n";
        std::cout << "  // auto lambda = [y = multiplier * 2](int x) { return x * y; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Move capture - ILLEGAL\n"; 
        std::cout << "  // auto lambda = [v = std::move(data)](int x) { return v[0] * x; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Auto parameters - ILLEGAL\n";
        std::cout << "  // auto lambda = [](auto x) { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Complex auto return type - ILLEGAL\n";
        std::cout << "  // auto lambda = [](bool flag) { if (flag) return 3.14; return 42; }; // ERROR!\n";
    }

#if __cplusplus >= 201402L
    std::cout << "\n--- C++14: NEW features that are now LEGAL ---\n";
    {
        // ✅ C++14: Generalized capture (init capture) - NEW!
        auto lambda1 = [y = multiplier * 2](int x) { return x * y; };               // ✅ NEW: Init capture
        auto lambda2 = [doubled = multiplier * 2, tripled = multiplier * 3](int x) { // ✅ NEW: Multiple init captures
            return x * doubled + tripled; 
        };
        
        // ✅ C++14: Move capture - NEW!
        auto data_copy = data;
        auto lambda3 = [v = std::move(data_copy)](int x) { return v[0] * x; };      // ✅ NEW: Move capture
        
        // ✅ C++14: Auto parameters (generic lambdas) - NEW!
        auto lambda4 = [](auto x) { return x * 2; };                                // ✅ NEW: Works with any type
        auto lambda5 = [](auto x, auto y) { return x + y; };                        // ✅ NEW: Multiple auto params
        
        // ✅ C++14: Auto return type deduction - NEW!
        auto lambda6 = [](bool flag) {                                               // ✅ NEW: No -> needed
            if (flag) return 3.14;   // double
            return 3.14;             // Must be same type, but auto deduced
        };
        
        // ✅ C++14: Complex generic operations - NEW!
        auto lambda7 = [](auto container, auto init, auto op) {                     // ✅ NEW: Generic algorithms
            return std::accumulate(container.begin(), container.end(), init, op);
        };
        
        std::cout << "  Init capture: " << lambda1(5) << std::endl;
        std::cout << "  Move capture: " << lambda3(3) << std::endl; 
        std::cout << "  Generic lambda (int): " << lambda4(5) << std::endl;
        std::cout << "  Generic lambda (double): " << lambda4(3.14) << std::endl;
        std::cout << "  Auto return: " << lambda6(true) << std::endl;
        
        auto sum_result = lambda7(data, 0, [](auto a, auto b) { return a + b; });
        std::cout << "  Generic algorithm: " << sum_result << std::endl;
        // Silence unused-variable warnings for demonstration-only lambdas
        (void)lambda2; (void)lambda5;
    }
#else
    std::cout << "\n--- C++14 features not available with current compiler settings ---\n";
#endif
}

void demonstrate_cpp14_vs_cpp17_comparison() {
    std::cout << "\n\n=== C++14 vs C++17 Lambda Comparison ===\n\n";
    
    std::vector<int> data = {1, 2, 3, 4, 5};
    
    std::cout << "--- C++14: What you can already do ---\n";
    {
#if __cplusplus >= 201402L
        // ✅ C++14: All previous features work
        auto lambda1 = [](auto x) { return x * x; };                                // Generic lambda
        auto lambda2 = [y = 42](auto x) { return x + y; };                         // Init capture
        
        std::cout << "  Generic lambda: " << lambda1(5) << std::endl;
        std::cout << "  Init capture: " << lambda2(3) << std::endl;
#else
        std::cout << "  C++14 features not available\n";
#endif
    }
    
    std::cout << "\n--- C++14: What you CANNOT do (will cause compile errors) ---\n";
    {
        std::cout << "  // ❌ C++14: Constexpr lambdas - ILLEGAL\n";
        std::cout << "  // constexpr auto lambda = [](auto x) constexpr { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++14: Structured bindings with lambdas - ILLEGAL\n";
        std::cout << "  // auto [min, max] = some_lambda_returning_pair(); // ERROR!\n";
    }

#if __cplusplus >= 201703L
    std::cout << "\n--- C++17: NEW features that are now LEGAL ---\n";
    {
        // ✅ C++17: Constexpr lambdas - NEW!
        constexpr auto lambda1 = [](auto x) constexpr { return x * x; };            // ✅ NEW: Constexpr lambda
        constexpr int compile_time_result = lambda1(5);                              // ✅ NEW: Compile-time computation
        
        // ✅ C++17: Constexpr can be used in constant expressions - NEW!
        constexpr auto square_if_even = [](int n) constexpr {                       // ✅ NEW: Complex constexpr
            return (n % 2 == 0) ? n * n : n;
        };
        constexpr int array_size = square_if_even(4);                                // ✅ NEW: Used for array size
        std::array<int, array_size> compile_time_array{};                            // Size = 16, known at compile-time
        
        // ✅ C++17: Lambdas in constant expressions - NEW!
        // Can use constexpr lambdas for array sizes, template parameters, etc.
        constexpr auto get_array_size = [](int base) constexpr { return base * base; };
        std::array<int, get_array_size(3)> const_array{};                           // Array size = 9, computed at compile-time
        
        // ✅ C++17: Structured bindings with algorithms - NEW!
        auto result_pair = std::minmax_element(data.begin(), data.end());           
        // auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());   // ✅ NEW: Structured bindings (C++17)
        auto min_val = *result_pair.first;
        auto max_val = *result_pair.second;
        
        // ✅ C++17: Constexpr lambdas in algorithms - NEW!
        auto transform_result = std::accumulate(data.begin(), data.end(), 0,
            [](auto sum, auto val) constexpr {                                      // ✅ NEW: Constexpr in algorithm
                return sum + val * val;
            });
        
        std::cout << "  Constexpr lambda result: " << compile_time_result << std::endl;
        std::cout << "  Array size from constexpr: " << compile_time_array.size() << std::endl;
        std::cout << "  Const array size from lambda: " << const_array.size() << std::endl;
        std::cout << "  Min/Max: " << min_val << "/" << max_val << std::endl;
        std::cout << "  Constexpr in algorithm: " << transform_result << std::endl;
    }
#else
    std::cout << "\n--- C++17 features not available with current compiler settings ---\n";
#endif
}

void demonstrate_cpp17_vs_cpp20_comparison() {
    std::cout << "\n\n=== C++17 vs C++20 Lambda Comparison ===\n\n";
    
    std::vector<int> data = {1, 2, 3, 4, 5, 6};
    
    std::cout << "--- C++17: What you can already do ---\n";
    {
#if __cplusplus >= 201703L
        // ✅ C++17: All previous features work
        constexpr auto lambda1 = [](auto x) constexpr { return x * 2; };           // Constexpr lambda
        auto lambda2 = [y = 42](auto x) { return x + y; };                         // Generic + init capture
        
        std::cout << "  Constexpr lambda: " << lambda1(5) << std::endl;
        std::cout << "  Generic + init: " << lambda2(3) << std::endl;
#else
        std::cout << "  C++17 features not available\n";
#endif
    }
    
    std::cout << "\n--- C++17: What you CANNOT do (will cause compile errors) ---\n";
    {
        std::cout << "  // ❌ C++17: Template parameters on lambdas - ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++17: Concepts with lambdas - ILLEGAL\n";
        std::cout << "  // auto lambda = [](auto x) requires std::integral<decltype(x)> { ... }; // ERROR!\n";
        
        std::cout << "  // ❌ C++17: Pack expansion in captures - ILLEGAL\n";
        std::cout << "  // auto lambda = [...args = std::move(args)](){ ... }; // ERROR!\n";
    }

#if __cplusplus >= 202002L
    std::cout << "\n--- C++20: NEW features that are now LEGAL ---\n";
    {
        // ✅ C++20: Template lambdas - NEW!
        auto lambda1 = []<typename T>(T x) { return x * x; };                       // ✅ NEW: Template parameter
        auto lambda2 = []<typename T, typename U>(T x, U y) { return x + y; };      // ✅ NEW: Multiple template params
        
        // ✅ C++20: Concepts with lambdas - NEW!
        auto lambda3 = []<typename T>(T x) requires std::is_arithmetic_v<T> {       // ✅ NEW: Requires clause
            return x * 2;
        };
        
        // ✅ C++20: Concepts in auto parameters - NEW!
        auto lambda4 = [](std::integral auto x) { return x + 1; };                 // ✅ NEW: Concept constraint
        
        // ✅ C++20: Advanced template lambda with concepts - NEW!
        auto generic_container_op = []<typename Container>                          // ✅ NEW: Complex template lambda
            (const Container& c, auto operation) 
            requires requires(typename Container::value_type v) { 
                { operation(v) } -> std::same_as<typename Container::value_type>; 
            }
        {
            Container result;
            std::transform(c.begin(), c.end(), std::back_inserter(result), operation);
            return result;
        };
        
        // ✅ C++20: Pack expansion in captures (advanced) - NEW!
        auto make_tuple_lambda = [](auto... args) {                                // ✅ NEW: Variadic lambda
            return std::make_tuple(args...);
        };
        
        std::cout << "  Template lambda (int): " << lambda1(5) << std::endl;
        std::cout << "  Template lambda (double): " << lambda1(3.14) << std::endl;
        std::cout << "  Multi-template: " << lambda2(5, 3.14) << std::endl;
        std::cout << "  Concept constrained: " << lambda3(42) << std::endl;
        std::cout << "  Integral concept: " << lambda4(10) << std::endl;
        
        auto squared_data = generic_container_op(data, [](auto x) { return x * x; });
        std::cout << "  Generic container op result size: " << squared_data.size() << std::endl;
        
        auto tuple_result = make_tuple_lambda(1, 2.5, "hello");
        std::cout << "  Variadic lambda tuple size: " << std::tuple_size_v<decltype(tuple_result)> << std::endl;
    }
#else
    std::cout << "\n--- C++20 features not available with current compiler settings ---\n";
#endif
}

void demonstrate_evolution_summary() {
    std::cout << "\n\n=== Lambda Evolution Summary ===\n\n";
    
    std::cout << "C++11 - The Foundation:\n";
    std::cout << "  ✅ Basic captures: [x], [&x], [=], [&]\n";
    std::cout << "  ✅ Explicit return types: [](int x) -> int\n";
    std::cout << "  ✅ Simple type-specific lambdas\n";
    std::cout << "  ❌ No auto parameters\n";
    std::cout << "  ❌ No init capture\n";
    std::cout << "  ❌ No move capture\n";
    std::cout << "  ❌ No auto return type deduction\n";
    std::cout << "  ❌ No constexpr\n\n";
    
    std::cout << "C++14 - Generic Power:\n";
    std::cout << "  ✅ All C++11 features\n";
    std::cout << "  ✅ NEW: Auto parameters: [](auto x)\n";
    std::cout << "  ✅ NEW: Init capture: [y = expr]\n";
    std::cout << "  ✅ NEW: Move capture: [v = std::move(x)]\n";
    std::cout << "  ✅ NEW: Auto return type deduction\n";
    std::cout << "  ❌ No constexpr lambdas\n\n";
    
    std::cout << "C++17 - Compile-time:\n";
    std::cout << "  ✅ All C++14 features\n";
    std::cout << "  ✅ NEW: Constexpr lambdas\n";
    std::cout << "  ✅ NEW: Lambdas in constant expressions\n";
    std::cout << "  ✅ NEW: Structured bindings (not lambda-specific)\n";
    std::cout << "  ❌ No template parameters\n\n";
    
    std::cout << "C++20 - Template Meta-programming:\n";
    std::cout << "  ✅ All C++17 features\n";
    std::cout << "  ✅ NEW: Template parameters: []<typename T>(T x)\n";
    std::cout << "  ✅ NEW: Concepts integration\n";
    std::cout << "  ✅ NEW: Pack expansion in captures\n";
    std::cout << "  ✅ NEW: Advanced type constraints\n\n";
}

int main() {
    std::cout << "Lambda Function Evolution: Feature-by-Feature Comparison\n";
    std::cout << "========================================================\n\n";
    
    demonstrate_cpp11_vs_cpp14_comparison();
    demonstrate_cpp14_vs_cpp17_comparison();
    demonstrate_cpp17_vs_cpp20_comparison();
    demonstrate_evolution_summary();
    
    return 0;
}