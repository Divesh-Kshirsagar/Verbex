# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <map>



// Token Definitions
// We use negative numbers so they never collide with ASCII characters (0-255)
// like '+', '-', '=', '(', '{', etc., which are returned as their raw ASCII value.
enum Token {
    tok_eof = -1,

    // Dynamic Tokens
    tok_identifier = -2,
    tok_number = -3,

    // Memory & Types
    tok_int = -10,
    tok_void = -11,
    tok_ref = -12,
    tok_address_of = -13,
    tok_deref = -14,

    // Logical & Bitwise
    tok_and = -20,
    tok_or = -21,
    tok_not = -22,
    tok_lsft = -23,
    tok_rsft = -24,
    tok_eq = -25, // '=='
    tok_neq = -26, // '!='

    // Control Flow
    tok_if = -30,
    tok_else = -31,
    tok_while = -32,
    tok_fun = -33,
    tok_return = -34
};

