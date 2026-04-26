# Rivet
Rivet is a statically typed, AOT-compiled programming language engineered specifically for bare-metal embedded systems. Designed as a strict C-subset, Rivet targets the ARM Cortex-M0 via the LLVM compiler infrastructure. 

It strips away the archaic syntax of C, replacing symbols with highly readable, verbose keywords and procedural abstractions, while retaining the raw execution speed and memory control required for constrained microcontrollers.

## Core Features

### ⚡ Bare-Metal LLVM Backend
Rivet is completely AOT (Ahead-Of-Time) compiled. There is no JIT, no Virtual Machine, and no runtime overhead. The compiler's front-end translates Rivet syntax into LLVM Intermediate Representation (IR), which is then aggressively optimized and emitted as raw Cortex-M0 machine code (`.o` / `.bin`). 

### 🧠 Agentic-First Hardware Mapping
In traditional embedded C, developers waste hours reading datasheet memory maps to find hexadecimal GPIO addresses. Rivet is designed to be agent-friendly. 
The compiler accepts a `board.json` file generated directly by an AI Agent reading the chip's Reference Manual. The developer simply writes `make_pin_output(13)`, and the Rivet compiler cross-references the JSON map to emit the raw LLVM `store` instructions to the correct physical silicon register.

### 🛡️ Explicit, Readable Memory Control (No GC)
Embedded systems cannot afford the latency or RAM overhead of a Garbage Collector. Rivet provides direct memory access (pointers) but replaces the confusing C-style `*` and `&` symbols with strict, verbose keywords:
* `ref` (Pointer type declaration)
* `address_of` (Get memory address)
* `deref` (Access value at address)

### 🎯 Rust-Style Diagnostic Errors
Most beginner compilers fail silently or throw generic syntax errors. Rivet's Lexer tracks exact line and column numbers, outputting highly verbose, visually formatted error messages with carets (`^`) pointing to the exact point of failure. This guarantees rapid debugging and is structured to be easily parsed by AI coding assistants.

## Built-In Hardware Intrinsics
To abstract Memory-Mapped I/O (MMIO), Rivet natively supports the following procedural built-ins inside the LLVM IR generation phase:
* `make_pin_output(pin)` / `make_pin_input(pin)`
* `set_pin_high(pin)` / `set_pin_low(pin)`
* `read_pin(pin)`
* `delay_cycles(cycles)`

## Module Imports
Rivet supports module imports using the `import` statement.

### Syntax
```rivet
import math;
import gpio;
```

### Resolution behavior
An import is resolved by module name to a source file at:

* `lib/<module_name>.rvt`

Examples:

* `import math;` -> `lib/math.rvt`
* `import board;` -> `lib/board.rvt`

Duplicate imports are ignored after the first successful import.

## Lexical Tokens & Keywords
Rivet minimizes cryptic symbols. Keywords return negative integer token values (to avoid collision), while standard symbols return their native ASCII integer equivalents.

### Memory & Types
| Keyword | Token Return | Behavior |
|---------|--------------|----------|
| `int` | -10 | 32-bit integer declaration |
| `void` | -11 | Null return type |
| `ref` | -12 | Declares a memory reference (pointer) |
| `address_of` | -13 | Gets the memory address of a variable |
| `deref` | -14 | Dereferences a memory address |

### Logical & Bitwise Operators
| Keyword / Symbol | Token Return | Behavior |
|------------------|--------------|----------|
| `and` | -20 | Logical AND |
| `or` | -21 | Logical OR |
| `not` | -22 | Logical NOT |
| `lsft` | -23 | Bitwise Left Shift |
| `rsft` | -24 | Bitwise Right Shift |
| `==` | -25 | Equality Comparison |
| `=` | 61 (ASCII) | Assignment |

### Conditionals & Control Flow
| Keyword | Token Return | Behavior |
|---------|--------------|----------|
| `if` | -30 | Standard conditional |
| `else` | -31 | Fallback conditional |
| `while` | -32 | Pre-condition loop |
| `fun` | -33 | Function declaration |
| `return`| -34 | Return from execution |
| `import`| -35 | Import Libraries|

## Example: Agentic Hardware Implementation

```rivet
// Blink an LED based on a button press
int led_pin = 13;
int btn_pin = 2;

make_pin_output(led_pin);
make_pin_input(btn_pin);

while (1) {
    if (read_pin(btn_pin) == 1 and not false) {
        set_pin_high(led_pin);
        delay_cycles(50000);
    } else {
        set_pin_low(led_pin);
    }
}
```

## Implementation Roadmap
1. **Architecture & CMake Setup:** Link LLVM 14+ and configure ARM cross-compilation targets.
2. **Lexical Analysis:** Implement state-machine Lexer with line/column tracking.
3. **AST Construction:** Build recursive descent parser and Abstract Syntax Tree.
4. **IR Generation:** Implement `codegen()` to translate AST into LLVM IR.
5. **Agentic JSON Parser:** Integrate `nlohmann/json` to parse AI-generated hardware maps.
6. **MMIO Intrinsics:** Hook `set_pin_high` etc., into raw LLVM `store` instructions.
7. **Target Emission:** Emit Cortex-M0 `.o` binary using LLVM PassManager.
8. **Hardware Demo:** Flash a 7-Segment Multiplexed Display written in Rivet.
