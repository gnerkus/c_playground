# Build
1. Navigate to root directory and run
```bash
cmake -B build -DLIBXML2_INCLUDE_DIR:PATH="C:\Program Files\libxml2\include" -DLIBXML2_LIBRARIES:PATH="C:\Program Files\libxml2\lib"
```
2. Then run
```bash
cmake --build build -DLIBXML2_INCLUDE_DIR:PATH="C:\Program Files\libxml2\include" -DLIBXML2_LIBRARIES:PATH="C:\Program Files\libxml2\lib"
```

# Execution