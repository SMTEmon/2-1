---
course: CSE 4303 Data Structures
topic: Graph Applications
lecture: 8
date: 2025-12-31
tags: [graph-theory, dfs, algorithms, articulation-points, bridges, topological-sort]
---

# Graph Applications: Structural Weaknesses & Ordering

## 1. DFS Tree Properties
To understand Articulation Points and Bridges, we must understand the structure of a graph during a Depth First Search (DFS).

> [!INFO] Edge Categories
> *   **Tree Edges:** Edges traversed to discover *new* unvisited nodes.
> *   **Back Edges:** Edges connecting a node to an already visited **ancestor**.

**Key Insight:** Back edges form **cycles**. They provide "alternative paths." If a node's subtree has a back edge to an ancestor, removing that node will not disconnect the subtree from the rest of the graph.

---

## 2. Articulation Points (Cut Vertices)

### Definition
A vertex $v$ is an **Articulation Point (AP)** if removing $v$ (and its incident edges) increases the number of connected components.
*   *Implication:* These represent single points of failure in a network.

### Algorithm (Hopcroft & Tarjan)
We use DFS and maintain two arrays for every node $u$:
1.  **$d[u]$ (Discovery Time):** The time counter when we first enter the node.
2.  **$low[u]$ (Low-Link Value):** The lowest discovery time reachable from $u$ (including itself) via its subtree or a single **back-edge**.

#### Logic for Updating $low[u]$
When at node $u$ looking at neighbor $v$:

| Case | Scenario | Action | Reasoning |
| :--- | :--- | :--- | :--- |
| **A** | $v$ is Parent of $u$ | **Ignore** | Going back to parent doesn't count as a cycle. |
| **B** | $v$ is Visited (Back Edge) | `low[u] = min(low[u], d[v])` | $u$ is part of a cycle connecting to ancestor $v$. |
| **C** | $v$ is Unvisited (Tree Edge) | 1. Recurse DFS($v$)<br>2. `low[u] = min(low[u], low[v])` | Propagate the "highest reach" of the subtree up to $u$. |

### The Critical Conditions
A node $u$ is an Articulation Point if:

1.  **If $u$ is the Root:**
    *   It has **more than 1 child** in the DFS tree.
    *   *Reasoning:* If the root has two children, there is no edge between the subtrees (otherwise DFS would have crossed over). Removing the root disconnects them.

2.  **If $u$ is NOT the Root:**
    *   There is a child $v$ such that:
    $$low[v] \ge d[u]$$
    *   *Reasoning:* The subtree rooted at $v$ has **no back-edge** to an ancestor of $u$. Every path from $v$ upwards must go through $u$.

### Visual Representation

```mermaid
graph TD
    A((A)) --- B((B))
    B --- C((C))
    C -. Back Edge .- A
    B --- D((D))
    
    classDef highlight fill:#f96,stroke:#333;
    class B,D highlight;
```
*In the graph above:*
*   **Cycle A-B-C:** $low$ values propagate up. Removing A, B, or C keeps the others connected via the cycle.
*   **Node D (Tail):** Connected only to B.
*   **Check for B:** D is a child of B. D cannot reach A (ancestor) without passing through B. Therefore, **B is an Articulation Point**.

### Complexity
*   **Time:** $O(V + E)$ (One DFS traversal).
*   **Space:** $O(V)$ (Arrays for $d$, $low$, parent, and stack).

---

## 3. Bridges (Cut Edges)

### Definition
An edge $(u, v)$ is a **Bridge** if removing it increases the number of connected components.
*   *Relation:* A bridge usually connects two Articulation Points (unless one end is a leaf).

### Algorithm
The logic is nearly identical to Articulation Points, but the condition changes.

**Condition:** An edge $(u, v)$ (where $v$ is a child of $u$) is a Bridge if:
$$low[v] > d[u]$$

> [!TIP] Inequality Check
> *   **Articulation Point:** $low[v] \ge d[u]$ (Back-edge to $u$ itself doesn't save $u$).
> *   **Bridge:** $low[v] > d[u]$ (Strict inequality).
> *   *Reasoning:* If $low[v] == d[u]$, there is a back-edge from the subtree to $u$. Removing the edge $(u, v)$ doesn't disconnect $v$ because it can still reach $u$ via the back-edge. We need $v$ to have *no* path to $u$ or above.

### Visual Representation

```mermaid
graph LR
    A((A)) --- B((B))
    B --- C((C))
    C -.- A
    B ===|Bridge| D((D))
    
    style B fill:#fff,stroke:#333
    style D fill:#fff,stroke:#333
    linkStyle 3 stroke:red,stroke-width:4px;
```

*   **Triangle (A, B, C):** No bridges. Removing any edge leaves a path.
*   **Edge (B, D):** If removed, D is isolated. $low[D] > d[B]$, so it is a Bridge.

### Complexity
*   **Time:** $O(V + E)$
*   **Space:** $O(V)$

---

## 4. Topological Sorting

### Definition
A linear ordering of vertices in a directed graph such that for every directed edge $u \to v$, vertex $u$ comes before $v$ in the ordering.

> [!WARNING] Constraints
> *   Graph must be a **DAG** (Directed Acyclic Graph).
> *   If a cycle exists, Topological Sort is **impossible**.

### Real-World Analogies
*   **Prerequisites:** Course $u$ must be taken before Course $v$.
*   **Assembly:** Put on socks ($u$) before shoes ($v$).

### Algorithm: Source Removal (Kahn's Algorithm)
This method relies on **In-Degrees** (number of incoming edges).

1.  **Initialization:** Calculate In-Degree for all nodes.
2.  **Queue:** Add all nodes with `In-Degree == 0` to a Queue.
3.  **Process:**
    *   While Queue is not empty:
        *   Dequeue $u$, add to **Sorted List**.
        *   For every neighbor $v$ of $u$:
            *   Decrement `InDegree[v]`.
            *   If `InDegree[v] == 0`, Enqueue $v$.

### Cycle Detection
Topological Sort works as a cycle detection algorithm.
*   Maintain a `count` of processed nodes.
*   If `count < V` (Total Vertices) when the queue is empty, a **Cycle Exists**.
*   *Why?* Nodes in a cycle never reach In-Degree 0.

### Visual Walkthrough

```mermaid
graph LR
    A((A)) --> B((B))
    A --> C((C))
    B --> D((D))
    C --> D
    D --> E((E))
```
1.  **Start:** A has in-degree 0. Queue: `[A]`.
2.  **Process A:** Remove A. Decrement B and C. Queue: `[B, C]`. Output: `[A]`
3.  **Process B:** Remove B. Decrement D. Queue: `[C]`. Output: `[A, B]`
4.  **Process C:** Remove C. Decrement D (D becomes 0). Queue: `[D]`. Output: `[A, B, C]`
5.  **Process D:** Remove D. Decrement E (E becomes 0). Queue: `[E]`. Output: `[A, B, C, D]`
6.  **End:** Process E.

### Complexity
*   **Time:** $O(V + E)$
    *   Calculated by processing every node once ($O(V)$) and every edge once ($O(E)$).
*   **Space:** $O(V)$ (Queue and In-Degree array).

---

## References
*   *Data Structures Using C, 2nd Edition*, Reema Thareja (Chapter 13).
*   CP-Algorithms: [Articulation Points](https://cp-algorithms.com/graph/cutpoints.html)
*   CP-Algorithms: [Bridges](https://cp-algorithms.com/graph/bridge-searching.html)
```