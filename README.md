# CPP Tasks

Includes C++ practice tasks.

## Building

Building is based on CMake. Debug and Release builds are supported.

Example:
```
cd TASKNUMBER_TASKNAME # e.g. 01_cache
cmake -DCMAKE_BUILD_TYPE=Release -B build
cd build
make
```

This will build 2 executables:
* `build/NAME_OF_PROJECT`
* `build/run_tests`

## Usage

* To run google tests, simply use `run_tests` or use `make test` target.
* To run interactive mode, run compiled binary `NAME_OF_PROJECT` or use `make run` target.
