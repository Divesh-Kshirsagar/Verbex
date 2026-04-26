# Keywords and Tokens

Rivet uses negative integer token values for language keywords and dynamic token categories.
Single-character punctuation/operators are returned as ASCII integer values.

## Dynamic Tokens

| Category | Token Value | Meaning |
|---|---:|---|
| `identifier` | `-2` | Variable/function/module names |
| `number` | `-3` | Integer literal |

## Types and Memory Keywords

| Keyword | Token Value | Status |
|---|---:|---|
| `int` | `-10` | Implemented |
| `void` | `-11` | Tokenized; parser integration limited |
| `ref` | `-12` | Tokenized; parser integration limited |
| `address_of` | `-13` | Tokenized; parser integration limited |
| `deref` | `-14` | Tokenized; parser integration limited |

## Logical and Bitwise Keywords

| Keyword | Token Value | Notes |
|---|---:|---|
| `and` | `-20` | Parsed as binary operator |
| `or` | `-21` | Parsed as binary operator |
| `not` | `-22` | Token exists; unary path not fully wired in codegen |
| `lsft` | `-23` | Parsed as shift-left-like operator |
| `rsft` | `-24` | Parsed as arithmetic shift-right-like operator |
| `==` | `-25` | Equality compare |
| `!=` | `-26` | Not-equal compare |

## Control/Module Keywords

| Keyword | Token Value | Status |
|---|---:|---|
| `if` | `-30` | Implemented |
| `else` | `-31` | Implemented |
| `while` | `-32` | Implemented |
| `fun` | `-33` | Tokenized; full function-declaration flow is in progress |
| `return` | `-34` | Tokenized; return statement flow is in progress |
| `import` | `-35` | Implemented |

## ASCII Operator Tokens

These are returned directly as character code values by the lexer:

- `=` (`61`)
- `<` (`60`)
- `>` (`62`)
- `+` (`43`)
- `-` (`45`)
- `*` (`42`)
- `/` (`47`)
- `(`, `)`, `{`, `}`, `,`, `;`

This is why AST debug output may show numbers like `43` for `+` and `61` for `=`.

