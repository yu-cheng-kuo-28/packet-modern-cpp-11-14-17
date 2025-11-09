# CMakeLists.txt for Lambda Evolution Demo
# Modern C++ Lambda Functions demonstration across C++11/14/17/20 standards

cmake_minimum_required(VERSION 3.16)
project(LambdaEvolutionDemo
    VERSION 1.0.0
    DESCRIPTION "C++ Lambda Evolution Demonstration"
    LANGUAGES CXX)

# Set C++ standards to test
set(CPP_STANDARDS 11 14 17 20)

# Common compiler settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Source files
set(SOURCES
    00_cpp_version_check.cpp
    01_simple_lambda_comparison.cpp
    02_lambda_feature_comparison.cpp
    03_lambda_evolution_demo.cpp
    04_lambda_replace_bind.cpp
)

# Define target names for each demo type
set(DEMO_NAMES
    "lambda_demo"
    "simple_demo" 
    "comparison"
)

# Function to create targets for all C++ standards based on source filename
function(create_demo_targets source_file)
    # Extract base name without extension (e.g., "03_lambda_evolution_demo" from "03_lambda_evolution_demo.cpp")
    get_filename_component(base_name ${source_file} NAME_WE)
    
    foreach(std ${CPP_STANDARDS})
        set(target_name "${base_name}_cpp${std}")
        add_executable(${target_name} ${source_file})
        set_target_properties(${target_name} PROPERTIES
            CXX_STANDARD ${std}
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
        )
        # Add to appropriate groups for organization
        set_target_properties(${target_name} PROPERTIES FOLDER "cpp${std}")
        
        message(STATUS "Created target: ${target_name} (C++${std})")
    endforeach()
endfunction()

# Create all demo targets with filenames as base names
create_demo_targets("03_lambda_evolution_demo.cpp")
create_demo_targets("01_simple_lambda_comparison.cpp")
create_demo_targets("02_lambda_feature_comparison.cpp")

# Create individual target for version check using filename-based naming
foreach(std ${CPP_STANDARDS})
    set(target_name "00_cpp_version_check_cpp${std}")
    add_executable(${target_name} "00_cpp_version_check.cpp")
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD ${std}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    message(STATUS "Created target: ${target_name} (C++${std})")
endforeach()

# Special handling for 04_lambda_replace_bind.cpp - only C++14
add_executable(04_lambda_replace_bind_cpp14 "04_lambda_replace_bind.cpp")
set_target_properties(04_lambda_replace_bind_cpp14 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
message(STATUS "Created target: 04_lambda_replace_bind_cpp14 (C++14 only)")


# === CONVENIENCE TARGETS ===

# Build all versions of each demo type
add_custom_target(all-full
    DEPENDS 03_lambda_evolution_demo_cpp11 03_lambda_evolution_demo_cpp14 03_lambda_evolution_demo_cpp17 03_lambda_evolution_demo_cpp20
    COMMENT "Building all full demo versions"
)

add_custom_target(all-simple
    DEPENDS 01_simple_lambda_comparison_cpp11 01_simple_lambda_comparison_cpp14 01_simple_lambda_comparison_cpp17 01_simple_lambda_comparison_cpp20
    COMMENT "Building all simple comparison versions"
)

add_custom_target(all-comparison
    DEPENDS 02_lambda_feature_comparison_cpp11 02_lambda_feature_comparison_cpp14 02_lambda_feature_comparison_cpp17 02_lambda_feature_comparison_cpp20
    COMMENT "Building all feature comparison versions"
)

add_custom_target(all-bind-replacement
    DEPENDS 04_lambda_replace_bind_cpp14
    COMMENT "Building std::bind replacement demo (C++14 only)"
)

add_custom_target(all-version-check
    DEPENDS 00_cpp_version_check_cpp11 00_cpp_version_check_cpp14 00_cpp_version_check_cpp17 00_cpp_version_check_cpp20
    COMMENT "Building all version check versions"
)

add_custom_target(all-demos
    DEPENDS all-full all-simple all-comparison all-bind-replacement all-version-check
    COMMENT "Building all demo versions"
)

# === RUN TARGETS ===

# Function to create run targets based on source filename
function(create_run_target source_file description)
    # Extract base name without extension
    get_filename_component(base_name ${source_file} NAME_WE)
    
    foreach(std ${CPP_STANDARDS})
        set(target_name "${base_name}_cpp${std}")
        add_custom_target(run-${target_name}
            COMMAND ${target_name}
            DEPENDS ${target_name}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Running ${description} (C++${std})"
        )
    endforeach()
endfunction()

# Create individual run targets
create_run_target("03_lambda_evolution_demo.cpp" "Full Lambda Evolution Demo")
create_run_target("01_simple_lambda_comparison.cpp" "Simple Lambda Comparison")
create_run_target("02_lambda_feature_comparison.cpp" "Feature Comparison Demo")

# Create run target for bind replacement demo (C++14 only)
add_custom_target(run-04_lambda_replace_bind_cpp14
    COMMAND 04_lambda_replace_bind_cpp14
    DEPENDS 04_lambda_replace_bind_cpp14
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running std::bind Replacement Demo (C++14)"
)

# Create run targets for version check
foreach(std ${CPP_STANDARDS})
    set(target_name "00_cpp_version_check_cpp${std}")
    add_custom_target(run-${target_name}
        COMMAND ${target_name}
        DEPENDS ${target_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running C++ Version Check (C++${std})"
    )
endforeach()

# Combined run targets
add_custom_target(run-all-full
    COMMAND 03_lambda_evolution_demo_cpp11
    COMMAND echo "\\n\\n=== C++14 Version ==="
    COMMAND 03_lambda_evolution_demo_cpp14
    COMMAND echo "\\n\\n=== C++17 Version ==="
    COMMAND 03_lambda_evolution_demo_cpp17
    COMMAND echo "\\n\\n=== C++20 Version ==="
    COMMAND 03_lambda_evolution_demo_cpp20
    DEPENDS all-full
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running all full demo versions"
)

add_custom_target(run-all-simple
    COMMAND 01_simple_lambda_comparison_cpp11
    COMMAND echo "\\n\\n=== Simple C++14 Version ==="
    COMMAND 01_simple_lambda_comparison_cpp14
    COMMAND echo "\\n\\n=== Simple C++17 Version ==="
    COMMAND 01_simple_lambda_comparison_cpp17
    COMMAND echo "\\n\\n=== Simple C++20 Version ==="
    COMMAND 01_simple_lambda_comparison_cpp20
    DEPENDS all-simple
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running all simple comparison versions"
)

add_custom_target(run-all-comparison
    COMMAND 02_lambda_feature_comparison_cpp11
    COMMAND echo "\\n\\n=== Comparison C++14 Version ==="
    COMMAND 02_lambda_feature_comparison_cpp14
    COMMAND echo "\\n\\n=== Comparison C++17 Version ==="
    COMMAND 02_lambda_feature_comparison_cpp17
    COMMAND echo "\\n\\n=== Comparison C++20 Version ==="
    COMMAND 02_lambda_feature_comparison_cpp20
    DEPENDS all-comparison
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running all feature comparison versions"
)

add_custom_target(run-all-bind-replacement
    COMMAND 04_lambda_replace_bind_cpp14
    DEPENDS all-bind-replacement
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running std::bind replacement demo"
)

add_custom_target(run-all-version-check
    COMMAND 00_cpp_version_check_cpp11
    COMMAND echo "\\n\\n=== C++14 Version Check ==="
    COMMAND 00_cpp_version_check_cpp14
    COMMAND echo "\\n\\n=== C++17 Version Check ==="
    COMMAND 00_cpp_version_check_cpp17
    COMMAND echo "\\n\\n=== C++20 Version Check ==="
    COMMAND 00_cpp_version_check_cpp20
    DEPENDS all-version-check
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running all version checks"
)

add_custom_target(run-all-demos
    DEPENDS run-all-full run-all-simple run-all-comparison run-all-bind-replacement run-all-version-check
    COMMENT "Running all demo versions"
)

# === INDIVIDUAL C++ STANDARD TARGETS (for convenience) ===
add_custom_target(cpp11
    DEPENDS 03_lambda_evolution_demo_cpp11
    COMMENT "Building C++11 version of full demo"
)

add_custom_target(cpp14
    DEPENDS 03_lambda_evolution_demo_cpp14
    COMMENT "Building C++14 version of full demo"
)

add_custom_target(cpp17
    DEPENDS 03_lambda_evolution_demo_cpp17
    COMMENT "Building C++17 version of full demo"
)

add_custom_target(cpp20
    DEPENDS 03_lambda_evolution_demo_cpp20
    COMMENT "Building C++20 version of full demo"
)

# Convenience target for quick version checking
add_custom_target(check-version
    DEPENDS 00_cpp_version_check_cpp17
    COMMENT "Quick version check with C++17"
)

# === HELP TARGET ===
add_custom_target(show-help
    COMMAND ${CMAKE_COMMAND} -E echo "Available CMake targets:"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Building:"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-full          - Build all full demo versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-simple        - Build all simple comparison versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-comparison    - Build all feature comparison versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-bind-replacement - Build std::bind replacement demo (C++14 only)"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-version-check - Build all version check versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  all-demos         - Build all demo versions"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Individual Standards (full demo):"
    COMMAND ${CMAKE_COMMAND} -E echo "  cpp11, cpp14, cpp17, cpp20"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Running:"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-full      - Run all full demo versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-simple    - Run all simple versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-comparison - Run all feature comparison versions"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-bind-replacement - Run std::bind replacement demo"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-version-check - Run all version checks"
    COMMAND ${CMAKE_COMMAND} -E echo "  run-all-demos     - Run all demo versions"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Individual runs: run-<target_name> (e.g., run-lambda_demo_cpp17)"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Usage examples:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target all-demos"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target run-all-full"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target cpp17"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target check-version"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target run-all-version-check"
    COMMENT "Showing available targets"
)

# Set default target to C++17 (most commonly used modern standard)
add_custom_target(default ALL DEPENDS cpp17)

# === STATUS INFORMATION ===
message(STATUS "Lambda Evolution Demo Configuration:")
message(STATUS "  C++ Standards: ${CPP_STANDARDS}")
message(STATUS "  Source files: ${SOURCES}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "To see all available targets: cmake --build . --target show-help")
message(STATUS "To build all demos: cmake --build . --target all-demos")
message(STATUS "To run all demos: cmake --build . --target run-all-demos")