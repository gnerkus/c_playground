# Compilation
## Pre-requisites
- Lua has been installed into the `C:\Program Files\Lua` directory.
- [Lua static binaries](https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/) have been extracted into the `C:\Program Files\Lua` directory. The static files include the `.h` and `.hpp` files as well as a `.a` file for Mingw64 and a `.lib` file for Visual studio (_Windows_).
- The static `.a` library file is called `liblua54`. This is because the `-l` options appends "lib" to the name of the library so that "lua54" becomes "liblua54"
- The static binaries in `C:\Program Files\Lua` are of the same bit as the `gcc` compiler i.e if `gcc` is 32 bit then the static binaries must be 32 bit.
- Git Bash is installed. The compilation step does not work in Powershell
 
# Steps
- Open up Git Bash in the project directory and run:
```bash
gcc -Wall -o test test.c -I "C:\Program Files\Lua\include" -L "C:\Program Files\Lua" -llua54
```

## Test environment
This compilation step was tested in an environment with the following specs:
- Windows 10
- Lua 64 bit was installed and configured as specified in the `#Assumptions` section
- gcc compiler is mingw 64 bit