# Ekonom
## Developers
### Prerequisites
This projects requires **conan** and **cmake**. Project developed in MSVC toolset version `14.28.*` (for x64 Windows) and GNU GCC toolset version `9.3.0` (for x64 linux).
### Structure
Project has cxx and web sources, that way you can easily navigate through native implementation and interface. 

### Compile
Compiling is done with cmake. This process depends on your platform and your meta generator. 

For Windows (VisualStudio generator)
```cmd
mkdir build && cd build
cmake .. 
cmake --build .
```

For Linux (GNU GCC generator)
```cmd
mkdir build && cd build
cmake .. 
make .
```
## Credits
Logo created by [@notfreeusername](https://github.com/notfreeusername)
