# Repository 

## Folder Structure
```markdown
my_lang/
│
├── CMakeLists.txt
├── cmake/                     # helper cmake modules (optional later)
│
├── apps/                      # executables (entry points)
│   └── cli/
│       ├── main.cpp
│       └── CMakeLists.txt
│
├── features/                  # CORE: feature modules
│   ├── lexer/
│   │   ├── lexer.cpp
│   │   ├── lexer.hpp
│   │   └── CMakeLists.txt
│   │
│   ├── parser/
│   │   ├── parser.cpp
│   │   ├── parser.hpp
│   │   └── CMakeLists.txt
│   │
│   ├── ast/
│   │   ├── ast.cpp
│   │   ├── ast.hpp
│   │   └── CMakeLists.txt
│   │
│   ├── semantic/
│   │   ├── analyzer.cpp
│   │   ├── analyzer.hpp
│   │   └── CMakeLists.txt
│   │
│   ├── codegen/
│   │   ├── codegen.cpp
│   │   ├── codegen.hpp
│   │   └── CMakeLists.txt
│   │
│   └── diagnostics/           # errors, logging
│       ├── diagnostic.cpp
│       ├── diagnostic.hpp
│       └── CMakeLists.txt
│
├── core/                      # shared utilities (NOT features)
│   ├── utils/
│   ├── memory/
│   └── CMakeLists.txt
│
├── include/                   # optional public headers (if needed)
│
└── tests/                     # later
```