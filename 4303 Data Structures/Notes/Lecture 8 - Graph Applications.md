# Graph Applications: Articulation Points, Bridges, & Topological Sort
**Tags:** #GraphTheory #DFS #Algorithms #ExamPrep #CSE4303
**Date:** December 31, 2025

---

## 1. Structural Weaknesses: Articulation Points & Bridges
The goal is to find "single points of failure" in a network efficiently ($O(V+E)$) using DFS, rather than the naive $O(V(V+E))$ approach.

### A. Articulation Points (Cut Vertices)
> [!info] Definition
> A vertex $v$ is an **Articulation Point** if removing $v$ (and its incident edges) increases the number of connected components in the graph.

### B. Bridges (Cut Edges)
> [!info] Definition
> An edge $(u, v)$ is a **Bridge** if removing it increases the number of connected components.

* **Relation:** A bridge always connects two articulation points (unless one end is a leaf node).

---

## 2. Finding Articulation Points
We rely on **DFS Tree** properties.
* **Tree Edges:** Edges traversed to discover new nodes.
* **Back Edges:** Edges connecting a node to an already visited ancestor. These form cycles and provide "alternative paths".

### Variables (For every node $u$)
1.  **$d[u]$ (Discovery Time):** When was the node first entered?
2.  **$low[u]$ (Low-Link Value):** The lowest discovery time reachable from $u$ (including itself) via the subtree or a single back-edge.
    * *Insight:* $low[u]$ indicates if a "secret path" exists connecting descendants back to ancestors.

### The Algorithm (DFS Logic)
For a current node $u$ and neighbor $v$:

1.  **If $v$ is Parent:** Ignore (going back to parent is not a cycle).
2.  **If $v$ is Visited (Back Edge):**
    * Update: $low[u] = \min(low[u], d[v])$.
    * *Reasoning:* $u$ connects to an ancestor $v$, forming a cycle.
3.  **If $v$ is Unvisited (Tree Edge):**
    * Recursive Call: `DFS(v)`.
    * Update on Return: $low[u] = \min(low[u], low[v])$.
    * **Check AP Condition:**
        > If $$low[v] \ge d[u]$$ (and $u \ne root$), then $u$ is an **Articulation Point**.
    * *Reasoning:* The subtree at $v$ has **no back-edge** to any ancestor of $u$; all paths must go through $u$.

### Special Root Case
* The condition $low[v] \ge d[u]$ is always true for the root.
* **Rule:** The root is an Articulation Point if and only if it has **more than 1 child** in the DFS tree.
* *Why:* If it has two children in the DFS tree, there is no edge connecting their subtrees (or DFS would have combined them). Removing the root disconnects them.

### Pseudocode & Implementation

> [!notes]+ Pseudocode
> ```
> Initialize: 
> 			timer = 0 
> 			d[u] = 0, 
> 			low[u] = 0 for all u 
> 			visited[u] = false for all u 
> 			is_cutpoint[u] = false 
> Function DFS(u, p = -1): 
> 			visited[u] = true 
> 			d[u] = low[u] = ++timer 
> 			children = 0 
> 			
> 			For each neighbor v of u: 
> 				If v == p: 
> 					Continue (Ignore parent) 
> 				If v is visited: 
> 					low[u] = min(low[u], d[v]) (Back Edge) 
> 				Else: 
> 					DFS(v, u) 
> 					low[u] = min(low[u], low[v]) 
> 					if low[v] >= d[u] AND p != -1: 
> 						is_cutpoint[u] = true 
> 					children++ 
> 			If p == -1 AND children > 1: (Special Root Case) 
> 				is_cutpoint[u] = true
> ```


>[!hint]- C++ Implementations
```c++

const int MAXN = 100005;
vector<int> adj[MAXN];
int tin[MAXN], low[MAXN]; // tin is 'd' in the slides
int timer;
bool is_cutpoint[MAXN]; // To store unique APs

void dfs_articulation_point(int u, int p = -1) {
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue; // Case A: Parent [cite: 72]

        if (tin[v]) { 
            // Case B: Back Edge [cite: 75-76]
            low[u] = min(low[u], tin[v]);
        } else {
            // Case C: Tree Edge [cite: 88-90]
            dfs_articulation_point(v, u);
            low[u] = min(low[u], low[v]);
            
            // Check AP condition for non-root [cite: 95]
            if (low[v] >= tin[u] && p != -1)
                is_cutpoint[u] = true;
            
            children++;
        }
    }

    // Root Check [cite: 113]
    if (p == -1 && children > 1)
        is_cutpoint[u] = true;
}
```


---

## 3. Finding Bridges (Cut Edges)
The logic is nearly identical to Articulation Points but checks edges instead of nodes.

### The Bridge Condition
In the DFS tree, an edge $(u, v)$ is a bridge if and only if:
> $$low[v] > d[u]$$

* **Comparison:**
    * **$low[v] \le d[u]$**: Subtree has a back-edge to $u$ or above (Cycle exists).
    * **$low[v] > d[u]$**: The "lowest" node $v$ can reach is itself; no path back to $u$'s ancestors exists.

### Complexity (For both AP and Bridges)
* **Time:** $O(V+E)$ (Single DFS traversal).
* **Space:** $O(V)$ (Recursion stack + Arrays $d, low, parent$).

### Pseudocode & Implementation

>[!notes] Pseudocode!
```text
Initialize:
    timer = 0
    d[u] = 0, low[u] = 0 for all u
    visited[u] = false

Function DFS_Bridge(u, p = -1):
    visited[u] = true
    d[u] = low[u] = ++timer

    For each neighbor v of u:
        If v == p:
            Continue
        If v is visited:
            low[u] = min(low[u], d[v])
        Else:
            DFS_Bridge(v, u)
            low[u] = min(low[u], low[v])
            
            If low[v] > d[u]:
                Print "Bridge found: u - v"
```

>[! hint]- C++ Implementation
```c++
// Re-using variables from AP section
vector<pair<int, int>> bridges; // Store result

void dfs_bridges(int u, int p = -1) {
    tin[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == p) continue; // Ignore parent [cite: 312]

        if (tin[v]) {
            // Back Edge [cite: 315]
            low[u] = min(low[u], tin[v]);
        } else {
            // Tree Edge [cite: 327-329]
            dfs_bridges(v, u);
            low[u] = min(low[u], low[v]);

            // Bridge Condition [cite: 330]
            if (low[v] > tin[u]) {
                bridges.push_back({u, v});
            }
        }
    }
}
```
---

## 4. Topological Sorting
> [!summary] Definition
> A linear ordering of vertices in a directed graph such that for every directed edge $u \to v$, $u$ comes before $v$ in the ordering.

### Constraints
* **DAG Only:** Graph must be a **Directed Acyclic Graph**.
* If a cycle exists, Topological Sort is impossible.
* *Analogy:* Prerequisites (Must take "Intro to C" before "Data Structures").

### Algorithm: Source Removal (Kahn's Algorithm)
1.  **Calculate In-Degrees** for all nodes (count incoming edges).
2.  **Initialize Queue:** Enqueue all nodes with `In-Degree == 0`.
3.  **Process:**
    * Dequeue node $u$, add to **Sorted Output**.
    * For every neighbor $v$ of $u$:
        * Decrement `In-Degree[v]` (simulate removing edge $u \to v$).
        * If `In-Degree[v]` becomes 0, Enqueue $v$.

### Correctness & Complexity
* **Cycle Detection:** If the final Sorted List count $< V$, the graph has a cycle (nodes in a cycle never reach In-Degree 0).
* **Time Complexity:** $O(V+E)$.
    * Initialization: $O(V+E)$.
    * Processing: Each edge visited once ($O(E)$).
* **Space Complexity:** $O(V)$ (Queue + In-Degree Array).

---

## 5. Quick Comparison

| Algorithm              | Condition / Key                         | Time     | Space  |
| :--------------------- | :-------------------------------------- | :------- | :----- |
| **Articulation Point** | $low[v] \ge d[u]$ (Root needs >1 child) | $O(V+E)$ | $O(V)$ |
| **Bridge**             | $low[v] > d[u]$                         | $O(V+E)$ | $O(V)$ |
| **Topological Sort**   | In-Degree == 0 (DAG only)               | $O(V+E)$ | $O(V)$ |