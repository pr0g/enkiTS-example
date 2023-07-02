# Steps

```bash
# FetchContent version
cmake -B build
cmake --build build
```

or

```bash
# ExternalProject_Add version (after having run steps in third-party/README.md)
cmake -B build -DENKITS_EXAMPLE_USE_INSTALL=ON -DCMAKE_PREFIX_PATH=third-party/build
cmake --build build
```
