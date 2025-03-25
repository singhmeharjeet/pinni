# This is my attempt on making a game engine

This is only for learning puposes.

## How to build the project?

1) ```
   git clone <url> pinni
   ```
2) ```
   cd pinni

   conan install . --build=missing -s build_type=Release
   cmake --preset conan-release
   cmake --build --preset conan-release
   ```

## What am I trying to learn here?

1. Game Development
   * Fundamental **theory and design principles**
   * Best practices in **architecture and performance optimization**
   * Core data structures **for real-time systems**
   * **Rendering techniques, shaders, and pipeline optimization**
   * **Physics, AI, and procedural generation**
2. Developer Tooling
   * CMake and build systems
   * C++ package management
   * Testing frameworks (Google Test, benchmarking, and fuzz testing)
   * Documentation **automation and best practices**
3. Instrumentation & Monitoring
   * Logging **strategies and structured logging**
   * Performance metrics **for real-time applications**
   * Distributed tracing **for debugging complex interactions** (Tracy and other tools)

## Scope Exclusions

This project is currently limited to macOS development. Due to limited experience with Windows solution files and CLI tools, supporting Windows would introduce additional complexity and slow down progress. Therefore, Windows support is not a priority at this stage.
