## Question Pattern
1.  **Algorithmic Simulation:** Step-by-step tracing of algorithms.
2.  **Pseudo Code:** Logic for applying a specific Data Structure.

---

## Part 1: Stacks & Complexity (Lectures 1-3)

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

**Application 1: Parentheses Balancing (Stack)**
**Scenario:** You are building a compiler. You need to verify if the braces in a source code file are balanced.
**Task:** Write pseudo code for a function `isBalanced(expression)` that returns `true` or `false`.
*   Supported pairs: `()`, `{}`, `[]`.

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

### Topic: Advanced Linked Lists (XOR)

**Problem 5: XOR Linked List Traversal**
You are working with a memory-efficient **XOR Linked List**.
*   **Formula:** `Node->npx = Address(Prev) XOR Address(Next)`
*   **Memory Map:**
    *   **Node A (Addr 100):** `npx = 0 XOR 200`
    *   **Node B (Addr 200):** `npx = 100 XOR 300`
    *   **Node C (Addr 300):** `npx = 200 XOR 400`
    *   **Node D (Addr 400):** `npx = 300 XOR 0`

**Task:** You are currently at **Node C** (Address 300) and you arrived from **Node B** (Address 200).
1.  Calculate the address of the **Next Node** (D).
2.  Show the XOR calculation step-by-step.

---

## Part 2: Comprehensive Practice (Lectures 4-6)

### Topic: Queues & Deques (Lecture 4)

**Problem 6: Circular Queue Tracing**
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
*Visual Aid: Remember `REAR = (REAR + 1) % SIZE`.*

**Problem 7: Deque Operations**
Assume a Deque allows insertion and deletion at both ends. Trace the contents:
1.  `push_front(A)`
2.  `push_back(B)`
3.  `push_front(C)`
4.  `pop_back()`
5.  `push_back(D)`
6.  `pop_front()`

**Problem 8: Sliding Window Maximum (Hard)**
Given an array `arr = [1, 3, -1, -3, 5, 3, 6, 7]` and a window size $k=3$.
You need to find the maximum integer in each sliding window.
*   **Algorithm:** Use a **Deque** to store *indices* of useful elements.
*   **Task:** Trace the content of the Deque for every step.
    *   *Constraint:* The Deque must be maintained in **decreasing order** of values. Indices of elements that fall out of the window must be removed from the front.

**Problem 9: Queue using Stacks (Implementation)**
Design a Queue Data Structure using **only two Stacks** (`S1` and `S2`).
1.  Write Pseudo Code for `Enqueue(x)`.
2.  Write Pseudo Code for `Dequeue()`.
3.  What is the **Amortized Time Complexity** of the Dequeue operation?

**Problem 10: Circular Queue Mathematics**
In a Circular Queue implemented with an array of size `MAX = 10`, you are given the current values of `FRONT` and `REAR`. Calculate the number of elements currently in the queue.
*   **Formula:** `Count = (REAR - FRONT + MAX) % MAX + 1` (assuming Rear points to last element, Front points to first).
*   **Cases:**
    1.  `FRONT = 2`, `REAR = 5`
    2.  `FRONT = 8`, `REAR = 1`
    3.  `FRONT = 5`, `REAR = 4` (Is this empty or full? Explain based on your implementation choice).

**Problem 11: Palindrome Checker (Deque App)**
Write pseudo code using a Deque to check if a given string is a palindrome.

### Topic: Trees & BSTs (Lectures 5-6)

**Problem 12: Tree Traversals**
Given the following Binary Tree structure: `A -> (B, C)`, `B -> (D, E)`, `C -> (F, G)`, `E -> (H, I)`.
Determine the output for:
1.  **Pre-order Traversal** (Root-Left-Right)
2.  **In-order Traversal** (Left-Root-Right)
3.  **Post-order Traversal** (Left-Right-Root)
4.  **Level-order Traversal** (BFS)

**Problem 13: Tree Reconstruction**
Construct the unique Binary Tree from the following two traversals. Draw the final tree.
*   **In-order:** `D B H E I A F C G`
*   **Pre-order:** `A B D E H I C F G`

**Problem 14: Huffman Coding**
Construct the Huffman Tree and determine the binary codes for the following characters and their frequencies:
*   **a:** 5, **b:** 9, **c:** 12, **d:** 13, **e:** 16, **f:** 45

**Problem 15: BST Construction & Deletion**
1.  Insert keys: `50, 30, 20, 40, 70, 60, 80` into an empty BST.
2.  **Delete Node 50** (Root). Show the tree after deletion.
    *(Hint: 50 has two children. Replace with In-order Predecessor or Successor.)*

**Problem 16: BST Validation (Hard)**
Write pseudo code for a function `isValidBST(Node root)` that returns `true` if a binary tree is a valid Binary Search Tree.
*   **Challenge:** Simple local checks fail. You must pass down a range `(min, max)` to recursive calls.

**Problem 18: Search Trace & Comparison**
Given BST: `Root(50) -> L(30), R(70)`, `30 -> L(20), R(40)`, `70 -> L(60), R(80)`.
*   **Target:** Search for `65` (Not present).
*   **Task:** List comparisons. Compare efficiency with a Linked List.

**Problem 19: Lowest Common Ancestor (Challenge)**
Given a Binary Search Tree and two values $n1$ and $n2$ (where $n1 < n2$).
Write pseudo code to find the **Lowest Common Ancestor (LCA)**.
*   *Logic:* Since it's a BST, if both $n1$ and $n2$ are smaller than Root, LCA is in Left. If both are greater, LCA is in Right. If they split (one smaller, one larger), Root is the LCA.

**Problem 20: Diameter of a Tree (Challenge)**
The diameter of a tree is the number of nodes on the longest path between two leaves.
*   **Task:** Write pseudo code to find the diameter.
*   *Hint:* For every node, calculate height of left and right subtrees. `Diameter = Max(LeftHeight + RightHeight + 1)` over all nodes.

---

# Solutions

## Part 1: Stacks & Complexity

### Problem 1: Infix to Postfix Conversion

> **Solution:**
>
> | Symbol | Action | Stack Status | Output String |
> | :--- | :--- | :--- | :--- |
> | **K** | Print | Empty | `K` |
> | **+** | Push | `+` | `K` |
> | **L** | Print | `+` | `KL` |
> | **-** | Pop `+` (Precedence Equal, Assoc L-R), Push `-` | `-` | `KL+` |
> | **M** | Print | `-` | `KL+M` |
> | ***** | Push | `- *` | `KL+M` |
> | **N** | Print | `- *` | `KL+MN` |
> | **+** | Pop `*`, Pop `-` (Lower Precedence/Equal), Push `+` | `+` | `KL+MN*-` |
> | **(** | Push | `+ (` | `KL+MN*-` |
> | **O** | Print | `+ (` | `KL+MN*-O` |
> | **^** | Push | `+ ( ^` | `KL+MN*-O` |
> | **P** | Print | `+ ( ^` | `KL+MN*-OP` |
> | **)** | Pop until `(` | `+` | `KL+MN*-OP^` |
> | ***** | Push | `+ *` | `KL+MN*-OP^` |
> | **W** | Print | `+ *` | `KL+MN*-OP^W` |
> | **/** | Pop `*` (Equal, L-R), Push `/` | `+ /` | `KL+MN*-OP^W*` |
> | **U** | Print | `+ /` | `KL+MN*-OP^W*U` |
> | **/** | Pop `/` (Equal, L-R), Push `/` | `+ /` | `KL+MN*-OP^W*U/` |
> | **V** | Print | `+ /` | `KL+MN*-OP^W*U/V` |
> | ***** | Pop `/` (Equal, L-R), Push `*` | `+ *` | `KL+MN*-OP^W*U/V/` |
> | **T** | Print | `+ *` | `KL+MN*-OP^W*U/V/T` |
> | **+** | Pop `*`, Pop `+`, Push `+` | `+` | `KL+MN*-OP^W*U/V/T*+` |
> | **Q** | Print | `+` | `KL+MN*-OP^W*U/V/T*+Q` |
> | **End** | Pop remaining | Empty | `KL+MN*-OP^W*U/V/T*+Q+` |
>
> **Final Postfix Expression:** `KL+MN*-OP^W*U/V/T*+Q+`

### Problem 2: Prefix Evaluation

> **Solution:**
>
> | Step | Token | Stack Status (Top is Right) | Action |
> | :--- | :--- | :--- | :--- |
> | 1 | **4** | `[4]` | Push |
> | 2 | **3** | `[4, 3]` | Push |
> | 3 | **2** | `[4, 3, 2]` | Push |
> | 4 | **^** | `[4, 8]` | Pop 2, 3. Calc $2^3 = 8$. Push 8. |
> | 5 | **/** | `[2]` | Pop 8, 4. Calc $8/4 = 2$. Push 2. |
> | 6 | **5** | `[2, 5]` | Push |
> | 7 | **3** | `[2, 5, 3]` | Push |
> | 8 | **2** | `[2, 5, 3, 2]` | Push |
> | 9 | ***** | `[2, 5, 6]` | Pop 2, 3. Calc $2 * 3 = 6$. Push 6. |
> | 10 | **+** | `[2, 11]` | Pop 6, 5. Calc $6 + 5 = 11$. Push 11. |
> | 11 | **-** | `[9]` | Pop 11, 2. Calc $11 - 2 = 9$. Push 9. |
>
> **Final Result:** `9`

### Problem 3: Postfix Evaluation

> **Solution:**
>
> | Step | Token | Stack Status | Action |
> | :--- | :--- | :--- | :--- |
> | 1 | **10** | `[10]` | Push |
> | 2 | **2** | `[10, 2]` | Push |
> | 3 | **8** | `[10, 2, 8]` | Push |
> | 4 | ***** | `[10, 16]` | Pop 8, 2. Calc $2 * 8 = 16$. Push. |
> | 5 | **+** | `[26]` | Pop 16, 10. Calc $10 + 16 = 26$. Push. |
> | 6 | **3** | `[26, 3]` | Push |
> | 7 | **-** | `[23]` | Pop 3, 26. Calc $26 - 3 = 23$. Push. |
>
> **Final Result:** `23`

### Problem 5: XOR Linked List

> **Solution:**
> **Logic:** `npx(Current) = Address(Prev) XOR Address(Next)`
> Therefore, `Address(Next) = npx(Current) XOR Address(Prev)`
>
> 1.  **Current Node:** C (Address 300)
> 2.  **Previous Node:** B (Address 200)
> 3.  **npx(C):** `200 XOR 400` (Given in memory map)
> 4.  **Calculation:**
>     `Address(Next) = (200 XOR 400) XOR 200`
>     `Address(Next) = 400 XOR (200 XOR 200)`
>     `Address(Next) = 400 XOR 0`
>     `Address(Next) = 400` (Address of Node D)

## Part 2: Comprehensive Practice

### Problem 6: Circular Queue Tracing

> **Solution:**
> *Assumed Array indices: 0 to 4.*
>
> | Operation | Front (F) | Rear (R) | Queue Content `[0, 1, 2, 3, 4]` | Note |
> | :--- | :--- | :--- | :--- | :--- |
> | **Initial** | -1 | -1 | `[ , , , , ]` | Empty |
> | **1. Enq(10)** | 0 | 0 | `[10, , , , ]` | First Element |
> | **2. Enq(20)** | 0 | 1 | `[10, 20, , , ]` |  |
> | **3. Enq(30)** | 0 | 2 | `[10, 20, 30, , ]` |  |
> | **4. Deq()** | 1 | 2 | `[ , 20, 30, , ]` | 10 Removed |
> | **5. Enq(40)** | 1 | 3 | `[ , 20, 30, 40, ]` |  |
> | **6. Enq(50)** | 1 | 4 | `[ , 20, 30, 40, 50]` |  |
> | **7. Enq(60)** | 1 | 0 | `[60, 20, 30, 40, 50]` | Wrap around. **FULL** now (Next R == F). |
> | **8. Deq()** | 2 | 0 | `[60, , 30, 40, 50]` | 20 Removed |
> | **9. Enq(70)** | 2 | 1 | `[60, 70, 30, 40, 50]` | Wrap around |

### Problem 8: Sliding Window Maximum (Hard)

> **Solution:**
> *Deque invariant: Indices are stored such that values are in decreasing order.*
>
> 1.  **Index 0 (Val 1):** Deque: `[0]`
> 2.  **Index 1 (Val 3):** 3 > 1, pop 0. Push 1. Deque: `[1]`
> 3.  **Index 2 (Val -1):** -1 < 3, push 2. Deque: `[1, 2]`. **Window [0-2] Max: arr[1] = 3**
> 4.  **Index 3 (Val -3):** Remove index 0 (out of window). -3 < -1, push 3. Deque: `[1, 2, 3]`. **Window [1-3] Max: arr[1] = 3**
> 5.  **Index 4 (Val 5):** Remove index 1 (out). 5 > -3 (pop 3), 5 > -1 (pop 2). Push 4. Deque: `[4]`. **Window [2-4] Max: arr[4] = 5**
> 6.  **Index 5 (Val 3):** 3 < 5, push 5. Deque: `[4, 5]`. **Window [3-5] Max: arr[4] = 5**
> 7.  **Index 6 (Val 6):** Remove index 3 (out). 6 > 3 (pop 5), 6 > 5 (pop 4). Push 6. Deque: `[6]`. **Window [4-6] Max: arr[6] = 6**
> 8.  **Index 7 (Val 7):** Remove index 4 (out). 7 > 6 (pop 6). Push 7. Deque: `[7]`. **Window [5-7] Max: arr[7] = 7**
>
> **Result:** `3, 3, 5, 5, 6, 7`

### Problem 9: Queue using Stacks

> **Solution:**
>
> ```cpp
> // Enqueue Operation (Always push to S1)
> void Enqueue(x) {
>     S1.push(x);
> }
>
> // Dequeue Operation
> int Dequeue() {
>     // If both empty, queue is empty
>     if (S1.isEmpty() && S2.isEmpty()) return Error;
>
>     // If S2 is empty, move everything from S1 to S2
>     if (S2.isEmpty()) {
>         while (!S1.isEmpty()) {
>             S2.push(S1.pop());
>         }
>     }
>
>     // Pop from S2
>     return S2.pop();
> }
> ```
> **Amortized Time Complexity:** $O(1)$.
> *Reasoning:* Each element is pushed to S1 once, popped from S1 once, pushed to S2 once, and popped from S2 once. Total 4 operations per element. Averaged over $N$ elements, cost is constant.

### Problem 10: Circular Queue Mathematics

> **Solution:**
> *Note: The formula assumes standard array implementation where Rear points to the last inserted element.*
>
> 1.  **F=2, R=5:**
>     $Count = (5 - 2 + 10) % 10 + 1 = 13 % 10 + 1 = 3 + 1 = 4$.
> 2.  **F=8, R=1:**
>     $Count = (1 - 8 + 10) % 10 + 1 = 3 % 10 + 1 = 3 + 1 = 4$.
> 3.  **F=5, R=4:**
>     $Count = (4 - 5 + 10) % 10 + 1 = 9 % 10 + 1 = 10$.
>     *Interpretation:* Since Count == MAX, the queue is **FULL**.

### Problem 12: Tree Traversals

> **Solution:**
> **Tree Structure:**
> ```text
>       A
>     /   \
>    B     C
>   / \   / \
>  D   E F   G
>     / \
>    H   I
> ```
>
> 1.  **Pre-order (Root-L-R):** `A, B, D, E, H, I, C, F, G`
> 2.  **In-order (L-Root-R):** `D, B, H, E, I, A, F, C, G`
> 3.  **Post-order (L-R-Root):** `D, H, I, E, B, F, G, C, A`
> 4.  **Level-order:** `A, B, C, D, E, F, G, H, I`

### Problem 13: Tree Reconstruction

> **Solution:**
> 1.  **Root:** `A` (First in Pre-order).
> 2.  **Left Subtree (from In-order):** `D B H E I`
> 3.  **Right Subtree (from In-order):** `F C G`
> 4.  **Recursion on Left (`D B H E I`):**
>     *   Next Pre-order root is `B`.
>     *   Left of B (In-order): `D`. Right of B: `H E I`.
> 5.  **Recursion on Right (`F C G`):**
>     *   Next Pre-order root (after processing Left subtree) is `C`.
>     *   Left of C: `F`. Right of C: `G`.
> 6.  **Sub-recursion (`H E I`):**
>     *   Next Pre-order root is `E`.
>     *   Left of E: `H`. Right of E: `I`.
>
> **Final Tree:**
> ```text
>       A
>     /   \
>    B     C
>   / \   / \
>  D   E F   G
>     / \
>    H   I
> ```

### Problem 14: Huffman Coding

> **Solution:**
> **Steps:**
> 1.  Priority Queue: `[a:5, b:9, c:12, d:13, e:16, f:45]`
> 2.  Pop 5, 9. Sum = 14 (Node `ab`). Queue: `[c:12, d:13, ab:14, e:16, f:45]`
> 3.  Pop 12, 13. Sum = 25 (Node `cd`). Queue: `[ab:14, e:16, cd:25, f:45]`
> 4.  Pop 14, 16. Sum = 30 (Node `abe`). Queue: `[cd:25, abe:30, f:45]`
> 5.  Pop 25, 30. Sum = 55 (Node `X`). Queue: `[f:45, X:55]`
> 6.  Pop 45, 55. Sum = 100 (Root).
>
> **Tree Visual:**
> ```text
>         (100)
>        /     \
>     f(45)    (55)
>             /    \
>         (25)     (30)
>         /  \     /   \
>       c(12)d(13)(14) e(16)
>                 /  \
>               a(5) b(9)
> ```
> **Codes (Left=0, Right=1):**
> *   **f:** `0`
> *   **c:** `100`
> *   **d:** `101`
> *   **e:** `111`
> *   **a:** `1100`
> *   **b:** `1101`

### Problem 15: BST Deletion

> **Solution:**
> **Original Tree:**
> ```text
>       50
>     /    \
>    30    70
>   /  \  /  \
>  20  40 60 80
> ```
> **Deletion Strategy:**
> Node 50 has 2 children. Replace with **In-order Successor** (Min of Right Subtree) -> `60`.
> (Alternatively, Predecessor `40` is valid).
>
> **Tree After Deleting 50 (using Successor 60):**
> 1.  Replace 50 with 60.
> 2.  Delete 60 from its original position (Leaf node).
> ```text
>       60
>     /    \
>    30    70
>   /  \     \
>  20  40    80
> ```

### Problem 16: BST Validation

> **Solution:**
> ```text
> Function isValidBST(node, minVal, maxVal):
>     // Base Case: Empty tree is valid
>     If node is NULL:
>         Return True
>
>     // Check current node constraints
>     If node.value <= minVal OR node.value >= maxVal:
>         Return False
>
>     // Recursive Check
>     // Left child must be < current
>     // Right child must be > current
>     Return isValidBST(node.left, minVal, node.value) AND
>            isValidBST(node.right, node.value, maxVal)
>
> // Initial Call
> isValidBST(root, -Infinity, +Infinity)
> ```

### Problem 19: Lowest Common Ancestor (BST)

> **Solution:**
> ```text
> Function findLCA(root, n1, n2):
>     While root is NOT NULL:
>         // If both are smaller, LCA is in Left
>         If root.value > n1 AND root.value > n2:
>             root = root.left
>
>         // If both are larger, LCA is in Right
>         Else If root.value < n1 AND root.value < n2:
>             root = root.right
>
>         // If they split (one smaller, one larger) OR
>         // one matches the root, THIS is the LCA.
>         Else:
>             Return root
>     Return NULL
> ```

---

## Part 3: Graphs (Lecture 7 - Practice Later)

### Topic: Graphs (Lecture 7)

**Problem 21: Warshall’s Algorithm (Transitive Closure)**
Given the Adjacency Matrix:
```text
  A B C
A 0 1 0
B 0 0 1
C 1 0 0
```
Trace the construction of matrices $R^{(0)}$ to $R^{(3)}$. What is the connectivity?

**Problem 22: Adjacency Multi-list**
Draw the **Adjacency Multi-list** representation for undirected graph with Edges: `(A, B)`, `(A, C)`.
*   Show `Head` array and Edge Nodes `[Mark | V1 | V2 | Link1 | Link2]`.

**Problem 23: Topological Sort & Cycles**
Trace **Kahn's Algorithm** (In-Degree) on graph: `A->B`, `B->C`, `C->A`, `C->D`.
*   Explain why the algorithm fails (Cycle detection).

**Problem 24: Matrix to List Conversion**
Convert this Matrix to an Adjacency List:
```text
  0 1 2 3
0 0 1 0 1
1 0 0 1 0
2 1 0 0 0
3 0 0 1 0
```

**Problem 25: DFS Stack Simulation**
Perform DFS on the graph from Problem 24 starting at Node 0.
*   **Constraint:** Choose smaller index neighbor first.
*   **Task:** Show Stack status at every step.

**Problem 26: Bipartite Graph Check (Challenge)**
A graph is Bipartite if vertices can be divided into two disjoint sets $U$ and $V$ such that every edge connects a vertex in $U$ to one in $V$.
*   **Task:** Use BFS/DFS coloring logic (Red/Blue) to check if the graph `A-B, B-C, C-D, D-A` (Square) is bipartite. Then try `A-B, B-C, C-A` (Triangle).
*   *Logic:* If you meet a neighbor with the same color, it's NOT bipartite.

**Problem 27: Shortest Path in Unweighted Maze (Challenge)**
Given a 2D grid where `0` is a wall and `1` is a path. You start at `(0,0)` and want to reach `(N-1, M-1)`.
*   **Task:** Explain how **BFS** can find the shortest path length. Trace for a 3x3 grid.

### Graph Solutions

#### Problem 21: Warshall's Algorithm

> **Solution:**
> **$R^{(0)}$ (Initial Matrix):**
> ```text
>   A B C
> A 0 1 0
> B 0 0 1
> C 1 0 0
> ```
> **$R^{(1)}$ (Using Node A as intermediate):**
> *   `C->A->B` creates path `C->B`.
> ```text
>   A B C
> A 0 1 0
> B 0 0 1
> C 1 1 0  <-- Changed (C can reach B via A)
> ```
> **$R^{(2)}$ (Using Node B as intermediate):**
> *   `A->B->C` creates `A->C`.
> *   `C->B->C` creates `C->C` (Cycle).
> ```text
>   A B C
> A 0 1 1  <-- Changed (A->B->C)
> B 0 0 1
> C 1 1 1  <-- Changed (C->B->C)
> ```
> **$R^{(3)}$ (Using Node C as intermediate):**
> *   `A->C->A` creates `A->A`.
> *   `B->C->A` creates `B->A`.
> *   `B->C->B` creates `B->B`.
> ```text
>   A B C
> A 1 1 1
> B 1 1 1
> C 1 1 1
> ```
> **Connectivity:** Strongly Connected (All 1s).

#### Problem 23: Topological Sort & Cycles

> **Solution:**
> 1.  **Calculate In-Degrees:**
>     *   A: 1 (from C)
>     *   B: 1 (from A)
>     *   C: 1 (from B)
>     *   D: 1 (from C)
> 2.  **Queue Initialization:** Add nodes with In-Degree 0.
>     *   **Queue is Empty!**
> 3.  **Result:**
>     *   Since the Queue starts empty (or eventually becomes empty before processing all nodes), the algorithm terminates prematurely.
>     *   This confirms a **Cycle** exists (`A->B->C->A`), making Topological Sort impossible.

#### Problem 25: DFS Stack Simulation

> **Solution:**
> *Graph Edges:* `0->1`, `0->3`, `1->2`, `2->0`, `3->2`.
>
> 1.  **Start:** Push 0. Mark 0 visited. **Output: 0**. Stack: `[0]`
> 2.  **Neighbors of 0:** 1, 3. Pick 1.
> 3.  **Visit 1:** Push 1. Mark 1 visited. **Output: 1**. Stack: `[0, 1]`
> 4.  **Neighbors of 1:** 2. Pick 2.
> 5.  **Visit 2:** Push 2. Mark 2 visited. **Output: 2**. Stack: `[0, 1, 2]`
> 6.  **Neighbors of 2:** 0 (Visited). No unvisited neighbors.
> 7.  **Backtrack:** Pop 2. Stack: `[0, 1]`
> 8.  **Neighbors of 1:** All visited.
> 9.  **Backtrack:** Pop 1. Stack: `[0]`
> 10. **Neighbors of 0:** 1 (Visited), 3 (Unvisited). Pick 3.
> 11. **Visit 3:** Push 3. Mark 3 visited. **Output: 3**. Stack: `[0, 3]`
> 12. **Neighbors of 3:** 2 (Visited). No unvisited neighbors.
> 13. **Backtrack:** Pop 3. Stack: `[0]`
> 14. **Neighbors of 0:** All visited.
> 15. **End:** Pop 0. Stack Empty.
>
> **DFS Order:** `0 -> 1 -> 2 -> 3`

#### Problem 27: Shortest Path in Maze (BFS)

> **Solution:**
> **Why BFS?** BFS explores layer-by-layer. All nodes at distance `d` are processed before `d+1`. The first time we reach the target, it is guaranteed to be via the shortest path.
>
> **Trace:**
> 1.  **Queue:** `[(0,0, dist=0)]`. Visited: `{(0,0)}`
> 2.  **Pop (0,0):** Neighbors -> `(0,1)`. (Assume `(1,0)` is wall/0).
>     *   **Queue:** `[(0,1, dist=1)]`. Visited: `{(0,0), (0,1)}`
> 3.  **Pop (0,1):** Neighbors -> `(1,1)` (Down), `(0,2)` (Right-Wall/0).
>     *   **Queue:** `[(1,1, dist=2)]`. Visited: `+{(1,1)}`
> 4.  **Pop (1,1):** Neighbors -> `(1,2)` (Right).
>     *   **Queue:** `[(1,2, dist=3)]`. Visited: `+{(1,2)}`
> 5.  **Pop (1,2):** Neighbors -> `(2,2)` (Down). Target Found!
>     *   **Shortest Path Length:** 4 steps (or Distance 4).