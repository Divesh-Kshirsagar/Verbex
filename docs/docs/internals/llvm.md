# LLVM Backend Details

This page explains how Rivet lowers language constructs into LLVM IR today.

## Module and Entry Function

Codegen initializes:

- `LLVMContext`
- `IRBuilder<>`
- `Module` named `Rivet Bare Metal Module`

Top-level code is emitted into:

```llvm
define i32 @__rivet_entry() {
entry:
	...
}
```

## Variable Lowering

Declaration:

```rivet
int x = 7;
```

Becomes roughly:

```llvm
%x = alloca i32
store i32 7, ptr %x
```

Variable read uses `load`.

## Binary Operators

Current mapping:

- `+` -> `CreateAdd`
- `-` -> `CreateSub`
- `*` -> `CreateMul`
- `/` -> `CreateSDiv`
- `and` -> `CreateAnd`
- `or` -> `CreateOr`
- `lsft` -> `CreateShl`
- `rsft` -> `CreateAShr`
- `==` -> `icmp eq` then zero-extend to `i32`
- `!=` -> `icmp ne` then zero-extend to `i32`
- `<` -> `icmp slt` then zero-extend to `i32`
- `>` -> `icmp sgt` then zero-extend to `i32`
- `=` -> `store` into variable slot and return RHS value

## Control Flow Lowering

### If/Else

If creates blocks:

- `then`
- `else`
- `ifcont`

Condition is tested against zero for branch selection.

### While

While creates blocks:

- `cond`
- `loop`
- `afterloop`

Flow:

1. branch to `cond`
2. evaluate condition
3. branch to `loop` or `afterloop`
4. loop body branches back to `cond`

## Imports and IR

`ImportAST::codegen()` codegens all imported AST nodes in sequence before continuing with the importing file.
This effectively injects imported declarations/statements into the same module.

## Current Backend Limitations

- Unary operations are not lowered yet.
- More advanced type system and arrays are not implemented.
- Function declaration pipeline is incomplete in parser/codegen integration.

