# Rivet Language Docs

Rivet is a small, LLVM-backed systems language prototype focused on readable syntax and explicit control.
These docs describe the current implementation in this repository so you can quickly understand what works today.

## What Rivet Currently Supports

- Integer literals and integer variables (`int`)
- Variable declarations with optional initialization
- Expression statements (for example, `a + b;`)
- Arithmetic operators: `+`, `-`, `*`, `/`
- Comparisons: `==`, `!=`, `<`, `>`
- Bitwise/logical keyword operators: `and`, `or`, `lsft`, `rsft`
- Assignment with `=` to declared variables
- `if` / `else` blocks
- `while` loops
- Function-call expressions (`name(arg1, arg2)`)
- Module imports with `import module_name;`
- LLVM IR generation to a synthetic entry function `__rivet_entry`

## What Is Partially Implemented or Planned

- `fun` and `return` tokens exist in the lexer, but function declaration parsing is not part of the current parser flow.
- Unary expression codegen is not implemented.
- Arrays are not implemented yet.
- Import resolution currently tries:
	- `lib/<module>.rvt`
	- `../lib/<module>.rvt` (fallback for build-directory execution)

## Typical Compile Flow

1. **Lexing**: source file is tokenized with line/column tracking.
2. **Parsing**: recursive-descent parser builds AST nodes.
3. **AST dump (optional)**: run with `--dump-ast` to inspect parse output.
4. **Codegen**: AST emits LLVM IR into module `Rivet Bare Metal Module`.
5. **IR print**: module is printed to stdout.

## Quick Example

```rivet
import dummy;

int i = 0;
while (i < 3) {
		i = i + 1;
}

i + imported_x;
```

Run from `build/`:

```bash
./rivet ../tests/import_dummy_test.rvt --dump-ast
```

## Reading Guide

- Start with **Language Basics** for day-to-day syntax.
- Use **Reference** for compact grammar and keyword tables.
- Use **Internals** to understand parser and LLVM backend behavior.

