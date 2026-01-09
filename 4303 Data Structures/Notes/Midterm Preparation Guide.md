# 📚 CSE 4303 Midterm Preparation Guide

## 📝 Set 1: Intro, Complexity & Linked Lists
*Focus: Fundamentals, Efficiency, and Linear Dynamic Structures.*

### 1. Definition & Analysis
*   **ADT vs. Data Structure:**
    *   **ADT (Abstract Data Type):** Logical model defining *what* operations can be done (e.g., Stack Interface: `push`, `pop`).
    *   **Data Structure:** The concrete implementation of *how* data is stored (e.g., Array-based Stack vs. Linked Stack).
*   **Asymptotic Notations:**
    *   **$O(n)$ (Big O):** **Upper Bound** (Worst Case). The "Ceiling". It takes *at most* this much time.
    *   **$\Omega(n)$ (Big Omega):** **Lower Bound** (Best Case). The "Floor". It takes *at least* this much time.
    *   **$\Theta(n)$ (Big Theta):** **Tight Bound**. Used when $O$ and $\Omega$ are the same. It grows *exactly* at this rate.
*   **How to Calculate:**
    1.  **Instruction Counting:** Count how many times each line runs based on input size $n$.
    2.  **Drop Constants:** $T(n) = 2n + 3 \rightarrow O(n)$.
    3.  **Keep Dominant Term:** $O(n^2 + n) \rightarrow O(n^2)$.
    4.  **Growth Rate Rank:** $O(1) < O(\log n) < O(n) < O(n \log n) < O(n^2) < O(2^n)$.
*   **Singly vs. Doubly Linked List:**
    *   SLL: Forward only, less memory (1 pointer). Hard to delete if you don't have the `prev` pointer.
    *   DLL: Bi-directional, more memory (2 pointers). Easy deletion (`curr->prev->next = curr->next`).

### 2. Scenario & Selection
*   **Scenario A:** You need to store student marks and frequently access the mark of Student #45 directly.
    *   **Selection:** **Array**.
    *   **Reason:** $O(1)$ random access via index. Linked List would take $O(n)$.
*   **Scenario B:** A music player playlist where users frequently drag-and-drop songs to reorder them or delete the current song.
    *   **Selection:** **Doubly Linked List**.
    *   **Reason:** Efficient insertion/deletion ($O(1)$ once pointer is known) without shifting elements like an array.

### 3. Pseudo Code (Singly Linked List Deletion)
**Task:** Delete the node *after* a given node `PREPTR`.
```text
FUNCTION DeleteNodeAfter(PREPTR)
    IF PREPTR == NULL OR PREPTR->NEXT == NULL
        RETURN "Error: Nothing to delete"
    
    SET TEMP = PREPTR->NEXT       // The node to be deleted
    SET PREPTR->NEXT = TEMP->NEXT // Bypass TEMP
    FREE TEMP                     // Release memory
END FUNCTION
```

### 4. Application / Simulation
**Problem:** Calculate Time Complexity ($T(n)$) for this snippet.
```cpp
for (i = 0; i < n; i++) {       // Runs n times
    for (j = 0; j < n; j++) {   // Runs n times per outer loop
        print(i, j);            // Constant time
    }
}
```
**Answer:**
*   Inner loop runs $n$ times.
*   Outer loop runs $n$ times.
*   Total = $n \times n = n^2$.
*   Complexity: **$O(n^2)$ (Quadratic)**.

---

## 🥞 Set 2: Stack and Queue
*Focus: Restricted Linear Data Structures (LIFO / FIFO).*

### 1. Definition & Analysis
*   **Stack (LIFO):** Last In, First Out. Major uses: Function recursion (Call Stack), Expression evaluation.
*   **Queue (FIFO):** First In, First Out. Major uses: CPU Scheduling, Printer Spooling.
*   **Circular Queue:** Solves the "Wasted Space" problem in Array Queues.
    *   *Equation:* `Next_Index = (Current_Index + 1) % Capacity`.

### 2. Scenario & Selection
*   **Scenario A:** Implementing an "Undo" feature in a text editor.
    *   **Selection:** **Stack**.
    *   **Reason:** The last action performed is the first one to be undone (LIFO).
*   **Scenario B:** A help-desk call center system holding calls until an agent is free.
    *   **Selection:** **Queue**.
    *   **Reason:** Fairness; the first caller waiting should be the first served (FIFO).

### 3. Pseudo Code (Circular Queue Enqueue)
```text
FUNCTION Enqueue(QUEUE, FRONT, REAR, SIZE, VAL)
    IF (REAR + 1) % SIZE == FRONT
        PRINT "Overflow"
        RETURN
    
    IF FRONT == -1
        SET FRONT = 0
        SET REAR = 0
    ELSE
        SET REAR = (REAR + 1) % SIZE  // Wrap around
        
    SET QUEUE[REAR] = VAL
END FUNCTION
```

### 4. Simulation (Infix to Postfix)
**Input:** `A + B * C`
**Stack Trace:**
1.  Read `A`: Output `A`. Stack: `[]`
2.  Read `+`: Push `+`. Stack: `[+]`
3.  Read `B`: Output `B`. Stack: `[+]`
4.  Read `*`: Push `*` (Higher priority than `+`). Stack: `[+, *]`
5.  Read `C`: Output `C`. Stack: `[+, *]`
6.  End: Pop all. Output `*`, then `+`.
**Result:** `A B C * +`

---

## 🌳 Set 3: Trees
*Focus: Hierarchical Structures, BST, Recursion.*

### 1. Definition & Analysis
*   **Binary Tree:** Max 2 children per node.
*   **BST Property:** Left Child < Parent < Right Child. Allows $O(\log n)$ search.
*   **Full vs. Complete:**
    *   *Strictly Binary (Full):* 0 or 2 children.
    *   *Complete:* All levels full (except last, filled left-to-right). Used in Heaps.
*   **Traversals:**
    *   *Pre-order:* Root $\to$ Left $\to$ Right.
    *   *In-order:* Left $\to$ Root $\to$ Right (Sorted output for BST).
    *   *Post-order:* Left $\to$ Right $\to$ Root (Deleting tree).

### 2. Scenario & Selection
*   **Scenario A:** Storing a generic file system directory structure.
    *   **Selection:** **General Tree** (N-ary Tree).
    *   **Reason:** A folder can have any number of sub-folders.
*   **Scenario B:** Compressing a text file based on character frequency.
    *   **Selection:** **Huffman Tree**.
    *   **Reason:** Generates optimal prefix codes (frequent chars near root get shorter binary codes).

### 3. Pseudo Code (BST Search - Recursive)
```text
FUNCTION Search(NODE, KEY)
    IF NODE == NULL OR NODE->DATA == KEY
        RETURN NODE
    
    IF KEY < NODE->DATA
        RETURN Search(NODE->LEFT, KEY)
    ELSE
        RETURN Search(NODE->RIGHT, KEY)
END FUNCTION
```

### 4. Simulation (Tree Reconstruction)
**Given Pre-order:** `A, B, D, E, C`
**Given In-order:** `D, B, E, A, C`
**Build Steps:**
1.  **Root:** `A` (First in Pre).
2.  **Split In-order:** `[D, B, E]` (Left of A) and `[C]` (Right of A).
3.  **Left Subtree:** Next in Pre is `B`. In In-order `[D, B, E]`, `B` is between `D` and `E`. So `B` is parent, `D` is Left, `E` is Right.
**Result Structure:**
```text
    A
   / \
  B   C
 / \
D   E
```

---

## 🕸️ Set 4: Graphs
*Focus: Networks, Connectivity, DFS/BFS, Structural Weakness.*

### 1. Definition & Analysis
*   **Graph vs. Tree:**
    *   Trees are hierarchical (Parent-Child) and acyclic.
    *   Graphs are Many-to-Many and **can contain cycles**.
*   **Representations (Lecture 7):**
    *   **Adjacency Matrix:** $O(V^2)$ space. Best for *Dense* graphs. $O(1)$ edge check.
    *   **Adjacency List:** $O(V+E)$ space. Best for *Sparse* graphs.
*   **DFS Tree Properties (Lecture 8):**
    *   **Tree Edge:** Normal path to unvisited node.
    *   **Back Edge:** Path to an already visited ancestor (creates a Cycle).
    *   *Significance:* Back edges are crucial for finding **Articulation Points** (Single points of failure).

### 2. Scenario & Selection
*   **Scenario A:** "People You May Know" feature in a Social Network (finding friends of friends).
    *   **Selection:** **BFS (Breadth-First Search)**.
    *   **Reason:** Explores layer-by-layer (Level 1 friends, then Level 2). Good for shortest path in unweighted graphs.
*   **Scenario B:** A Build System (like Makefile) determining compile order where file B depends on file A.
    *   **Selection:** **Topological Sort (DAG)**.
    *   **Reason:** Linearly orders tasks respecting dependencies. Fails if there is a circular dependency (Cycle).

### 3. Pseudo Code (DFS - Recursive)
*Used for Cycle Detection and Pathfinding.*
```text
FUNCTION DFS(u, visited, adj)
    SET visited[u] = TRUE
    PRINT u
    
    FOR each neighbor v in adj[u]
        IF visited[v] is FALSE
            DFS(v, visited, adj)
        END IF
    END FOR
END FUNCTION
```

### 4. Simulation (Topological Sort - Kahn's Algo)
**Graph:** $A \to B, A \to C, B \to D, C \to D$.
**Task:** Show the state of In-Degrees and Queue at each step.

**Step-by-Step Trace:**
1.  **Init:** Calculate In-Degrees.
    *   $A=0, B=1 (from A), C=1 (from A), D=2 (from B, C)$.
    *   **Queue:** `[A]` (Nodes with 0 in-degree).
2.  **Process A:** Pop $A$. Output `A`.
    *   Decrement neighbors $B$ ($1 \to 0$) and $C$ ($1 \to 0$).
    *   Push $B, C$. **Queue:** `[B, C]`.
3.  **Process B:** Pop $B$. Output `B`.
    *   Decrement neighbor $D$ ($2 \to 1$).
    *   **Queue:** `[C]`.
4.  **Process C:** Pop $C$. Output `C`.
    *   Decrement neighbor $D$ ($1 \to 0$).
    *   Push $D$. **Queue:** `[D]`.
5.  **Process D:** Pop $D$. Output `D`.
**Final Order:** `A, B, C, D` (or `A, C, B, D`).

