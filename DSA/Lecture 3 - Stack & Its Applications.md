---
course: CSE 4303 - Data Structures
lecture: 3
date: 2025-11-21
tags:
  - data-structures
  - Stack
  - LIFO
  - CS
  - Algorithms
---
---

## 1. Introduction to Stacks
A **Stack** is a linear data structure that follows a specific order for insertion and deletion.

> [!abstract] The Rule: LIFO
> **Last In First Out.**
> The element inserted last is the first one to be removed.

**Real World Analogies:**
*   A stack of cafeteria trays.
*   A stack of books on a desk.
*   The "Undo" button in text editors.

---

## 2. The Stack ADT (Abstract Data Type)
The stack defines the following interface:

### Primary Operations
1.  **Push(x)**: Adds element $x$ to the top of the stack.
2.  **Pop()**: Removes the top element from the stack.

### Auxiliary Operations
1.  **Peek() / Top()**: Returns the top element *without* removing it.
2.  **isEmpty()**: Returns `true` if the stack contains no elements.
3.  **isFull()**: Returns `true` if the stack cannot accept more elements (implementation specific).

---

## 3. Implementations

### A. Array-Based Implementation
Uses a simple array and a variable `TOP` to track the last inserted element.
*   **MAX_SIZE**: Fixed capacity.
*   **Initialization**: `TOP = -1`.

**Operations:**
*   **Push**: Increment `TOP`, then add data. *Corner case: Overflow (Array full).*
*   **Pop**: Return data at `TOP`, then decrement `TOP`. *Corner case: Underflow (Empty).*

```c
// Push Algorithm
IF TOP == MAX_SIZE - 1
    Print "OVERFLOW"
ELSE
    TOP = TOP + 1
    STACK[TOP] = item

// Pop Algorithm
IF TOP == -1
    Print "UNDERFLOW"
ELSE
    DATA = STACK[TOP]
    TOP = TOP - 1
    Return DATA
```

### B. Linked List-Based Implementation
Uses a Linked List to avoid fixed size limitations. The **HEAD** of the list acts as the **TOP** of the stack.
*   **Push**: Insert at Head ($O(1)$).
*   **Pop**: Delete at Head ($O(1)$).

```c
// Push Algorithm
NewNode = malloc()
NewNode->Data = item
NewNode->Next = TOP
TOP = NewNode

// Pop Algorithm
IF TOP == NULL
    Error "Underflow"
Temp = TOP
TOP = TOP->Next
FREE Temp
```

### C. Comparison: Array vs. Linked List

| Feature | Array Stack | Linked Stack |
| :--- | :--- | :--- |
| **Size** | Fixed (Static) | Dynamic (Grows/Shrinks) |
| **Efficiency** | $O(1)$ (Very Fast) | $O(1)$ (Pointer overhead) |
| **Memory** | No pointer overhead | Extra memory for pointers |
| **Limits** | Stack Overflow likely | Limit is System RAM |

> [!TIP] Key Takeaway
> Use **Array** implementation if you know the maximum size in advance.
> Use **Linked** implementation for flexibility.

---

## 4. Applications of Stacks

### 1. Reversing a Data Series
The LIFO property naturally reverses any sequence of data.
**Algorithm:**
1.  Read elements (String, Array, List) and **Push** them onto the stack.
2.  **Pop** elements one by one until empty.
3.  Store/Print the popped elements.
*   *Example:* Input "HELLO" $\rightarrow$ Stack: [H, E, L, L, O] $\rightarrow$ Pop: "OLLEH".

### 2. Parentheses Balancing / Checker
Check if an expression has balanced delimiters: `()`, `{}`, `[]`.
**Algorithm:**
1.  Scan string left to right.
2.  If **Opening** `( { [`: **Push** onto stack.
3.  If **Closing** `) } ]`:
    *   If Stack Empty $\rightarrow$ **Error**.
    *   Else, **Pop**. If popped char doesn't match closing type $\rightarrow$ **Error**.
4.  End of string: If Stack NOT Empty $\rightarrow$ **Error** (Missing closing bracket).

### 3. Expression Notations
*   **Infix:** Operator *between* operands (e.g., $A + B$). Human readable.
*   **Postfix (Reverse Polish):** Operator *after* operands (e.g., $AB+$). Machine friendly, no parentheses needed.
*   **Prefix (Polish):** Operator *before* operands (e.g., $+AB$).

#### Operator Hierarchy
| Precedence | Operator | Associativity |
| :---: | :--- | :--- |
| **1 (High)** | `( )` | - |
| **2** | `^` (Exponentiation) | **Right to Left** |
| **3** | `*`, `/`, `%` | Left to Right |
| **4 (Low)** | `+`, `-` | Left to Right |

### 4. Infix to Postfix Conversion
**Algorithm:**
1.  Push `(` onto stack, add `)` to end of infix expression.
2.  Scan expression:
    *   If `(`: Push to stack.
    *   If **Operand**: Add to postfix output.
    *   If `)`: Pop and output operators until `(` is found. Discard `(`.
    *   If **Operator**:
        *   Pop operators from stack that have **$\ge$ precedence** than the current operator.
        *   Push current operator.
        *   *Note on Associativity:* 
	        * For **Right-to-Left** (`^`), if precedence is equal, **PUSH** (do not pop). 
	        * For **Left-to-Right**, if precedence is equal, **POP**.

> **Class Exercise:**
> Convert: $A - (B / C + ( D \% E * F ) / G) * H$

### 5. Evaluating Postfix
Computers prefer Postfix because it eliminates precedence rules during calculation.
**Algorithm:**
1.  Scan Postfix expression left to right.
2.  If **Operand**: Push to stack.
3.  If **Operator**:
    *   Pop top two elements (Top is `A`, next is `B`).
    *   Calculate `B Operator A`.
    *   Push result back to stack.
4.  Final result is on top of the stack.

### 6. Infix to Prefix
**Strategy:** Reuse Infix $\rightarrow$ Postfix logic.
1.  **Reverse** the Infix string.
2.  **Swap brackets**: Change `(` to `)` and `)` to `(`.
3.  Convert modified string to **Postfix**.
4.  **Reverse** the resulting Postfix string to get Prefix.

### 7. Evaluating Prefix
Similar to Postfix, but scan from **Right to Left**.
**Algorithm:**
1.  Scan expression **Right to Left**.
2.  If **Operand**: Push to stack.
3.  If **Operator**:
    *   Pop top two elements (`Op1`, `Op2`).
    *   Calculate `Op1 Operator Op2` (*Note: order preserves original flow*).
    *   Push Result.

### 8. Recursion
A function calling itself.
*   **System Stack**: Uses the stack to manage function calls.
*   **Activation Record (Stack Frame)**: Pushed every time a function is called. Contains:
    *   Local variables.
    *   Return address.
    *   Parameters.

---

## References
*   **Textbook**: *Data Structures Using C*, 2nd Edition, Reema Thareja.
*   **Chapters**: 7.1, 7.2, 7.3, 7.4, 7.5, 7.7.