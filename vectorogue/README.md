# Build
1. Navigate to root directory and run
```bash
cmake -B build
```
2. Then run
```bash
cmake --build build
```

# Execution

# TEMP
## Helpful notes about C
### Deciphering C types
https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c#comment45106472_1088622

>  "Start at the name, read right when you can, left when you must": `char (*a[2])[14]` - start at a, move right: "array of two", move left: "pointer to", bracket complete so read right: "array of forteen", read left: "char"... Put it together and we have "a is array of two pointers to arrays of forteen chars" 