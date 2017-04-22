# Creature

Fan-Project inspired by Digimon (Digimon World 1), Pokemon, Black and White and other Tamagotchii-Stuff.

## Features

 - Feed (Hunger, Thirsty)
 - Poop
 - Sleep
 - RPG-Elements
     - Level
     - Stats: MaxHP, MaMP, Atk ,...
 - Evolve
     - different paths
     - base on RPG-Stats
     - base on Happiness and other factors
 - Happiness
     - can "run away"
 - Discipline
 - some Memory (Personality?)
 - Fitness
     - Weight, Size, ...



## <a name="build"></a> Build

### CMake

I used CMake 3.2 for the build.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBuildTests:BOOL="0" -DCXXOPTS_BUILD_EXAMPLES:BOOL="0" -DTYPE_SAFE_ARITHMETIC_UB:BOOL="1" -DWITH_CPP11:BOOL="1" -DBUILD_TESTING:BOOL="0" -DTHREAD_SAFE:BOOL="1"`
 4. `cmake --build ./build --target creature_backend`
    - OR for Tests `cmake --build ./build --target creature_backend_test`

#### CTest

 1. `cd ./build/backend`
 2. Build Tests: `cmake --build .. --target creature_backend_test`
 3. Run Tests `ctest -R ".*creature_backend.*"` 


### C++ Compiler

 - modern C++14 Standard (`-std=c++14`)
 - Default CMake Release Flags (`-O3 -DNDEBUG`)
 - some Compiler Warnings (`-Wall -Wextra -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -pedantic`)
 - Threading (not used, yet?) (`-pthread`)


I used g++ 6.4.0, clang++ 3.8 should work, too.


#### clang-tidy

 1. `mkdir ./build`
 2. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBuildTests:BOOL="0" -DCXXOPTS_BUILD_EXAMPLES:BOOL="0" -DTYPE_SAFE_ARITHMETIC_UB:BOOL="1" -DWITH_CPP11:BOOL="1" -DBUILD_TESTING:BOOL="0" -DTHREAD_SAFE:BOOL="1"`
 3. `cp ./tools/run-clang-tidy.py ./build`
 4. `cd ./build`
 5. `python2 run-clang-tidy.py -p . -header-filter='^(.*\.h|.*(?!cereal|backend/lib).*)$' -checks='-*,modernize-*,cppcoreguidelines-*,llvm-header-guard,llvm-include-order,llvm-namespace-comment' -fix -format`
