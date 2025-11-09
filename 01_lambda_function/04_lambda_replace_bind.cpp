#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

/**
 * 04_lambda_replace_bind.cpp
 * 
 * PURPOSE: Demonstrate the evolution from Functors → std::bind → Lambdas
 * 
 * EVOLUTION TIMELINE:
 * 1. Pre-C++11: Manual Functors (verbose but necessary)
 * 2. C++11: std::bind (automated functor generation, but confusing)
 * 3. C++11: Basic Lambdas (clean, but limited)
 * 4. C++14: Generic Lambdas (complete replacement for std::bind)
 * 5. C++20: std::bind_front (simple partial application)
 * 
 * KEY INSIGHT: All three approaches compile to the same machine code!
 * The evolution is about SYNTAX, CLARITY, and TYPE SAFETY.
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

// Pre-C++11 style: Manual Functor
struct Multiplier {
    int factor;
    explicit Multiplier(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

struct Foo {
    void bar(int x) { std::cout << "Foo::bar(" << x << ")\n"; }
    void process(const std::string& data) { 
        std::cout << "Foo::process(\"" << data << "\")\n"; 
    }
};

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    section_header("THE EVOLUTION: Functors → std::bind → Lambdas");
    std::cout << "This demonstration shows THREE stages of callable object evolution:\n";
    std::cout << "  1. Pre-C++11: Manual Functors (struct with operator())\n";
    std::cout << "  2. C++11:     std::bind (automated functor generation)\n";
    std::cout << "  3. C++14+:    Lambdas (inline, type-safe, clear)\n\n";
    std::cout << "KEY CONCEPT: A lambda IS a functor!\n";
    std::cout << "The compiler generates the struct and operator() for you.\n\n";

    section_header("ACT I: The Functor Era (Pre-C++11)");
    std::cout << "WHAT IS A FUNCTOR?\n";
    std::cout << "A functor (function object) is any object that overloads operator().\n";
    std::cout << "It lets you store STATE and behave like a function.\n\n";
    
    std::cout << "--- Example: Manual Functor ---\n";
    std::cout << "Code:\n";
    std::cout << "  struct Multiplier {\n";
    std::cout << "      int factor;\n";
    std::cout << "      explicit Multiplier(int f) : factor(f) {}\n";
    std::cout << "      int operator()(int x) const { return x * factor; }\n";
    std::cout << "  };\n\n";
    
    {
        Multiplier times2(2);
        Multiplier times3(3);
        
        std::cout << "Usage:\n";
        std::cout << "  Multiplier times2(2);\n";
        std::cout << "  times2(10) = " << times2(10) << "  // Calls operator()(10)\n";
        std::cout << "  times2(5)  = " << times2(5) << "\n\n";
        
        std::vector<int> nums = {1, 2, 3, 4, 5};
        std::vector<int> result(5);
        std::transform(nums.begin(), nums.end(), result.begin(), Multiplier(2));
        
        std::cout << "With STL algorithm:\n";
        std::cout << "  std::transform(v.begin(), v.end(), result.begin(), Multiplier(2));\n";
        std::cout << "  Result: ";
        for (int n : result) std::cout << n << " ";
        std::cout << "\n\n";
    }
    
    std::cout << "PROBLEMS WITH MANUAL FUNCTORS:\n";
    std::cout << "  ❌ Boilerplate hell (7+ lines for simple multiply)\n";
    std::cout << "  ❌ Scope pollution (named types everywhere)\n";
    std::cout << "  ❌ Poor readability (intent hidden in implementation)\n\n";

    section_header("ACT II: The std::bind Era (C++11)");
    std::cout << "WHAT IS std::bind?\n";
    std::cout << "std::bind is a FUNCTOR GENERATOR - it creates function objects automatically!\n";
    std::cout << "Instead of writing a struct with operator(), std::bind does it for you.\n\n";
    
    std::cout << "Comparison:\n";
    std::cout << "  Pre-C++11:  struct Multiplier { int factor; ... operator()... };  // 7 lines\n";
    std::cout << "  C++11:      auto times2 = std::bind(std::multiplies<int>(), _1, 2);  // 1 line!\n\n";
    
    std::cout << "std::bind creates a FUNCTION OBJECT (callable) by:\n";
    std::cout << "  1. Binding some arguments to fixed values (partial application)\n";
    std::cout << "  2. Using placeholders (_1, _2, ...) for arguments to be provided later\n";
    std::cout << "  3. Reordering arguments\n\n";
    std::cout << "Key insight: std::bind returns a function object, NOT a function pointer.\n";
    std::cout << "It creates a callable object that can be:\n";
    std::cout << "  - Stored in std::function (type-erased polymorphic wrapper)\n";
    std::cout << "  - Passed to algorithms\n";
    std::cout << "  - Called like a function\n\n";
    
    std::cout << "PROBLEMS WITH std::bind:\n";
    std::cout << "  ⚠️ Placeholder syntax (_1, _2) is cryptic\n";
    std::cout << "  ⚠️ Complex template types, hard to debug\n";
    std::cout << "  ⚠️ Fragile with overloaded functions\n";
    std::cout << "  ⚠️ Cannot capture by move (no init capture)\n\n";

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
        
        std::cout << "\nMember Function Callbacks: Real-world use case\n";
        std::cout << "Common pattern: Binding 'this' pointer for callbacks\n\n";
        
        std::cout << "Example: Event handler registration\n";
        std::cout << "  C++11 std::bind:\n";
        std::cout << "    auto callback = std::bind(&Foo::process, this, _1);\n";
        std::cout << "    event_system.register_handler(callback);\n\n";
        
        std::cout << "  C++11 lambda (clearer):\n";
        std::cout << "    auto callback = [this](const std::string& data) { process(data); };\n";
        std::cout << "    event_system.register_handler(callback);\n\n";
        
        std::vector<std::string> events = {"event1", "event2", "event3"};
        std::cout << "Simulating event processing:\n";
        for (const auto& event : events) {
            auto callback_bind = std::bind(&Foo::process, &foo, std::placeholders::_1);
            callback_bind(event);
        }
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
    
    {
        std::cout << "\n--- C++14: Perfect Forwarding with Generic Lambdas ---\n";
        std::cout << "Generic lambdas enable perfect forwarding patterns that std::bind struggles with.\n\n";
        
        std::cout << "Use case: Generic callback wrapper that forwards arguments efficiently\n";
        std::cout << "Code pattern:\n";
        std::cout << "  auto callback = [](auto&& arg) {\n";
        std::cout << "      process(std::forward<decltype(arg)>(arg));\n";
        std::cout << "  };\n\n";
        
        std::cout << "Why this matters:\n";
        std::cout << "  - Preserves lvalue/rvalue-ness (no unnecessary copies)\n";
        std::cout << "  - Works with move-only types (std::unique_ptr, etc.)\n";
        std::cout << "  - std::bind requires complex std::ref/std::cref workarounds\n\n";
        
        // Demonstration
        Foo foo;
        auto perfect_forward_lambda = [&foo](auto&& data) {
            foo.process(std::forward<decltype(data)>(data));
        };
        
        std::string str1 = "lvalue_string";
        std::cout << "Forwarding lvalue: ";
        perfect_forward_lambda(str1);
        
        std::cout << "Forwarding rvalue: ";
        perfect_forward_lambda(std::string("rvalue_string"));
        
        std::cout << "\nComparison with std::bind:\n";
        std::cout << "  std::bind: Requires std::ref for references, cannot forward perfectly\n";
        std::cout << "  Lambda:    Natural forwarding with auto&& and std::forward\n";
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

    section_header("Comparison Summary: Functors vs std::bind vs Lambda");
    std::cout << "┌─────────────────────────────┬──────────────────────┬────────────────────┬─────────────────────┐\n";
    std::cout << "│ Feature                     │ Functor (Pre-C++11)  │ std::bind (C++11)  │ Lambda (C++11/14+)  │\n";
    std::cout << "├─────────────────────────────┼──────────────────────┼────────────────────┼─────────────────────┤\n";
    std::cout << "│ Syntax verbosity            │ ❌ 7+ lines          │ ⚠️ Medium          │ ✅ 1 line           │\n";
    std::cout << "│ Readability                 │ ⚠️ Fair              │ ❌ Poor            │ ✅ Excellent        │\n";
    std::cout << "│ Partial application         │ ✅ Yes (manual)      │ ✅ Yes             │ ✅ Yes              │\n";
    std::cout << "│ State capture               │ ✅ Yes (members)     │ ✅ Yes (copy/ref)  │ ✅ Yes (capture)    │\n";
    std::cout << "│ Argument reordering         │ ✅ Yes (manual)      │ ✅ Yes             │ ✅ Yes (explicit)   │\n";
    std::cout << "│ Generic parameters          │ ⚠️ Requires template │ ❌ No              │ ✅ Yes (C++14)      │\n";
    std::cout << "│ Move semantics              │ ✅ Yes (manual)      │ ❌ No              │ ✅ Yes (C++14)      │\n";
    std::cout << "│ Perfect forwarding          │ ✅ Yes (manual)      │ ⚠️ Complex         │ ✅ Easy (C++14)     │\n";
    std::cout << "│ Overload safety             │ ✅ Safe              │ ❌ Fragile         │ ✅ Safe             │\n";
    std::cout << "│ Inline at call site         │ ❌ No                │ ❌ No              │ ✅ Yes              │\n";
    std::cout << "│ Modern status               │ ⚠️ When needed       │ ⚠️ Legacy          │ ✅ Preferred        │\n";
    std::cout << "└─────────────────────────────┴──────────────────────┴────────────────────┴─────────────────────┘\n";
    std::cout << "\nEVOLUTION INSIGHT:\n";
    std::cout << "  Functors → std::bind:  Automated functor generation, reduced boilerplate\n";
    std::cout << "  std::bind → Lambdas:   Inline syntax, type safety, modern features\n";
    std::cout << "  All three compile to the same machine code - it's about DEVELOPER EXPERIENCE!\n";

    section_header("THREE LAYERS: Function Objects, Containers, and Pointers");
    std::cout << "Understanding the relationship between lambdas, std::bind, and std::function:\n\n";
    
    std::cout << "LAYER 1: CALLABLE OBJECTS (Compile-time types)\n";
    std::cout << "  - Function pointers: void(*)(int)\n";
    std::cout << "  - Functors: struct with operator()\n";
    std::cout << "  - Lambdas: [](int x){ return x * 2; }\n";
    std::cout << "  - std::bind results: std::bind(func, _1)\n";
    std::cout << "  Each has a UNIQUE, CONCRETE type known at compile-time\n\n";
    
    std::cout << "LAYER 2: TYPE-ERASED CONTAINER (Runtime polymorphism)\n";
    std::cout << "  - std::function<Signature>: Polymorphic wrapper\n";
    std::cout << "  Can hold ANY callable matching the signature\n";
    std::cout << "  Provides runtime flexibility at slight performance cost\n\n";
    
    std::cout << "CRITICAL DISTINCTION:\n";
    std::cout << "  ❌ WRONG: std::bind and std::function are similar\n";
    std::cout << "  ✅ RIGHT: std::bind CREATES callables, std::function STORES them\n\n";
    
    std::cout << "┌─────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Layer 2: std::function (CONTAINER)                     │\n";
    std::cout << "│         - Type erasure (runtime polymorphism)           │\n";
    std::cout << "│         - Can hold any callable with matching signature │\n";
    std::cout << "│         - std::function<int(int)>                       │\n";
    std::cout << "└─────────────────────────────────────────────────────────┘\n";
    std::cout << "                       ▲\n";
    std::cout << "                       │ Can store\n";
    std::cout << "                       │\n";
    std::cout << "┌─────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Layer 1: Callable Objects (CONCRETE TYPES)             │\n";
    std::cout << "│  • Lambda:      [](int x){ return x * 2; }             │\n";
    std::cout << "│  • std::bind:   std::bind(add, 10, _1)                 │\n";
    std::cout << "│  • Functor:     struct Adder { int operator()(int); }  │\n";
    std::cout << "│  • Function ptr: int(*)(int)                            │\n";
    std::cout << "└─────────────────────────────────────────────────────────┘\n\n";
    
    std::cout << "KEY INSIGHT:\n";
    std::cout << "  std::bind and lambdas are at the SAME layer (callable objects)\n";
    std::cout << "  std::function is at a DIFFERENT layer (polymorphic container)\n";
    std::cout << "  Both std::bind results AND lambdas can be stored in std::function\n";

    section_header("std::function Deep Dive: Type Erasure and Polymorphism");
    {
        std::cout << "WHAT IS std::function?\n";
        std::cout << "A type-erased, polymorphic wrapper for ANY callable matching a signature.\n\n";
        
        std::cout << "Think of it as a 'universal container' for callables:\n";
        std::cout << "  std::function<int(int)> can hold:\n";
        std::cout << "    - Lambda:         [](int x){ return x * 2; }\n";
        std::cout << "    - std::bind:      std::bind(add, 10, _1)\n";
        std::cout << "    - Functor:        Multiplier(2)\n";
        std::cout << "    - Function ptr:   &add  (if signature matches)\n\n";
        
        std::cout << "--- Example: std::function holding different callables ---\n";
        
        // Lambda
        auto lambda_multiply = [](int x){ return x * 2; };
        
        // std::bind result
        auto bind_add = std::bind(add, 10, std::placeholders::_1);
        
        // Functor
        Multiplier functor(3);
        
        // Store all three in std::function (polymorphic!)
        std::vector<std::function<int(int)>> operations;
        
        operations.push_back(lambda_multiply);
        operations.push_back(bind_add);
        operations.push_back(functor);
        
        std::cout << "Calling different callables through std::function:\n";
        for (size_t i = 0; i < operations.size(); ++i) {
            std::cout << "  operations[" << i << "](5) = " << operations[i](5) << '\n';
        }
        
        std::cout << "\nKEY POINT: All three have DIFFERENT concrete types,\n";
        std::cout << "but std::function provides a COMMON interface!\n";
    }
    
    section_header("std::function vs auto vs Template: Performance Trade-offs");
    {
        std::cout << "THREE ways to store a callable:\n\n";
        
        std::cout << "1. DIRECT TYPE (auto / concrete type)\n";
        std::cout << "   auto f = [](int x){ return x * 2; };\n";
        std::cout << "   ✅ Zero overhead - fully inlined\n";
        std::cout << "   ✅ Compile-time type known\n";
        std::cout << "   ❌ Cannot change what f points to\n";
        std::cout << "   ❌ Cannot store different callables in same variable\n\n";
        
        std::cout << "2. std::function (type-erased)\n";
        std::cout << "   std::function<int(int)> f = [](int x){ return x * 2; };\n";
        std::cout << "   ✅ Can change what f points to at runtime\n";
        std::cout << "   ✅ Can store in containers\n";
        std::cout << "   ✅ Polymorphic - accepts any matching callable\n";
        std::cout << "   ⚠️ Slight overhead (indirection + possible heap allocation)\n\n";
        
        std::cout << "3. Template parameter (generic)\n";
        std::cout << "   template<typename Func> void process(Func f) { f(5); }\n";
        std::cout << "   ✅ Zero overhead - fully inlined\n";
        std::cout << "   ✅ Works with any callable\n";
        std::cout << "   ⚠️ Code bloat (instantiated for each type)\n";
        std::cout << "   ❌ Cannot store in non-template containers\n\n";
        
        std::cout << "PERFORMANCE COMPARISON:\n";
        auto direct_lambda = [](int x){ return x * 2; };
        std::function<int(int)> wrapped_lambda = direct_lambda;
        
        std::cout << "  Direct call:         auto f = [](int x){ return x * 2; };  // ~1 CPU cycle\n";
        std::cout << "  std::function call:  std::function<int(int)> f = ...;      // ~5-10 cycles\n";
        std::cout << "  (Numbers approximate - compiler-dependent)\n\n";
        
        std::cout << "WHEN TO USE EACH:\n";
        std::cout << "  • auto:          When callable type is known and fixed\n";
        std::cout << "  • Template:      When you need zero-overhead generic code\n";
        std::cout << "  • std::function: When you need runtime polymorphism\n";
    }
    
    section_header("Real-World Use Cases for std::function");
    {
        std::cout << "USE CASE 1: Callback Storage\n";
        std::cout << "Example: Event system with multiple handler types\n\n";
        std::cout << "Code:\n";
        std::cout << "  std::vector<std::function<void(const Event&)>> handlers;\n";
        std::cout << "  handlers.push_back([](const Event& e){ /* lambda handler */ });\n";
        std::cout << "  handlers.push_back(std::bind(&Class::method, &obj, _1));\n";
        std::cout << "  handlers.push_back(legacy_function);  // function pointer\n\n";
        
        std::cout << "USE CASE 2: Strategy Pattern\n";
        std::cout << "Example: Configurable algorithm behavior\n\n";
        std::cout << "Code:\n";
        std::cout << "  class Processor {\n";
        std::cout << "      std::function<int(int)> strategy_;\n";
        std::cout << "  public:\n";
        std::cout << "      void set_strategy(std::function<int(int)> s) { strategy_ = s; }\n";
        std::cout << "      int process(int x) { return strategy_(x); }\n";
        std::cout << "  };\n\n";
        std::cout << "  Processor p;\n";
        std::cout << "  p.set_strategy([](int x){ return x * 2; });  // multiply strategy\n";
        std::cout << "  p.set_strategy([](int x){ return x + 10; }); // add strategy\n\n";
        
        std::cout << "USE CASE 3: Thread Pool / Async Tasks\n";
        std::cout << "Example: Task queue accepting any callable\n\n";
        std::cout << "Code:\n";
        std::cout << "  std::queue<std::function<void()>> tasks;\n";
        std::cout << "  tasks.push([]{ std::cout << \"Task 1\\n\"; });\n";
        std::cout << "  tasks.push([&obj]{ obj.work(); });\n";
        std::cout << "  tasks.push(std::bind(&Class::method, &obj));\n\n";
        
        std::cout << "USE CASE 4: API Boundaries / Plugin Systems\n";
        std::cout << "When you don't know the callable type at compile time:\n";
        std::cout << "  void register_plugin(std::function<void(Data&)> plugin);\n\n";
        
        std::cout << "ANTI-PATTERN: Don't use std::function when auto/template suffices!\n";
        std::cout << "  ❌ BAD:  std::function<int(int)> f = [](int x){ return x * 2; };\n";
        std::cout << "           int result = f(5);  // Unnecessary overhead\n\n";
        std::cout << "  ✅ GOOD: auto f = [](int x){ return x * 2; };\n";
        std::cout << "           int result = f(5);  // Zero overhead\n";
    }
    
    section_header("std::function Internals: How Type Erasure Works");
    {
        std::cout << "UNDER THE HOOD:\n";
        std::cout << "std::function uses type erasure via internal vtable-like mechanism:\n\n";
        
        std::cout << "Conceptual implementation (simplified):\n";
        std::cout << "  template<typename R, typename... Args>\n";
        std::cout << "  class function<R(Args...)> {\n";
        std::cout << "      void* callable_;     // Pointer to stored callable\n";
        std::cout << "      R (*invoker_)(void*, Args...);  // Function to invoke it\n";
        std::cout << "      void (*deleter_)(void*);        // Function to destroy it\n";
        std::cout << "  };\n\n";
        
        std::cout << "MEMORY ALLOCATION:\n";
        std::cout << "  Small Callable:  Stored inline (Small Buffer Optimization)\n";
        std::cout << "  Large Callable:  Heap-allocated\n\n";
        
        std::cout << "PERFORMANCE COST:\n";
        std::cout << "  1. Indirection (function pointer call)\n";
        std::cout << "  2. Possible heap allocation on assignment\n";
        std::cout << "  3. Cannot be inlined by compiler\n\n";
        
        std::cout << "TRADE-OFF:\n";
        std::cout << "  You pay a small runtime cost for HUGE flexibility:\n";
        std::cout << "  - Store any callable with matching signature\n";
        std::cout << "  - Change callable at runtime\n";
        std::cout << "  - Build polymorphic containers of callables\n";
    }

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

    section_header("Complete Comparison: Lambda vs std::bind vs std::function");
    std::cout << "┌──────────────────────┬─────────────────────┬─────────────────────┬──────────────────────┐\n";
    std::cout << "│ Aspect               │ Lambda              │ std::bind           │ std::function        │\n";
    std::cout << "├──────────────────────┼─────────────────────┼─────────────────────┼──────────────────────┤\n";
    std::cout << "│ What it is           │ Callable object     │ Callable generator  │ Callable container   │\n";
    std::cout << "│ Type                 │ Unique concrete     │ Unique concrete     │ Type-erased wrapper  │\n";
    std::cout << "│ Purpose              │ Define logic inline │ Bind args/reorder   │ Store any callable   │\n";
    std::cout << "│ Performance          │ ✅ Zero overhead    │ ✅ Zero overhead    │ ⚠️ Slight overhead   │\n";
    std::cout << "│ Polymorphism         │ ❌ No               │ ❌ No               │ ✅ Yes (type erasure)│\n";
    std::cout << "│ Inlining             │ ✅ Excellent        │ ⚠️ Good             │ ❌ Prevented         │\n";
    std::cout << "│ Heap allocation      │ ❌ No               │ ❌ No               │ ⚠️ Possible          │\n";
    std::cout << "│ Reassignable         │ ❌ No (const type)  │ ❌ No (const type)  │ ✅ Yes               │\n";
    std::cout << "│ Container storage    │ ❌ Different types  │ ❌ Different types  │ ✅ Homogeneous       │\n";
    std::cout << "│ C++ version          │ C++11+              │ C++11 (obsolete)    │ C++11+               │\n";
    std::cout << "│ Modern status        │ ✅ Preferred        │ ⚠️ Legacy           │ ✅ When needed       │\n";
    std::cout << "└──────────────────────┴─────────────────────┴─────────────────────┴──────────────────────┘\n\n";
    
    std::cout << "CONCEPTUAL RELATIONSHIP:\n\n";
    std::cout << "  Lambda and std::bind are at the SAME layer:\n";
    std::cout << "    Both create concrete callable objects\n";
    std::cout << "    Lambda is cleaner, std::bind is obsolete\n\n";
    
    std::cout << "  std::function is at a DIFFERENT layer:\n";
    std::cout << "    It's a container that can hold EITHER lambdas OR bind results\n";
    std::cout << "    Provides runtime polymorphism\n\n";
    
    std::cout << "ANALOGY:\n";
    std::cout << "  Lambda/std::bind → like creating objects (int, std::string, MyClass)\n";
    std::cout << "  std::function    → like std::any (can hold any matching type)\n\n";
    
    std::cout << "DECISION TREE:\n";
    std::cout << "  Need to define callable?\n";
    std::cout << "    ✅ Use lambda (not std::bind)\n\n";
    std::cout << "  Need to store callable in variable/container?\n";
    std::cout << "    └─ Same type always? → Use auto or concrete type\n";
    std::cout << "    └─ Different types?  → Use std::function<Signature>\n\n";
    
    std::cout << "PERFORMANCE HIERARCHY (fastest to slowest):\n";
    std::cout << "  1. Direct lambda call:              auto f = []{ ... };  f();\n";
    std::cout << "  2. Template parameter:              template<typename F> void g(F f);\n";
    std::cout << "  3. std::function call:              std::function<void()> f = ...;\n";
    std::cout << "  4. Virtual function call:           obj->virtual_func();\n";
    std::cout << "  (Typical overhead: 0x, 0x, 1-2x, 2-3x baseline)\n";

    section_header("Final Recommendation");
    std::cout << "THE EVOLUTION COMPLETE:\n";
    std::cout << "  Pre-C++11: Manual functors (necessary but verbose)\n";
    std::cout << "  C++11:     std::bind (automated but cryptic)\n";
    std::cout << "  C++14+:    Lambdas (clean, safe, feature-rich)\n\n";
    
    std::cout << "WHEN TO USE EACH:\n\n";
    std::cout << "✅ LAMBDAS (Preferred for all new code)\n";
    std::cout << "   - Any C++11 code: Basic lambdas work fine\n";
    std::cout << "   - C++14+: Generic lambdas for maximum flexibility\n";
    std::cout << "   - C++17+: constexpr lambdas for compile-time computation\n";
    std::cout << "   - C++20+: Template lambdas, concept-constrained lambdas\n\n";
    
    std::cout << "✅ std::function (When you need runtime polymorphism)\n";
    std::cout << "   - Storing different callables in same container\n";
    std::cout << "   - Callback systems with varying implementations\n";
    std::cout << "   - Plugin architectures / Strategy pattern\n";
    std::cout << "   - API boundaries where callable type unknown\n\n";
    
    std::cout << "✅ FUNCTORS (When you need specific control)\n";
    std::cout << "   - Public member functions (not just operator())\n";
    std::cout << "   - Complex state management with multiple methods\n";
    std::cout << "   - Inheritance hierarchies\n";
    std::cout << "   - When you want a named, reusable class\n\n";
    
    std::cout << "⚠️  std::bind (Only for legacy code)\n";
    std::cout << "   - Maintaining existing C++11 codebases\n";
    std::cout << "   - When migrating from Boost.Bind\n";
    std::cout << "   - Consider refactoring to lambdas when possible\n\n";
    
    std::cout << "❌ AVOID (Unless interfacing with C)\n";
    std::cout << "   - Raw function pointers (use std::function instead)\n";
    std::cout << "   - C++03 std::bind1st/bind2nd (removed in C++17)\n\n";
    
    std::cout << "Modern C++ idiom (C++14+):\n";
    std::cout << "  // Simple inline lambda (zero overhead)\n";
    std::cout << "  auto my_callable = [captured_state](auto x) { return captured_state + x; };\n\n";
    std::cout << "  // Member function callback with perfect forwarding\n";
    std::cout << "  auto callback = [this](auto&& arg) {\n";
    std::cout << "      this->process(std::forward<decltype(arg)>(arg));\n";
    std::cout << "  };\n\n";
    std::cout << "  // Polymorphic storage (when needed)\n";
    std::cout << "  std::function<int(int)> poly_callable = my_callable;\n\n";
    std::cout << "  // Container of different callables\n";
    std::cout << "  std::vector<std::function<void()>> tasks;\n";
    std::cout << "  tasks.push_back([](){ std::cout << \"Task 1\\n\"; });\n";
    std::cout << "  tasks.push_back([](){ std::cout << \"Task 2\\n\"; });\n";

    return 0;
}
