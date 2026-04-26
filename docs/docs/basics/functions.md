# Functions

This page separates what is supported today from what is planned.

## What Works Today

### Function call expressions

Parser supports calls in expression position:

```rivet
do_work();
mix(a, b, 3);
```

A call is parsed when an identifier is followed by `(`.
Arguments are parsed as comma-separated expressions.

### Call codegen behavior

During codegen, Rivet:

1. Looks up the callee by name in the LLVM module.
2. Verifies argument count.
3. Emits `call` instruction.

If function is missing or arity mismatches, codegen reports an error.

## Not Fully Enabled Yet

### Function declarations

Tokens for `fun` and `return` exist, and docs grammar mentions function declarations.
However, parser flow in the current implementation is focused on statements/imports/variables/control-flow.
Treat function declaration syntax as in-progress unless you add parser + AST + codegen paths for it.

## Practical Guidance

- Use calls only when callee functions are present in the LLVM module.
- For quick experiments, most current tests focus on top-level statements and generated `__rivet_entry`.

## Example Call Form

```rivet
import math;

int x = 7;
int y = 3;
add(x, y);
```

