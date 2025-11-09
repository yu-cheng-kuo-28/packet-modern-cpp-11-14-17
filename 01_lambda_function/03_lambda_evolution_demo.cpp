#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

/**
 * EDUCATIONAL FOCUS: Practical Lambda Applications
 * Real-world example: Data processing pipeline
 * Shows how lambda evolution makes code more elegant and powerful
 */

void demonstrate_practical_evolution() {
    std::vector<int> data = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    
    std::cout << "=== PRACTICAL: Lambda Evolution in Data Processing ===\n";
    std::cout << "Task: Process data pipeline (filter → transform → reduce)\n";
    std::cout << "Input: {1, -2, 3, -4, 5, -6, 7, -8, 9, -10}\n\n";

    // ===== C++11: Verbose but Clear =====
    std::cout << "=== C++11 Approach (Verbose) ===\n";
    std::cout << "\n--- C++11: What you CAN do ---\n";
    {
        // ✅ Separate lambdas for each operation (explicit types required)
        auto is_positive = [](int x) -> bool { return x > 0; };
        auto square = [](int x) -> int { return x * x; };
        auto add = [](int a, int b) -> int { return a + b; };
        
        // ✅ Single-return deduction works, but multi-return needs explicit type
        auto abs_value = [](int x) { return x > 0 ? x : -x; };  // Single return - OK
        // auto abs_value2 = [](int x) { if (x > 0) return x; return -x; }; // ❌ ERROR! Need -> int
        auto abs_value2 = [](int x) -> int {  // Explicit type required for multiple returns
            if (x > 0) return x;
            return -x;
        };
        
        // Multi-step process
        std::vector<int> positives;
        std::copy_if(data.begin(), data.end(), std::back_inserter(positives), is_positive);
        
        std::vector<int> squared;
        std::transform(positives.begin(), positives.end(), std::back_inserter(squared), square);
        
        int sum = std::accumulate(squared.begin(), squared.end(), 0, add);
        
        std::cout << "  Pipeline: filter positives → square → sum\n";
        std::cout << "  Positive numbers: ";
        for (int n : positives) std::cout << n << " ";
        std::cout << "\n  Squared: ";
        for (int n : squared) std::cout << n << " ";
        std::cout << "\n  Sum: " << sum << std::endl;
        std::cout << "  Abs value demo: " << abs_value(-5) << ", " << abs_value2(-5) << std::endl;
        std::cout << "  ✅ Explicit types work\n";
        std::cout << "  ✅ Single-return type deduction works\n";
        std::cout << "  ✅ Multiple-return needs explicit -> T\n";
        std::cout << "  ✅ Separate steps work\n";
    }
    
    std::cout << "\n--- C++11: What you CANNOT do ---\n";
    {
        std::cout << "  // ❌ C++11: Multiple return without explicit type - ILLEGAL\n";
        std::cout << "  // auto abs = [](int x) { if (x > 0) return x; return -x; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Generic lambdas - ILLEGAL\n";
        std::cout << "  // auto is_positive = [](auto x) { return x > 0; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Init capture - ILLEGAL\n";
        std::cout << "  // auto processor = [factor = 2](int x) { return x * factor; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Constexpr - ILLEGAL\n";
        std::cout << "  // constexpr auto square = [](int x) constexpr { return x * x; }; // ERROR!\n";
    }
    std::cout << "\n";

#if __cplusplus >= 201402L
    // ===== C++14: Generic Lambdas and Init Capture =====
    std::cout << "=== C++14 Approach (Generic & Flexible) ===\n";
    std::cout << "\n--- C++14: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Generic lambdas can work with different types
        auto is_positive = [](auto x) { return x > 0; };
        auto square = [](auto x) { return x * x; };
        
        // ✅ NEW: Multiple return type deduction (C++11 limitation removed!)
        auto abs_value = [](auto x) {  // No explicit -> T needed anymore!
            if (x > 0) return x;
            return -x;  // Multiple returns now work with auto deduction
        };
        
        // Single-pass processing with generic lambda
        auto result = std::accumulate(data.begin(), data.end(), 0,
            [is_positive, square](auto sum, auto value) {
                return is_positive(value) ? sum + square(value) : sum;
            });
        
        // ✅ NEW: Demonstrate init capture
        auto transform_and_sum = [factor = 2](const auto& vec) {
            return std::accumulate(vec.begin(), vec.end(), 0,
                [factor](auto acc, auto val) {
                    return acc + (val > 0 ? val * factor : 0);
                });
        };
        
        auto transformed_result = transform_and_sum(data);
        
        std::cout << "  Pipeline: combined filter + transform + reduce\n";
        std::cout << "  Sum of squared positives: " << result << std::endl;
        std::cout << "  Sum of doubled positives: " << transformed_result << std::endl;
        std::cout << "  Abs value (multi-return deduction): " << abs_value(-7) << std::endl;
        std::cout << "  ✅ NEW: Generic lambdas with auto parameters\n";
        std::cout << "  ✅ NEW: Multiple-return type deduction (C++11 fix!)\n";
        std::cout << "  ✅ NEW: Init capture for inline variables\n";
        std::cout << "  ✅ NEW: Auto return type deduction\n";
    }
    
    std::cout << "\n--- C++14: What you STILL CANNOT do ---\n";
    {
        std::cout << "  // ❌ C++14: Constexpr lambdas - STILL ILLEGAL\n";
        std::cout << "  // constexpr auto square = [](auto x) constexpr { return x * x; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++14: Structured bindings - STILL ILLEGAL (C++17 feature)\n";
        std::cout << "  // auto [min, max] = some_lambda_returning_pair(); // ERROR!\n";
        
        std::cout << "  // ❌ C++14: Template parameters - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * x; }; // ERROR!\n";
    }
    std::cout << "\n";
#else
    std::cout << "=== C++14 Features Not Available ===\n";
    std::cout << "Compile with -std=c++14 or later to see generic lambda features.\n\n";
#endif

#if __cplusplus >= 201703L
    // ===== C++17: Constexpr Optimization =====
    std::cout << "=== C++17 Approach (Constexpr & Performance) ===\n";
    std::cout << "\n--- C++17: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Constexpr lambdas for compile-time optimization
        constexpr auto process_value = [](auto value) constexpr {
            return (value > 0) ? value * value : 0;
        };
        
        // ✅ NEW: Structured bindings with lambda returns
        auto get_stats = [](const std::vector<int>& vec) {
            int pos_count = 0, neg_count = 0;
            for (auto v : vec) {
                if (v > 0) ++pos_count;
                else if (v < 0) ++neg_count;
            }
            return std::make_pair(pos_count, neg_count);
        };
        auto [positives, negatives] = get_stats(data);  // ✅ NEW: Structured binding!
        
        auto result = std::accumulate(data.begin(), data.end(), 0,
            [process_value](auto sum, auto value) constexpr {
                return sum + process_value(value);
            });
        
        // Compile-time demonstration
        constexpr int compile_time_result = process_value(5);
        
        std::cout << "  Pipeline: constexpr processing for optimization\n";
        std::cout << "  Sum of squared positives: " << result << std::endl;
        std::cout << "  Compile-time demo: process_value(5) = " << compile_time_result << std::endl;
        std::cout << "  Structured binding: " << positives << " positives, " << negatives << " negatives\n";
        std::cout << "  ✅ NEW: Constexpr lambdas\n";
        std::cout << "  ✅ NEW: Compile-time computation\n";
        std::cout << "  ✅ NEW: Structured bindings with lambda returns\n";
        std::cout << "  ✅ NEW: Performance optimizations\n";
    }
    
    std::cout << "\n--- C++17: What you STILL CANNOT do ---\n";
    {
        std::cout << "  // ❌ C++17: Template parameters - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * x; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++17: Concepts - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) requires std::is_arithmetic_v<T> { ... }; // ERROR!\n";
    }
    std::cout << "\n";
#else
    std::cout << "=== C++17 Features Not Available ===\n";
    std::cout << "Compile with -std=c++17 or later to see constexpr lambda features.\n\n";
#endif

#if __cplusplus >= 202002L
    // ===== C++20: Type Safety - Templates and Concepts =====
    std::cout << "=== C++20 Approach (Type-Safe & Advanced) ===\n";
    std::cout << "\n--- C++20: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Template lambda with concepts for type safety
        auto safe_processor = []<typename T>(const std::vector<T>& vec, auto predicate, auto transformer)
            requires std::is_arithmetic_v<T>
        {
            T result = T{};
            for (const auto& item : vec) {
                if (predicate(item)) {
                    result += transformer(item);
                }
            }
            return result;
        };
        
        // ✅ NEW: Concept-constrained lambdas
        auto is_positive = []<typename T>(T x) requires std::is_arithmetic_v<T> { 
            return x > 0; 
        };
        auto square = []<typename T>(T x) requires std::is_arithmetic_v<T> { 
            return x * x; 
        };
        
        auto result = safe_processor(data, is_positive, square);
        
        std::cout << "  Pipeline: type-safe template lambda with concepts\n";
        std::cout << "  Sum of squared positives: " << result << std::endl;
        std::cout << "  ✅ NEW: Template lambdas\n";
        std::cout << "  ✅ NEW: Concepts integration\n";
        std::cout << "  ✅ NEW: Type safety guarantees\n";
        
        std::cout << "\n  // This would cause a compile error:\n";
        std::cout << "  // safe_processor(std::vector<std::string>{\"a\"}, pred, trans); // ❌ ERROR: string not arithmetic\n";
    }
    std::cout << "\n";
#else
    std::cout << "=== C++20 Features Not Available ===\n";
    std::cout << "Compile with -std=c++20 or later to see template lambda features.\n\n";
#endif
}

int main() {
    std::cout << "Lambda Evolution: Practical Applications\n";
    std::cout << "=====================================\n\n";
    
    demonstrate_practical_evolution();
    
    std::cout << "\n=== Lambda Evolution Summary ===\n\n";
    std::cout << "C++11 - The Foundation:\n";
    std::cout << "  ✅ Basic lambdas with explicit types\n";
    std::cout << "  ✅ Simple captures\n";
    std::cout << "  ✅ Single-return type deduction\n";
    std::cout << "  ❌ No multiple-return type deduction\n";
    std::cout << "  ❌ No generic lambdas\n";
    std::cout << "  ❌ No init capture\n";
    std::cout << "  ❌ No constexpr\n";
    std::cout << "  ❌ No templates\n\n";
#if __cplusplus >= 201402L
    std::cout << "C++14 - Generic Power:\n";
    std::cout << "  ✅ All C++11 features\n";
    std::cout << "  ✅ NEW: Generic lambdas (auto params)\n";
    std::cout << "  ✅ NEW: Multiple-return type deduction\n";
    std::cout << "  ✅ NEW: Init captures\n";
    std::cout << "  ❌ No constexpr\n";
    std::cout << "  ❌ No structured bindings\n";
    std::cout << "  ❌ No templates\n\n";
#endif
#if __cplusplus >= 201703L
    std::cout << "C++17 - Compile-time:\n";
    std::cout << "  ✅ All C++14 features\n";
    std::cout << "  ✅ NEW: Constexpr lambdas\n";
    std::cout << "  ✅ NEW: Structured bindings with lambda returns\n";
    std::cout << "  ✅ NEW: Enhanced algorithms\n";
    std::cout << "  ❌ No template parameters\n";
    std::cout << "  ❌ No concepts\n\n";
#endif
#if __cplusplus >= 202002L
    std::cout << "C++20 - Template Meta-programming:\n";
    std::cout << "  ✅ All C++17 features\n";
    std::cout << "  ✅ NEW: Template lambdas\n";
    std::cout << "  ✅ NEW: Concepts integration\n";
    std::cout << "  ✅ NEW: Pack expansion\n";
    std::cout << "  ✅ NEW: Advanced type constraints\n\n";
#endif
    
    std::cout << "Conclusion: Each C++ version makes lambdas more powerful and elegant!\n";
    
    return 0;
}