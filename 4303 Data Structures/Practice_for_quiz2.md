# Practice for Quiz 02: Data Structures

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

### Topic: Complexity Analysis

**Problem 4: Asymptotic Analysis (Time Complexity)**
Calculate the tightest upper bound ($O$) for the following code snippet. Explain your derivation.
```cpp
void obscureFunction(int n) {
    for (int i = 1; i < n; i = i * 2) {      // Loop A
        for (int j = 0; j < i; j++) {        // Loop B
            cout << i << j;
        }
    }
}
```
*Hint: Analyze how many times Loop B runs relative to the growth of `i` (1, 2, 4, 8...). It is a geometric series.*

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

## Part 2: Comprehensive Practice (Lectures 4-7)

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

**Problem 17: Theoretical Properties**
1.  **Height Calculation:** If a Complete Binary Tree has `N = 20` nodes, what is its height?
2.  **Strictly Binary Tree:** If a Strictly Binary Tree (2-Tree) has `15` Leaf Nodes, how many Internal Nodes does it have? ($E = I + 1$)

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