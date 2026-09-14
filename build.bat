mkdir build
cmake -B build -G  Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_COMPILER=clang
cmake --build build
