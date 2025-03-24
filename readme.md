# This is my attempt on making a game engine.

This is only for learning puposes.

## How to build the project

1) ```
   git clone <url> pinni
   ```
2) ```
   cd pinni

   conan install . --build=missing -s build_type=Release
   #or
   conan install . --build=missing -s build_type=Debug

   cmake --preset=conan-release
   #or
   cmake --preset=conan-debug -DPINNI_BUILD_TESTS=ON

   cd build/Release; cmake --build .
   #or
   cd build/Debug; cmake --build .
   ```
