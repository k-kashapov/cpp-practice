# Task 1
## Task
_Justify the situation with volatile nullptr_t using the standard._

```cpp
volatile std::nullptr_t a = nullptr;
int *b;
b = a;
```

### Clang:
```assembly
mov qword ptr [rsp - 8], 0
xor eax, eax
ret
```
### GCC:
```assembly
mov QWORD PTR [rsp-8], 0
mov rax, QWORD PTR [rsp-8]
mov eax, 0
ret
```

## Explanation

Variable `a` is an lvalue which is converted to an rvalue in expression `b = a`. The C++ 23 standard says about that

### [7.3.2] Lvalue-to-rvalue conversion:
The result of the conversion is determined according to the following rules:
    — (3.1) If **T** is _cv_ `std::nullptr_t`, the result is a null pointer constant (7.3.12).
    [Note 1 : Since the conversion does not access the object to which the glvalue refers, there is **no side effect even
    if T is volatile-qualified** (6.9.1), and the glvalue can refer to an inactive member of a union (11.5). — end note]

This means that no side effect should be produced when reading from `a`. This means that gcc does not comply with this point of C++ standard. The correct version of this code is Clang's.

# Task 3

## Task

_Find how to write proper protection code for_
```cpp
int foo(int *a, int base, int off) {
    return a[base + off];
}
```

## Solution

```cpp
#include <limits>

int foo(int *a, int base, int off) {
    if (base > 0) {
        if ((std::numeric_limits<int>::max() - base) < off) {
            return 0x0BAD;
        }
    } else {
        if ((std::numeric_limits<int>::min() - base) > off) {
            return 0x0BAD;
        }
    }

    int res = base + off;

    if (res < 0) {
        return 0x0BAD;
    }

    return a[res];
}
```
