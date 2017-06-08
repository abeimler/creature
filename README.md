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
 - and more



## <a name="build"></a> Build

### CMake

I used CMake 3.2 for the build.

 1. change directory to this Folder
 2. `mkdir ./build`
 3. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DWITH_WERROR:BOOL="0" -DBuildTests:BOOL="0" -DSKIP_PORTABILITY_TEST:BOOL="1" -DDOCTEST_WITH_TESTS:BOOL="0" -DJUST_INSTALL_CEREAL:BOOL="1" -DTHREAD_SAFE:BOOL="1"`
 4. `cmake --build ./build --target creature_backend`
    - OR for Tests `cmake --build ./build --target creature_backend_test`

#### CTest

 1. `cd ./build/backend`
 2. Build Tests: `cmake --build .. --target creature_backend_test`
 3. Run Tests `ctest -R ".*creature_backend.*"` 


### C++ Compiler

 - modern C++14 Standard (`-std=c++14`)
 - Default CMake Flags


I used g++ 6.4.0, clang++ 3.8 should work, too.


#### clang-tidy

 1. `mkdir ./build`
 2. `cmake -H. -B./build -DCMAKE_BUILD_TYPE=Release -DWITH_WERROR:BOOL="0" -DBuildTests:BOOL="0" -DSKIP_PORTABILITY_TEST:BOOL="1" -DDOCTEST_WITH_TESTS:BOOL="0" -DJUST_INSTALL_CEREAL:BOOL="1" -DTHREAD_SAFE:BOOL="1"`
 3. `cp ./tools/run-clang-tidy.py ./build`
 4. `cd ./build`
 5. `python2 run-clang-tidy.py -p . -header-filter='^(.*\.h|.*(?!cereal|doctest).*)$' -checks='-*,modernize-*,cppcoreguidelines-*,llvm-header-guard,llvm-include-order,llvm-namespace-comment' -fix -format`
