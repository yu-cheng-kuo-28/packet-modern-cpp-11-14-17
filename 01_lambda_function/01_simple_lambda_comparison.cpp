#include <iostream>
#include <vector>

/**
 * EDUCATIONAL FOCUS: Pure Lambda Evolution (No Complex STL)
 * Simple Task: Double all numbers in a vector
 * Shows ONLY lambda syntax evolution, nothing else
 */

void demonstrate_lambda_evolution() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "=== EDUCATIONAL: Lambda Evolution Demo ===\n";
    std::cout << "Task: Apply a function to each number (simple doubling)\n";
    std::cout << "Input: {1, 2, 3, 4, 5}\n\n";
    
    // ===== C++11: The Foundation =====
    std::cout << "=== C++11 Lambda (The Beginning) ===\n";
    std::cout << "\n--- C++11: What you CAN do ---\n";
    {
        // ✅ Must specify types explicitly
        auto doubler = [](int x) -> int {    // ← Explicit parameter type + return type
            return x * 2;
        };
        
        // ✅ Must specify capture explicitly
        int multiplier = 3;
        auto tripler = [multiplier](int x) -> int {  // ← Explicit capture by value
            return x * multiplier;
        };
        
        // Apply to each element (simple loop - no confusing STL)
        std::cout << "  Doubled: ";
        for (int n : numbers) {
            std::cout << doubler(n) << " ";
        }
        std::cout << "\n  Tripled: ";
        for (int n : numbers) {
            std::cout << tripler(n) << " ";
        }
        std::cout << "\n";
        std::cout << "  ✅ Explicit types work\n";
        std::cout << "  ✅ Basic capture by value works\n";
    }
    
    std::cout << "\n--- C++11: What you CANNOT do (will cause compile errors) ---\n";
    {
        std::cout << "  // ❌ C++11: Auto parameters - ILLEGAL\n";
        std::cout << "  // auto lambda = [](auto x) { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Init capture - ILLEGAL\n";
        std::cout << "  // auto lambda = [multiplier = 4](int x) { return x * multiplier; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Constexpr lambdas - ILLEGAL\n";
        std::cout << "  // constexpr auto lambda = [](int x) constexpr { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++11: Template parameters - ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * 2; }; // ERROR!\n";
    }
    std::cout << "\n";
    
#if __cplusplus >= 201402L
    // ===== C++14: The Game Changer =====
    std::cout << "=== C++14 Lambda (Generic Power) ===\n";
    std::cout << "\n--- C++14: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Auto parameters (works with any type!)
        auto doubler = [](auto x) {          // ← AUTO parameter (works with int, double, etc.)
            return x * 2;                    // ← AUTO return type deduction
        };
        
        // ✅ NEW: Generalized capture (init capture)
        auto processor = [multiplier = 4](auto x) {  // ← NEW: Create variable in capture
            return x * multiplier;
        };
        
        // Works with different types now!
        std::cout << "  Doubled (int): ";
        for (int n : numbers) {
            std::cout << doubler(n) << " ";
        }
        std::cout << "\n  Doubled (double): ";
        for (double d : {1.5, 2.5, 3.5}) {
            std::cout << doubler(d) << " ";  // Same lambda works with double!
        }
        std::cout << "\n  Processed: ";
        for (int n : numbers) {
            std::cout << processor(n) << " ";
        }
        std::cout << "\n";
        std::cout << "  ✅ NEW: Auto parameters work with any type\n";
        std::cout << "  ✅ NEW: Auto return type deduction\n";
        std::cout << "  ✅ NEW: Init capture creates variables\n";
    }
    
    std::cout << "\n--- C++14: What you STILL CANNOT do ---\n";
    {
        std::cout << "  // ❌ C++14: Constexpr lambdas - STILL ILLEGAL\n";
        std::cout << "  // constexpr auto lambda = [](auto x) constexpr { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++14: Template parameters - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++14: Concepts - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = [](auto x) requires std::is_arithmetic_v<decltype(x)> { ... }; // ERROR!\n";
    }
    std::cout << "\n";
#else
    std::cout << "=== C++14 Lambda ===\n";
    std::cout << "C++14 features not available with current compiler settings.\n\n";
#endif
    
#if __cplusplus >= 201703L
    // ===== C++17: Compile-Time Power =====
    std::cout << "=== C++17 Lambda (Constexpr Magic) ===\n";
    std::cout << "\n--- C++17: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Constexpr lambdas (compile-time computation)
        constexpr auto doubler = [](auto x) constexpr {  // ← NEW: constexpr lambda
            return x * 2;
        };
        
        // This can be computed at compile time!
        constexpr int compile_time_result = doubler(5);  // Computed during compilation!
        
        std::cout << "  Runtime doubled: ";
        for (int n : numbers) {
            std::cout << doubler(n) << " ";
        }
        std::cout << "\n  Compile-time doubled: " << compile_time_result;
        std::cout << " (computed during compilation!)\n";
        std::cout << "  ✅ NEW: Constexpr lambdas enable compile-time computation\n";
        std::cout << "  ✅ NEW: Can use in constant expressions\n";
    }
    
    std::cout << "\n--- C++17: What you STILL CANNOT do ---\n";
    {
        std::cout << "  // ❌ C++17: Template parameters - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = []<typename T>(T x) { return x * 2; }; // ERROR!\n";
        
        std::cout << "  // ❌ C++17: Concepts - STILL ILLEGAL\n";
        std::cout << "  // auto lambda = [](auto x) requires std::is_arithmetic_v<decltype(x)> { ... }; // ERROR!\n";
    }
    std::cout << "\n";
#endif


#if __cplusplus >= 202002L
    // ===== C++20: Template Power =====
    std::cout << "=== C++20 Lambda (Template + Concepts) ===\n";
    std::cout << "\n--- C++20: NEW features that are now LEGAL ---\n";
    {
        // ✅ NEW: Template parameters with concepts
        auto safe_doubler = []<typename T>(T x) requires std::is_arithmetic_v<T> {
            return x * 2;
        };
        
        std::cout << "  Type-safe doubled: ";
        for (int n : numbers) {
            std::cout << safe_doubler(n) << " ";
        }
        std::cout << "\n";
        std::cout << "  ✅ NEW: Template parameters on lambdas\n";
        std::cout << "  ✅ NEW: Concepts for type constraints\n";
        std::cout << "  ✅ NEW: Compile-time type safety\n";
        
        std::cout << "\n  // This would cause a compile error:\n";
        std::cout << "  // safe_doubler(std::string(\"hello\"));  // ❌ ERROR: string is not arithmetic\n";
    }
    std::cout << "\n";
#endif

    // ===== SUMMARY: What Each Version Brought =====
    std::cout << "=== Lambda Evolution Summary ===\n\n";
    std::cout << "C++11 - The Foundation:\n";
    std::cout << "  ✅ Explicit types and return types\n";
    std::cout << "  ✅ Basic capture: [x], [&x], [=], [&]\n";
    std::cout << "  ❌ No auto parameters\n";
    std::cout << "  ❌ No init capture\n";
    std::cout << "  ❌ No constexpr\n";
    std::cout << "  ❌ No templates\n\n";
#if __cplusplus >= 201402L
    std::cout << "C++14 - Generic Power:\n";
    std::cout << "  ✅ All C++11 features\n";
    std::cout << "  ✅ NEW: Auto parameters (generic lambdas)\n";
    std::cout << "  ✅ NEW: Auto return type deduction\n";
    std::cout << "  ✅ NEW: Init capture\n";
    std::cout << "  ❌ No constexpr\n";
    std::cout << "  ❌ No templates\n\n";
#endif
#if __cplusplus >= 201703L  
    std::cout << "C++17 - Compile-time:\n";
    std::cout << "  ✅ All C++14 features\n";
    std::cout << "  ✅ NEW: Constexpr lambdas\n";
    std::cout << "  ✅ NEW: Compile-time computation\n";
    std::cout << "  ❌ No template parameters\n";
    std::cout << "  ❌ No concepts\n\n";
#endif
#if __cplusplus >= 202002L
    std::cout << "C++20 - Template Meta-programming:\n";
    std::cout << "  ✅ All C++17 features\n";
    std::cout << "  ✅ NEW: Template parameters\n";
    std::cout << "  ✅ NEW: Concepts integration\n";
    std::cout << "  ✅ NEW: Full type safety\n\n";
#endif
}

int main() {
    std::cout << "Lambda Evolution: Pure Syntax Progression\n";
    std::cout << "========================================\n\n";
    
    demonstrate_lambda_evolution();
    
    return 0;
}