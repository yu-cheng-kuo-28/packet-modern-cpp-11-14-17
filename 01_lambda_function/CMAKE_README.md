# Lambda Evolution Demo - CMake Build System

This project demonstrates C++ lambda evolution across C++11/14/17/20 using a modern CMake build system. The source files are organized numerically for learning progression.

## Project Structure

The demo files are organized in learning order:
- `00_cpp_version_check.cpp` - Check your compiler's C++ standard support
- `01_lambda_feature_comparison.cpp` - Compare illegal vs legal features by version
- `02_simple_lambda_comparison.cpp` - Same task implemented across versions  
- `03_lambda_evolution_demo.cpp` - Full scientific computing demonstration

This project has been modernized to use CMake instead of the traditional Makefile for a cleaner, more maintainable build system.

## Quick Start

### Prerequisites
- CMake 3.16 or higher
- A modern C++ compiler (g++, clang++, MSVC)

### Building

1. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure the project:**
   ```bash
   cmake ..
   ```

3. **Build specific targets:**
   ```bash
   # Build all demos for all C++ standards
   cmake --build . --target all-demos
   
   # Build only the full demo for C++17
   cmake --build . --target cpp17
   
   # Build all simple comparison versions
   cmake --build . --target all-simple
   ```

4. **Run the demos:**
   ```bash
   # Run all full demo versions
   cmake --build . --target run-all-full
   
   # Run a specific version
   cmake --build . --target run-lambda_demo_cpp17
   ```

## Available Targets

### Building Targets
- `all-demos` - Build all demo versions (version check + feature comparison + simple + full evolution)
- `all-full` - Build all versions of the full evolution demo (`03_lambda_evolution_demo.cpp`)
- `all-simple` - Build all versions of the simple comparison (`02_simple_lambda_comparison.cpp`)
- `all-comparison` - Build all versions of the feature comparison (`01_lambda_feature_comparison.cpp`)
- `cpp11`, `cpp14`, `cpp17`, `cpp20` - Build specific C++ standard version of full demo
- Version check targets: `version_check_cpp11`, `version_check_cpp14`, etc.

### Running Targets  
- `run-all-demos` - Run all demo versions
- `run-all-full` - Run all full demo versions
- `run-all-simple` - Run all simple comparison versions  
- `run-all-comparison` - Run all feature comparison versions
- `run-<target_name>` - Run specific target (e.g., `run-lambda_demo_cpp17`)

### Utility Targets
- `show-help` - Show all available targets
- `clean` - Remove build artifacts (use `cmake --build . --target clean`)

## Advantages over Makefile

1. **Cross-platform compatibility** - Works on Windows, Linux, macOS
2. **Cleaner syntax** - More readable and maintainable
3. **Better dependency management** - CMake handles dependencies automatically
4. **IDE integration** - Better support for Visual Studio, CLion, etc.
5. **Modern build features** - Out-of-source builds, parallel compilation
6. **Standardized** - Industry standard build system for C++

## Example Workflow

```bash
# Set up build directory (one-time setup)
mkdir build && cd build

# Configure project
cmake ..

# Build and run everything
cmake --build . --target all-demos
cmake --build . --target run-all-demos

# Or build and run specific versions
cmake --build . --target cpp17
cmake --build . --target run-lambda_demo_cpp17
```

## Individual Executables

The CMake system generates these executables:
- **Version Check**: `version_check_cpp11`, `version_check_cpp14`, `version_check_cpp17`, `version_check_cpp20`
- **Feature Comparison**: `comparison_cpp11`, `comparison_cpp14`, `comparison_cpp17`, `comparison_cpp20`
- **Simple Comparison**: `simple_demo_cpp11`, `simple_demo_cpp14`, `simple_demo_cpp17`, `simple_demo_cpp20`  
- **Full Evolution Demo**: `lambda_demo_cpp11`, `lambda_demo_cpp14`, `lambda_demo_cpp17`, `lambda_demo_cpp20`

You can run these directly from the build directory after building.

## Recommended Learning Path

1. **Start with version check**: `cmake --build . --target version_check_cpp17`
2. **Learn what's illegal vs legal**: `cmake --build . --target run-comparison_cpp11`
3. **See simple comparisons**: `cmake --build . --target run-all-simple`
4. **Explore full scientific demo**: `cmake --build . --target run-all-full`