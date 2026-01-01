## Topic: Graphs (Lecture 7)

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

---

# Solutions (Lecture 7)

### Problem 21: Warshall's Algorithm

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

### Problem 23: Topological Sort & Cycles

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

### Problem 25: DFS Stack Simulation

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

### Problem 27: Shortest Path in Maze (BFS)

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
