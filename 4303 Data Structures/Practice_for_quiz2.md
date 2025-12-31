# Practice for Quiz 02: Data Structures

## Question Pattern
1.  **Algorithmic Simulation:** Step-by-step tracing of algorithms (like Quiz 01 Prefix evaluation).
2.  **Pseudo Code:** Logic for applying a specific Data Structure to solve a problem.

---

## Part 1: Algorithmic Simulations

### Topic: Stacks (Prefix/Postfix/Infix)

**Problem 1: Infix to Postfix Conversion**
Convert the following Infix expression to Postfix notation. Show the status of the **Stack** and the **Output String** at each step.
**Expression:** `K + L - M * N + (O ^ P) * W / U / V * T + Q`

*Tip: Remember the precedence: `^` (highest, R-L), `* /` (medium, L-R), `+ -` (lowest, L-R).*

**Problem 2: Prefix Evaluation**
Evaluate the following Prefix expression. Show the Stack status at each step.
**Expression:** `- + * 2 3 5 / ^ 2 3 4`

*Steps:*
1.  Scan from **Right to Left**.
2.  Push operands.
3.  When operator is found, Pop 2 operands, compute, Push result.

**Problem 3: Postfix Evaluation**
Evaluate the following Postfix expression. Show the Stack status.
**Expression:** `10 2 8 * + 3 -`

---

### Topic: Queues (Circular Queue & Deque)

**Problem 4: Circular Queue Tracing**
Consider a Circular Queue with a capacity (`MAX_SIZE`) of **5**.
Initial State: `FRONT = -1`, `REAR = -1`.
Trace the values of `FRONT`, `REAR`, and the **Queue Content** after the following operations:
1.  Enqueue(10)
2.  Enqueue(20)
3.  Enqueue(30)
4.  Dequeue()
5.  Enqueue(40)
6.  Enqueue(50)
7.  Enqueue(60) *(Check for Overflow)*
8.  Dequeue()
9.  Enqueue(70)

*Visual Aid:*
Remember `REAR = (REAR + 1) % SIZE`.

**Problem 5: Deque Operations**
Assume a Deque allows insertion and deletion at both ends. Trace the contents:
1.  `push_front(A)`
2.  `push_back(B)`
3.  `push_front(C)`
4.  `pop_back()`
5.  `push_back(D)`
6.  `pop_front()`

---

### Topic: Trees (Traversals & Construction)

**Problem 6: Tree Traversals**
Given the following Binary Tree:

```mermaid
graph TD
    A((A)) --> B((B))
    A --> C((C))
    B --> D((D))
    B --> E((E))
    C --> F((F))
    C --> G((G))
    E --> H((H))
    E --> I((I))
```

Determine the output for:
1.  **Pre-order Traversal** (Root-Left-Right)
2.  **In-order Traversal** (Left-Root-Right)
3.  **Post-order Traversal** (Left-Right-Root)
4.  **Level-order Traversal** (BFS)

**Problem 7: Tree Reconstruction**
Construct the unique Binary Tree from the following two traversals. Draw the final tree.
*   **In-order:** `D B H E I A F C G`
*   **Pre-order:** `A B D E H I C F G`

*Strategy:* Use Pre-order to find the Root (`A`), then use In-order to split into Left Subtree (`D B H E I`) and Right Subtree (`F C G`). Repeat recursively.

**Problem 8: Huffman Coding**
Construct the Huffman Tree and determine the binary codes for the following characters and their frequencies:
*   **a:** 5
*   **b:** 9
*   **c:** 12
*   **d:** 13
*   **e:** 16
*   **f:** 45

---

### Topic: Binary Search Trees (BST)

**Problem 9: BST Construction & Deletion**
1.  Insert the following keys (in this order) into an initially empty BST:
    `50, 30, 20, 40, 70, 60, 80`
2.  Draw the resulting tree.
3.  **Delete Node 50** (Root). Show the tree after deletion.
    *(Hint: 50 has two children. You must replace it with its **In-order Predecessor** (Max of Left) or **Successor** (Min of Right).)*

---

## Part 2: Pseudo Code Applications

### Application 1: Parentheses Balancing (Stack)
**Scenario:** You are building a compiler. You need to verify if the braces in a source code file are balanced.
**Task:** Write pseudo code for a function `isBalanced(expression)` that returns `true` or `false`.
*   Supported pairs: `()`, `{}`, `[]`.
*   **Data Structure:** Stack.

```text
Function isBalanced(string exp):
    Create empty Stack S
    For each character C in exp:
        If C is '(', '{', or '[':
            Push C to S
        Else If C is ')', '}', or ']':
            If S is Empty -> Return False
            TopChar = Pop S
            If (C is ')' AND TopChar != '(') OR ... (check other pairs):
                Return False
    If S is Empty -> Return True
    Else -> Return False
```

### Application 2: Breadth-First Search (Queue)
**Scenario:** You need to print all nodes of a tree level-by-level (e.g., for analyzing network topology depth).
**Task:** Write pseudo code for Level Order Traversal.
*   **Data Structure:** Queue.

```text
Function LevelOrder(Node root):
    If root is NULL -> Return
    Create Queue Q
    Enqueue(Q, root)
    
    While Q is NOT Empty:
        Current = Dequeue(Q)
        Print Current.Data
        
        If Current.Left != NULL -> Enqueue(Q, Current.Left)
        If Current.Right != NULL -> Enqueue(Q, Current.Right)
```

### Application 3: Palindrome Checker (Deque)
**Scenario:** Check if a given string is a palindrome (reads same forwards and backwards).
**Task:** Write pseudo code using a Deque.

```text
Function isPalindrome(string s):
    Create Deque D
    For each char C in s:
        Push_Back(D, C)
        
    While Size(D) > 1:
        FrontChar = Pop_Front(D)
        BackChar = Pop_Back(D)
        If FrontChar != BackChar -> Return False
        
    Return True
```

### Application 4: BST Insertion (Iterative)
**Scenario:** Recursive functions can cause Stack Overflow on deep trees. You need an iterative version of BST insertion.
**Task:** Write pseudo code for `insertIterative(root, value)`.

```text
Function insertIterative(root, value):
    NewNode = CreateNode(value)
    If root is NULL:
        root = NewNode
        Return

    Current = root
    Parent = NULL

    While Current is NOT NULL:
        Parent = Current
        If value < Current.Data:
            Current = Current.Left
        Else:
            Current = Current.Right
            
    If value < Parent.Data:
        Parent.Left = NewNode
    Else:
        Parent.Right = NewNode
```
