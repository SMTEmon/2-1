# Modern C++ Concepts Guide for Drim Lang

This guide explains the specific C++ Standard Library (STL) features used in the Drim Lang interpreter. These features help manage memory automatically and handle data types safely.

---

## 1. `std::variant`, `std::holds_alternative`, and `std::get`

### The "Mystery Box"
In Drim Lang, a variable can hold different types of data (Integer, Double, String, or Boolean) at different times. `std::variant` is the type-safe way to handle this.

- **`std::variant`**: The box itself. It can hold exactly **one** value from a specific list of allowed types.
- **`std::holds_alternative`**: A check to see what type is currently inside the box without crashing.
- **`std::get`**: The function to retrieve the value.

### Why do we need it?
C++ is strongly typed. You cannot treat a string as a number. You must verify the type before using it.

### Code Example
```cpp
#include <variant>
#include <string>
#include <iostream>

// define the box
using Value = std::variant<int, std::string>;

int main() {
    Value v = "Hello"; 

    // SAFETY CHECK: "Does this box currently hold an integer?"
    if (std::holds_alternative<int>(v)) {
        // If yes, safely grab the integer
        int number = std::get<int>(v); 
        std::cout << number;
    } 
    else if (std::holds_alternative<std::string>(v)) {
        // If no, grab the string
        std::string text = std::get<std::string>(v);
        std::cout << text;
    }
}
```

**Rule:** If you call `std::get<int>(v)` when the variant actually holds a string, your program will crash. Always check with `holds_alternative` first!

---

## 2. `std::shared_ptr`

### The "Shared Document"
In older C++, you had to manually delete every object you created. `std::shared_ptr` is a "Smart Pointer" that manages memory for you using **Reference Counting**.

1. When you create an object, the "counter" is 1.
2. If you pass the pointer to another function, they share it. The "counter" becomes 2.
3. When a function finishes using it, the "counter" drops by 1.
4. When the "counter" hits **0** (nobody is using it anymore), the object deletes itself automatically.

### Why use it in the Interpreter?
The Abstract Syntax Tree (AST) is complex. An Expression (`Expr`) might be referenced by multiple parts of the program. `shared_ptr` ensures the memory stays valid as long as something needs it, and cleans it up when done.

### Code Example
```cpp
#include <memory>

// Creating a shared pointer to an integer with value 10
std::shared_ptr<int> ptr = std::make_shared<int>(10);
```

---

## 3. `std::unique_ptr`

### The "Exclusive Key"
This is a stricter version of `shared_ptr`.
- It owns the object **exclusively**.
- It cannot be copied, only moved.
- If the pointer is destroyed, the object is deleted immediately.

*Note: Drim Lang currently uses `shared_ptr` for simplicity, but `unique_ptr` is often used when an object definitely has only one owner.*

---

## 4. `std::dynamic_pointer_cast`

### The "Identity Check"
This is used heavily in `Interpreter.cpp`.

**The Problem:**
The parser treats everything as a generic `Expr` (Expression). The interpreter receives a `std::shared_ptr<Expr>`, but it needs to know the specific *kind* of expression (e.g., is it a number? a math operation? a variable?).
The generic `Expr` parent class doesn't have fields like `.left`, `.right`, or `.value`.

**The Solution:**
`std::dynamic_pointer_cast` attempts to cast the generic pointer to a specific child pointer.

- **Success:** Returns a valid pointer to the specific child type (allowing access to its fields).
- **Failure:** Returns `nullptr` (meaning the object was not that type).

### Code Example
```cpp
// 'expr' is a generic shared_ptr<Expr> passed to the function

// "Is this generic expression actually a BinaryExpr (like 1 + 2)?"
if (auto bin = std::dynamic_pointer_cast<BinaryExpr>(expr)) {
    // YES! It is a BinaryExpr.
    // Now we can access specific fields like 'left' and 'right'
    evaluate(bin->left);
    evaluate(bin->right);
} 
else if (auto num = std::dynamic_pointer_cast<LiteralExpr>(expr)) {
    // NO, but it IS a LiteralExpr.
    // Now we can access 'num->value'
    return num->value;
}
```

---

## Summary Cheat Sheet

| Tool | Analogy | Purpose |
| :--- | :--- | :--- |
| **`std::variant`** | Mystery Box | Holds one of several types (e.g., int OR string). |
| **`std::holds_alternative`** | X-Ray Vision | Checks what type is currently inside the variant. |
| **`std::get`** | The Hand | Extracts the value from the variant (must match the type). |
| **`std::shared_ptr`** | Google Doc | Keeps an object alive as long as anyone is using it. |
| **`std::dynamic_pointer_cast`**| ID Check | Checks if a generic parent object is actually a specific child type. |
