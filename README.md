# Ekonom
## Developers
### Prerequisites
This projects requires **conan** and **cmake**. Project developed in MSVC toolset version `14.28.29910` (for x64 Windows) and GNU GCC toolset version `9.3.0` (for x64 linux).
### Structure
Source is divided into two parts. CXX where cpp/hpp files are stored, and WEB where all html/css/js UI files are stored.

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
