# Internals Overview

This page documents the actual compiler pipeline as implemented in this repository.

## High-Level Architecture

Rivet currently uses a classic front-end + LLVM IR backend design:

1. **Lexer** (`src/Lexer.cpp`)
2. **Parser** (`src/Parser.cpp`)
3. **AST** (`include/Rivet/AST.h`, `src/AST.cpp`)
4. **Codegen Context** (`include/Rivet/CodeGen.h`, `src/CodeGen.cpp`)
5. **Driver** (`src/main.cpp`)

## Lexer

The lexer reads a file stream and returns integer tokens.

- Keywords are negative enum values (for example `tok_if`, `tok_import`).
- Punctuation/operators such as `+`, `=`, `<`, `(` are returned as ASCII values.
- Supports line comments `// ...`.
- Tracks `CurrentLine` and `CurrentColumn` for diagnostics.

## Parser

Parser is recursive descent with operator-precedence parsing for binary expressions.

### Statement entry points

Current statement parsing includes:

- `import <id>;`
- variable declarations (`int ...`)
- `if (...) { ... } [else { ... }]`
- `while (...) { ... }`
- blocks `{ ... }`
- expression statements
- empty statement `;`

### Expression parsing

- primary: number, identifier/call, parenthesized expression
- binary RHS parser (`ParseBinOpRHS`) with precedence table

### Import flow

`ParseImport` parses module name, avoids duplicate imports, and recursively parses imported source file into an `ImportAST` node.

Path strategy currently:

1. `lib/<module>.rvt`
2. fallback `../lib/<module>.rvt`

## AST Layer

Main nodes currently present:

- `NumberAST`
- `VariableAST`
- `VariableDeclAST`
- `BinaryOpAST`
- `BlockAST`
- `IfAST`
- `WhileAST`
- `CallAST`
- `ImportAST`

Each node provides:

- `dump()` for debug tree output
- `codegen()` for LLVM generation

## Driver (`main`)

The driver:

1. Loads source file.
2. Parses to top-level AST node list.
3. Optionally dumps AST.
4. Creates LLVM module context.
5. Builds synthetic entry function `__rivet_entry`.
6. Codegens each top-level node.
7. Emits `ret` if current block has no terminator.
8. Prints full LLVM IR.

