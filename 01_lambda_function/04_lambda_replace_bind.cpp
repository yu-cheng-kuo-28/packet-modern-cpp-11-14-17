#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

/**
 * 04_lambda_replace_bind.cpp
 * 
 * PURPOSE: Demonstrate why lambdas (C++11+, enhanced in C++14) replaced std::bind (C++11)
 * 
 * KEY TOPICS:
 * 1. What std::bind does: creates callable objects (function objects) with partial application
 * 2. Pre-C++11 alternatives (std::bind1st, std::bind2nd, manual functors)
 * 3. C++11: std::bind introduction
 * 4. C++14: Generic lambdas make std::bind nearly obsolete
 * 5. std::bind as polymorphic function wrapper (std::function relation)
 * 
 * Build: g++ -std=c++11 04_lambda_replace_bind.cpp -o 04_lambda_replace_bind_cpp11
 *        g++ -std=c++14 04_lambda_replace_bind.cpp -o 04_lambda_replace_bind_cpp14
 */

void section_header(const std::string &title) {
    std::cout << "\n=== " << title << " ===\n";
}

// Simple free function used in examples
void print_sum(int a, int b) {
    std::cout << "print_sum(" << a << ", " << b << ") = " << (a + b) << '\n';
}

void multiply_and_print(int a, int b, int c) {
    std::cout << "multiply_and_print(" << a << ", " << b << ", " << c << ") = " << (a * b * c) << '\n';
}

struct Foo {
    void bar(int x) { std::cout << "Foo::bar(" << x << ")\n"; }
    void process(int a, int b) { std::cout << "Foo::process(" << a << ", " << b << ") = " << (a + b) << '\n'; }
};

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    section_header("HISTORICAL CONTEXT: Before C++11");
    std::cout << "Before C++11, partial application required:\n";
    std::cout << "  - Manual functor classes (verbose)\n";
    std::cout << "  - std::bind1st / std::bind2nd (limited, deprecated in C++11, removed in C++17)\n";
    std::cout << "  - Boost.Bind library (popular but external dependency)\n\n";
    std::cout << "Example (conceptual - won't compile here):\n";
    std::cout << "  // C++03: Manual functor\n";
    std::cout << "  struct AddN {\n";
    std::cout << "      int n;\n";
    std::cout << "      AddN(int val) : n(val) {}\n";
    std::cout << "      int operator()(int x) const { return x + n; }\n";
    std::cout << "  };\n";
    std::cout << "  AddN add5(5);\n";
    std::cout << "  std::transform(v.begin(), v.end(), result.begin(), add5);\n";

    section_header("C++11: std::bind Introduction");
    std::cout << "std::bind creates a FUNCTION OBJECT (callable) by:\n";
    std::cout << "  1. Binding some arguments to fixed values (partial application)\n";
    std::cout << "  2. Using placeholders (_1, _2, ...) for arguments to be provided later\n";
    std::cout << "  3. Reordering arguments\n\n";
    std::cout << "Key insight: std::bind returns a function object, NOT a function pointer.\n";
    std::cout << "It creates a callable object that can be:\n";
    std::cout << "  - Stored in std::function (type-erased polymorphic wrapper)\n";
    std::cout << "  - Passed to algorithms\n";
    std::cout << "  - Called like a function\n\n";

    section_header("C++11 Example: Partial Application with std::bind");
    {
        std::cout << "--- Binding first argument of print_sum to 2 ---\n";
        
        // C++11: std::bind
        auto bound_cpp11 = std::bind(print_sum, 2, std::placeholders::_1);
        std::cout << "std::bind(print_sum, 2, _1): ";
        bound_cpp11(10);  // Equivalent to print_sum(2, 10)
        
        // C++11: Lambda equivalent (explicit types)
        auto lambda_cpp11 = [](int x) -> void { print_sum(2, x); };
        std::cout << "C++11 lambda [](int x): ";
        lambda_cpp11(10);
        
        std::cout << "\nNote: Both create function objects, but lambda is clearer.\n";
    }

    section_header("C++11 Example: Binding Multiple Arguments");
    {
        std::cout << "--- Binding multiple arguments ---\n";
        
        // Bind first two arguments, leave third as placeholder
        auto bound = std::bind(multiply_and_print, 2, 3, std::placeholders::_1);
        std::cout << "std::bind(multiply_and_print, 2, 3, _1): ";
        bound(5);  // multiply_and_print(2, 3, 5) = 30
        
        // Lambda equivalent
        auto lambda = [](int c) { multiply_and_print(2, 3, c); };
        std::cout << "Lambda equivalent: ";
        lambda(5);
    }

    section_header("C++11 Example: Member Functions with std::bind");
    {
        std::cout << "--- Binding member functions ---\n";
        Foo foo;
        std::vector<int> v = {1, 2, 3};
        
        // std::bind for member function
        std::cout << "std::bind(&Foo::bar, &foo, _1):\n  ";
        std::for_each(v.begin(), v.end(), std::bind(&Foo::bar, &foo, std::placeholders::_1));
        
        // C++11 lambda equivalent
        std::cout << "C++11 lambda [&foo](int x):\n  ";
        std::for_each(v.begin(), v.end(), [&foo](int x){ foo.bar(x); });
    }

    section_header("std::bind and std::function: Polymorphism Concept");
    {
        std::cout << "std::bind returns a function object with SPECIFIC type (implementation-defined).\n";
        std::cout << "std::function provides TYPE ERASURE - polymorphic wrapper for ANY callable.\n\n";
        
        std::cout << "Example: storing different callables in std::function\n\n";
        
        // Different ways to create callables
        auto bound_add = std::bind(add, 10, std::placeholders::_1);
        auto lambda_subtract = [](int x){ return subtract(20, x); };
        
        // Store in std::function (polymorphic wrapper)
        std::function<int(int)> operation1 = bound_add;
        std::function<int(int)> operation2 = lambda_subtract;
        
        std::cout << "operation1 (bound std::bind): 10 + 5 = " << operation1(5) << '\n';
        std::cout << "operation2 (lambda): 20 - 5 = " << operation2(5) << '\n';
        
        std::cout << "\nKey point: std::function allows RUNTIME polymorphism of callables.\n";
        std::cout << "Both std::bind results and lambdas can be stored in std::function.\n";
        std::cout << "This is NOT about function pointers - it's about callable objects.\n";
    }

    section_header("C++11: Argument Reordering with std::bind");
    {
        std::cout << "--- std::bind can reorder arguments ---\n";
        
        // Reverse argument order using std::bind
        auto reversed = std::bind(print_sum, std::placeholders::_2, std::placeholders::_1);
        std::cout << "Original call print_sum(10, 20): "; print_sum(10, 20);
        std::cout << "Reversed bind(_2, _1)(10, 20): "; reversed(10, 20);  // Calls print_sum(20, 10)
        
        // Lambda equivalent (C++11)
        auto lambda_reversed = [](int x, int y) { print_sum(y, x); };
        std::cout << "Lambda equivalent: "; lambda_reversed(10, 20);
    }

#if __cplusplus >= 201402L
    section_header("C++14: Generic Lambdas Make std::bind Nearly Obsolete");
    std::cout << "C++14 introduced GENERIC LAMBDAS with auto parameters.\n";
    std::cout << "This makes lambdas more flexible than std::bind for most use cases.\n\n";
    
    {
        std::cout << "--- C++14: Generic lambda vs std::bind ---\n";
        
        // std::bind (still C++11 style)
        auto bound_generic = std::bind(add, 10, std::placeholders::_1);
        
        // C++14: Generic lambda (works with any type)
        auto lambda_generic = [](auto x){ return add(10, x); };
        
        std::cout << "std::bind result: 10 + 5 = " << bound_generic(5) << '\n';
        std::cout << "C++14 generic lambda: 10 + 5 = " << lambda_generic(5) << '\n';
        
        std::cout << "\nC++14 lambda advantages:\n";
        std::cout << "  ✅ Auto parameters - generic without templates\n";
        std::cout << "  ✅ Auto return type deduction\n";
        std::cout << "  ✅ Init capture (move semantics)\n";
        std::cout << "  ✅ Clearer syntax\n";
    }
    
    {
        std::cout << "\n--- C++14: Init capture (impossible with std::bind) ---\n";
        std::vector<int> data = {1, 2, 3, 4, 5};
        
        // C++14: Move capture into lambda
        auto lambda_with_move = [v = std::move(data)](int multiplier) {
            int sum = 0;
            for (int x : v) sum += x * multiplier;
            return sum;
        };
        
        std::cout << "Lambda with move capture: sum * 2 = " << lambda_with_move(2) << '\n';
        std::cout << "Original vector is now empty: size = " << data.size() << '\n';
        std::cout << "\nstd::bind CANNOT do this - it only captures by copy or reference.\n";
    }
#else
    section_header("C++14 Features Not Available");
    std::cout << "Compile with -std=c++14 or later to see generic lambda advantages.\n";
#endif

    section_header("Why std::bind Is Rarely Used in Modern C++ (C++14+)");
    std::cout << "Reasons to prefer lambdas over std::bind:\n\n";
    std::cout << "1. READABILITY\n";
    std::cout << "   - std::bind: Placeholders (_1, _2) are cryptic\n";
    std::cout << "   - Lambda: Parameters are explicit and clear\n\n";
    std::cout << "2. TYPE SAFETY\n";
    std::cout << "   - std::bind: Complex template types, hard to debug\n";
    std::cout << "   - Lambda: Compiler-friendly types, better error messages\n\n";
    std::cout << "3. OVERLOAD RESOLUTION\n";
    std::cout << "   - std::bind: May bind wrong overload, requires explicit casts\n";
    std::cout << "   - Lambda: Normal overload resolution rules apply\n\n";
    std::cout << "4. PERFORMANCE\n";
    std::cout << "   - std::bind: Extra template machinery, harder to optimize\n";
    std::cout << "   - Lambda: Direct inline code, easier for compiler to optimize\n\n";
    std::cout << "5. MODERN FEATURES (C++14+)\n";
    std::cout << "   - std::bind: No init capture, no move semantics, no constexpr\n";
    std::cout << "   - Lambda: Full support for init capture, move, constexpr, etc.\n";

    section_header("Comparison Summary: std::bind vs Lambda");
    std::cout << "┌─────────────────────────────┬────────────────────┬─────────────────────┐\n";
    std::cout << "│ Feature                     │ std::bind (C++11)  │ Lambda (C++11/14+)  │\n";
    std::cout << "├─────────────────────────────┼────────────────────┼─────────────────────┤\n";
    std::cout << "│ Introduced                  │ C++11              │ C++11               │\n";
    std::cout << "│ Readability                 │ ❌ Poor            │ ✅ Excellent        │\n";
    std::cout << "│ Partial application         │ ✅ Yes             │ ✅ Yes              │\n";
    std::cout << "│ Argument reordering         │ ✅ Yes             │ ✅ Yes (explicit)   │\n";
    std::cout << "│ Generic parameters          │ ❌ No              │ ✅ Yes (C++14)      │\n";
    std::cout << "│ Init capture / move         │ ❌ No              │ ✅ Yes (C++14)      │\n";
    std::cout << "│ Overload safety             │ ❌ Fragile         │ ✅ Safe             │\n";
    std::cout << "│ constexpr support           │ ❌ No              │ ✅ Yes (C++17)      │\n";
    std::cout << "│ Modern status               │ ⚠️ Legacy           │ ✅ Preferred        │\n";
    std::cout << "└─────────────────────────────┴────────────────────┴─────────────────────┘\n";

    section_header("Clarification: std::bind vs Function Pointers vs Polymorphism");
    std::cout << "IMPORTANT DISTINCTIONS:\n\n";
    std::cout << "1. FUNCTION POINTER:\n";
    std::cout << "   - Points to a specific function in memory\n";
    std::cout << "   - Type: void(*)(int) or int(*)(int, int)\n";
    std::cout << "   - Cannot capture state or bind arguments\n";
    std::cout << "   - Example: void (*ptr)(int) = &print_sum;  // ERROR: wrong signature\n\n";
    std::cout << "2. FUNCTION OBJECT (FUNCTOR):\n";
    std::cout << "   - Object with operator() defined\n";
    std::cout << "   - Can capture state (member variables)\n";
    std::cout << "   - std::bind returns a function object\n";
    std::cout << "   - Lambdas are function objects (compiler-generated class)\n\n";
    std::cout << "3. std::function (POLYMORPHIC WRAPPER):\n";
    std::cout << "   - Type-erased wrapper for ANY callable (function, lambda, bind result, functor)\n";
    std::cout << "   - Provides runtime polymorphism via type erasure\n";
    std::cout << "   - Slight overhead (virtual dispatch-like behavior)\n";
    std::cout << "   - Example: std::function<int(int)> can hold lambda OR bind result\n\n";
    std::cout << "KEY INSIGHT:\n";
    std::cout << "  std::bind creates a FUNCTION OBJECT (not a pointer).\n";
    std::cout << "  Polymorphism comes from std::function, not from std::bind itself.\n";
    std::cout << "  Both std::bind and lambdas create callable objects that can be stored in std::function.\n";

    section_header("Example: Function Pointer vs Function Object vs std::function");
    {
        // Function pointer (traditional C)
        int (*func_ptr)(int, int) = &add;
        std::cout << "Function pointer: add(3, 4) = " << func_ptr(3, 4) << '\n';
        
        // Function object from std::bind
        auto bind_obj = std::bind(add, 10, std::placeholders::_1);
        std::cout << "std::bind object: bind(add, 10, _1)(5) = " << bind_obj(5) << '\n';
        
        // Function object from lambda
        auto lambda_obj = [](int x){ return add(10, x); };
        std::cout << "Lambda object: lambda(5) = " << lambda_obj(5) << '\n';
        
        // std::function can hold any of these (polymorphic wrapper)
        std::function<int(int)> poly_func = bind_obj;
        std::cout << "std::function(bind): " << poly_func(5) << '\n';
        
        poly_func = lambda_obj;
        std::cout << "std::function(lambda): " << poly_func(5) << '\n';
        
        std::cout << "\nNote: std::function adds type erasure (runtime polymorphism).\n";
    }

    section_header("Final Recommendation");
    std::cout << "✅ Use lambdas (C++11 basic, C++14 generic) for new code\n";
    std::cout << "✅ Use std::function when you need polymorphic storage of different callables\n";
    std::cout << "⚠️  Use std::bind only for maintaining legacy C++11 code\n";
    std::cout << "❌ Avoid raw function pointers unless interfacing with C APIs\n\n";
    std::cout << "Modern C++ idiom (C++14+):\n";
    std::cout << "  auto my_callable = [captured_state](auto x) { return captured_state + x; };\n";
    std::cout << "  std::function<int(int)> poly_callable = my_callable;  // If polymorphism needed\n";

    return 0;
}
