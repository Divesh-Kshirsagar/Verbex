# Control Flow

Rivet currently supports block-based `if`/`else` and `while`.

## `if` / `else`

Syntax:

```rivet
if (<expression>) {
	<statements>
} else {
	<statements>
}
```

### Current parser behavior

- `if` condition must be wrapped in parentheses.
- `then` and `else` are parsed as blocks (`{ ... }`) in the current implementation.
- `else` is optional.

### Truthiness in codegen

Conditions are lowered to integer comparison against zero:

- non-zero -> true
- zero -> false

## `while`

Syntax:

```rivet
while (<expression>) {
	<statements>
}
```

### Current parser behavior

- Condition must be in `(...)`.
- Body is parsed as a block.

### LLVM structure generated

Codegen creates three blocks:

1. condition block
2. loop body block
3. after-loop block

The body branches back to the condition block.

## Example

```rivet
int i = 0;

while (i < 10) {
	if (i == 5) {
		i = i + 2;
	} else {
		i = i + 1;
	}
}

i;
```

## Current Limitations

- No `break` / `continue` yet.
- No single-line non-block `if` body form in parser path right now.
- No `for` loop support yet.

