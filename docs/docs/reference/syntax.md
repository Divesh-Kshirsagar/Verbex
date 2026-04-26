# Syntax Reference

This page is a practical syntax reference for the current Rivet implementation.

## Program Shape

A file can contain top-level items such as:

- import statements
- variable declarations
- control-flow statements
- expression statements

## Statements

### Import

```rivet
import dummy;
```

### Variable declaration

```rivet
int x;
int y = 10;
```

### If / Else

```rivet
if (x == 0) {
	x = x + 1;
} else {
	x = x + 2;
}
```

### While

```rivet
while (x < 10) {
	x = x + 1;
}
```

### Expression statement

```rivet
x + y;
call_me(x);
```

### Empty statement

```rivet
;
```

## Expressions

Primary forms:

- number literal
- identifier
- function call
- parenthesized expression

Supported binary operators:

- assignment: `=`
- relational: `<`, `>`
- equality: `==`, `!=`
- arithmetic: `+`, `-`, `*`, `/`
- keyword operators: `and`, `or`, `lsft`, `rsft`

## Calls

```rivet
sum(a, b, 3);
```

Arguments are comma-separated expressions.

## Notes on Current Parsing Rules

- Conditions for `if`/`while` require parentheses.
- Bodies are currently handled as block forms.
- Every declaration/statement above ends with `;` except block/control structures.

