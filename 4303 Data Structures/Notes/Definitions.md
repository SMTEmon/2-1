## 1. Introduction & Complexity

*   **Data**: Values, sets of values, raw facts, or figures without specific meaning.
*   **Data Structure (DS)**: The logical or mathematical model of a particular organization of data. Defines *how* data is stored and operations are performed efficiently.
*   **Abstract Data Type (ADT)**: A logical model defining *what* operations can be performed on a data set (the interface) without specifying the implementation details.
*   **Time Complexity**: The amount of computer time needed for a program to run to completion, measured as a function of input size ($n$).
*   **Space Complexity**: The amount of memory needed for a program to run to completion. $S(P) = C + S_p(I)$ (Fixed + Variable space).
*   **Big O Notation ($O$)**: Asymptotic **Upper Bound** (Worst Case). The algorithm takes *at most* this much time.
*   **Big Omega Notation ($\Omega$)**: Asymptotic **Lower Bound** (Best Case). The algorithm takes *at least* this much time.
*   **Big Theta Notation ($\Theta$)**: Asymptotic **Tight Bound**. Used when the Upper and Lower bounds are the same.

## 2. Linear Data Structures

### Arrays & Linked Lists
*   **Array**: A collection of elements of the **same type** stored in **contiguous** memory locations. Supports $O(1)$ random access.
*   **Record (Structure)**: A collection of related data items of **different types** grouped under a single name.
*   **Pointer**: A variable that stores the **memory address** of another variable.
*   **Linked List**: A linear collection of data elements (nodes) where each node points to the next, allowing dynamic memory allocation.
*   **Singly Linked List (SLL)**: Nodes have one pointer (`Next`), allowing only forward traversal.
*   **Doubly Linked List (DLL)**: Nodes have two pointers (`Prev` and `Next`), allowing bi-directional traversal.
*   **Circular Linked List (CLL)**: A list where the last node points back to the first node instead of `NULL`.
*   **Orthogonal List**: A grid-like structure for **Sparse Matrices** where nodes are linked horizontally (Rows) and vertically (Cols) to save space.
*   **XOR Linked List**: A memory-efficient DLL that stores both directions in a single pointer field using bitwise XOR ($Address(Prev) \oplus Address(Next)$).

### Stacks & Queues
*   **Stack**: A linear data structure following **LIFO** (Last In, First Out). Elements are added/removed from the **Top**.
*   **Queue**: A linear data structure following **FIFO** (First In, First Out). Elements are added at the **Rear** and removed from the **Front**.
*   **Circular Queue**: A queue implemented with a fixed array where the indices wrap around (modulo arithmetic) to utilize empty space created by dequeues.
*   **Deque (Double-Ended Queue)**: A generalized queue allowing insertion and deletion at **both** ends (Front and Rear).

## 3. Trees (Non-Linear)

*   **Tree**: A hierarchical structure consisting of nodes connected by edges (1:N relationship), with no cycles.
*   **Root**: The topmost node (Level 0) with no parent.
*   **Leaf (External Node)**: A node with no children.
*   **Internal Node**: A node with at least one child.
*   **Depth**: Number of edges from Root to a specific Node.
*   **Height**: Number of nodes on the longest path from a Node down to a Leaf.
*   **Binary Tree**: A tree where every node has **at most 2 children**.
*   **Strictly Binary Tree (Full/2-Tree)**: Every node has either 0 or 2 children. ($E = I + 1$).
*   **Complete Binary Tree**: All levels are fully filled except possibly the last, which is filled left-to-right.
*   **Skewed Binary Tree**: A tree where every node has only one child (degrades to a Linked List).
*   **Binary Search Tree (BST)**: A binary tree where Left Subtree < Node < Right Subtree (providing $O(\log n)$ search).
*   **Huffman Tree**: A weighted, strictly binary tree used for lossless data compression (optimal prefix codes).

## 4. Graphs

*   **Graph**: A non-linear structure $G = (V, E)$ consisting of Vertices (Nodes) and Edges (Connections). Can be cyclic.
*   **Directed Graph (Digraph)**: Edges have a direction ($u \to v$).
*   **Undirected Graph**: Edges have no direction ($u \leftrightarrow v$).
*   **Weighted Graph**: Edges have assigned values (weights/costs).
*   **Degree**: Number of edges connected to a node.
    *   **In-Degree**: Number of edges entering a node (Directed).
    *   **Out-Degree**: Number of edges leaving a node (Directed).
*   **Path**: A sequence of vertices where each pair is connected by an edge.
*   **Cycle**: A path that starts and ends at the same vertex.
*   **DAG (Directed Acyclic Graph)**: A directed graph with no cycles. Required for Topological Sort.
*   **Adjacency Matrix**: A 2D array representation ($O(V^2)$). Good for dense graphs.
*   **Adjacency List**: An array of linked lists ($O(V+E)$). Good for sparse graphs.
*   **Adjacency Multi-list**: Represents edges as nodes to avoid duplication in undirected graphs.
*   **Transitive Closure**: A graph representing reachability (an edge exists if a path exists).
*   **Articulation Point (Cut Vertex)**: A node whose removal increases the number of connected components (disconnects the graph).
*   **Bridge (Cut Edge)**: An edge whose removal disconnects the graph.
*   **Topological Sort**: A linear ordering of vertices in a DAG such that for every edge $u \to v$, $u$ comes before $v$.
