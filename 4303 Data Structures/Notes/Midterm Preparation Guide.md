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
*Focus: Networks, Connectivity, BFS/DFS.*

### 1. Definition & Analysis
*   **Graph:** Collection of Vertices ($V$) and Edges ($E$).
*   **Representation:**
    *   *Adjacency Matrix:* $O(V^2)$ space. Good for dense graphs. $O(1)$ to check edge.
    *   *Adjacency List:* $O(V+E)$ space. Good for sparse graphs.
*   **Articulation Point:** A node which, if removed, disconnects the graph.

### 2. Scenario & Selection
*   **Scenario A:** Google Maps finding the shortest route from Home to University.
    *   **Selection:** **Graph + BFS (or Dijkstra)**.
    *   **Reason:** Maps are networks. BFS finds shortest path in unweighted graphs.
*   **Scenario B:** Determining the order of tasks where Task B depends on Task A.
    *   **Selection:** **DAG + Topological Sort**.
    *   **Reason:** Resolves dependencies linearly.

### 3. Pseudo Code (BFS - Breadth First Search)
```text
FUNCTION BFS(START_NODE)
    CREATE Queue Q
    MARK START_NODE as Visited
    ENQUEUE START_NODE into Q

    WHILE Q is not Empty
        SET U = DEQUEUE(Q)
        PRINT U
        
        FOR each neighbor V of U
            IF V is not Visited
                MARK V as Visited
                ENQUEUE V into Q
END FUNCTION
```

### 4. Simulation (Adjacency List)
**Graph:** Node 0 connected to 1, 2. Node 1 connected to 2.
**Task:** Draw Adjacency List.
**Answer:**
*   `Arr[0]` $\to$  `[1] -> [2] -> NULL`
*   `Arr[1]` $\to$  `[2] -> NULL` (and `[0]` if undirected)
*   `Arr[2]` $\to$  `NULL` (and `[0], [1]` if undirected)

