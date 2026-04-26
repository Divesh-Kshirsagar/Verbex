# Variables

This page describes variable behavior in the current Rivet implementation.

## Declaration Forms

Rivet currently supports `int` variables with two forms:

```rivet
int x;
int y = 42;
```

### Notes

- `int x;` is valid and defaults to `0` during codegen.
- `int y = <expression>;` evaluates the expression and stores the result.
- Declarations must end with `;`.

## Assignment

Assignment works as a binary expression with `=`:

```rivet
int i = 0;
i = i + 1;
```

Current rule: the left-hand side must be a declared variable.
If the left side is not a variable node, codegen reports an error.

## Reading Variables

Using a variable in an expression generates a load from its stack slot:

```rivet
int a = 7;
int b = 3;
a + b;
```

## Scope Model (Current)

Variables are stored in a shared name map for codegen.
Practical implication in the current prototype:

- Redeclaration and shadowing rules are not fully formalized yet.
- Keep names unique in small programs to avoid confusion.

## Supported Expression Operators with Variables

- Arithmetic: `+`, `-`, `*`, `/`
- Equality: `==`, `!=`
- Relational: `<`, `>`
- Keyword logical/bitwise: `and`, `or`, `lsft`, `rsft`

## Example

```rivet
int x = 10;
int y = 2;

x = x + y;
x = x lsft 1;
x;
```

