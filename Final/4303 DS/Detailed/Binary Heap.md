 **Tags:** #data-structures #algorithms #heaps #priority-queue #binary-tree #complexity
**Course:** CSE 4303 - Data Structures
**Reference:** *Data Structures Using C*, Reema Thareja (Chapter 12)
Checked: No

---

![[Pasted image 20260224030352.png]]
## 1. Introduction: The Priority Queue Problem

### What is a Priority Queue?
A **Priority Queue (PQ)** is an Abstract Data Type (ADT) where every element has a "priority".
*   **Rule:** Elements with higher priority are served before elements with lower priority.
*   **Key Operations:**
    *   `insert(item)`: Add an element.
    *   `extract_max()` (or `extract_min()`): Remove and return the highest priority element.

### Why not use Arrays or Linked Lists?
Naive implementations suffer from performance bottlenecks:

| Approach | Insert | Extract Max | Verdict |
| :--- | :--- | :--- | :--- |
| **Unsorted Array** | $O(1)$ | $O(N)$ | Searching takes too long. |
| **Sorted Array** | $O(N)$ | $O(1)$ | Shifting elements to insert takes too long. |
| **Binary Heap** | **$O(\log N)$** | **$O(\log N)$** | **Balanced efficiency.** |

---

## 2. Definition & Properties

A **Binary Heap** is a binary tree that satisfies two specific constraints:

### A. Shape Property (Structure)
It must be a **Complete Binary Tree**.
1.  All levels are fully filled, except possibly the last level.
2.  Nodes in the last level are filled from **left to right**.
3.  **Benefit:** This allows the tree to be implemented using a simple **Array** without gaps, removing the need for pointers (`left`, `right`, `parent`).

### B. Heap Property (Order)
*   **Max-Heap:** For every node $i$, the value of the parent is greater than or equal to the values of its children.
    $$Parent(i) \ge Children(i)$$
    *   *Result:* The largest element is always at the Root.
*   **Min-Heap:** For every node $i$, the value of the parent is less than or equal to the values of its children.
    $$Parent(i) \le Children(i)$$
    *   *Result:* The smallest element is always at the Root.

---

## 3. Array Implementation

Because heaps are complete binary trees, we can map node positions directly to array indices.

### Indexing Formulas
Depending on whether the array starts at index `0` or `1`:

| Node Relationship | **0-based Indexing** (Standard Code) | **1-based Indexing** (Math/Textbooks) |
| :--- | :--- | :--- |
| **Root** | Index `0` | Index `1` |
| **Left Child** | $2i + 1$ | $2i$ |
| **Right Child** | $2i + 2$ | $2i + 1$ |
| **Parent** | $\lfloor \frac{i-1}{2} \rfloor$ | $\lfloor \frac{i}{2} \rfloor$ |

> [!INFO] Leaf Node Property
> In a heap of size $N$ (1-based), **Internal Nodes** are from index $1$ to $\lfloor N/2 \rfloor$.
> **Leaf Nodes** are from index $\lfloor N/2 \rfloor + 1$ to $N$.
> *This is crucial for optimizing the "Build Heap" operation.*

---

## 4. Core Operations

### A. Heapify Down (Max-Heapify)
Used when a node violates the heap property by being **smaller** than its children (in a Max-Heap). We must "demote" the node.

*   **Algorithm (Percolate Down):**
    1.  Compare the current node ($i$) with its children (`left` and `right`).
    2.  Find the **largest** of the three (Parent, Left, Right).
    3.  If the Parent is already the largest: Stop.
    4.  Otherwise: **Swap** the parent with the **largest child**.
    5.  Recursively call `max_heapify` on the new position of the demoted node.
*   **Time Complexity:** $O(\log N)$ (proportional to the height of the tree).

> [!WARNING] Why swap with the largest child?
> If you swap with the smaller child, the new parent would be smaller than the other child, which still violates the Max-Heap property.

### B. Insertion (Percolate Up)
When adding a new element:
*   **Algorithm:**
    1.  **Shape First:** Insert the new key at the very end of the array (the next available leaf spot) to maintain the Complete Tree property.
    2.  **Order Second:** Compare the new key with its **Parent**.
    3.  If `Child > Parent`: **Swap**.
    4.  Repeat step 2-3 moving up the tree until the property is restored or the root is reached.
*   **Time Complexity:** $O(\log N)$.

### C. Extract Max (Delete Root)
To remove the highest priority element:
*   **Algorithm:**
    1.  **Swap:** Exchange the Root (index 0 or 1) with the **Last Leaf** (last index).
    2.  **Remove:** Decrease the `heap_size` (effectively deleting the max element, which is now at the end).
    3.  **Fix:** The new Root is likely a small value (it came from the bottom). Call **`max_heapify(root)`** to bubble it down to its correct position.
*   **Time Complexity:** $O(\log N)$.

---

## 5. Building a Heap

How do we convert an arbitrary unordered array into a Heap?

### Method 1: Top-Down (Naive)
Iterate from the start of the array and call `insert` (percolate up) for every element.
*   **Complexity:** $O(N \log N)$.

### Method 2: Bottom-Up (Optimized)
We fix small sub-trees first and work our way up.
*   **Algorithm:**
    1.  Identify the last internal node (index $\lfloor N/2 \rfloor$).
    2.  Iterate backwards from $i = \lfloor N/2 \rfloor$ down to $1$ (or 0).
    3.  Call `max_heapify(i)` on each node.
*   **Why it works:** By the time we process node $i$, its children are already roots of valid heaps.
*   **Time Complexity:** **$O(N)$ (Linear Time)**.

> [!Abstract] Mathematical Proof for $O(N)$
> `max_heapify` cost depends on height.
> *   Leaves (50% of nodes) have height 0: Cost = 0.
> *   Next level (25%) height 1: Cost = 1 step.
> *   Root (1 node) height $\log N$.
>
> The summation corresponds to a convergent series:
> $$ \sum_{h=0}^{\log N} \frac{N}{2^{h+1}} \cdot O(h) \approx O(N) $$
> Most nodes are at the bottom and require very little work.

---

## 6. Other Operations & Applications

### Arbitrary Deletion
To delete a node with value $X$:
1.  **Find the node:** Linear scan required (Heaps are not sorted like BSTs). **Cost: $O(N)$**.
2.  **Delete:** Swap with last element, remove last, then either Percolate Up or Heapify Down depending on the value. **Cost: $O(\log N)$**.
3.  *Total:* $O(N)$ unless index is known.

### Modify Key (Increase/Decrease)
Used in algorithms like Dijkstra or Prim.
*   **Increase Key:** Update value $\to$ Percolate Up.
*   **Decrease Key:** Update value $\to$ Heapify Down.
*   **Complexity:** $O(\log N)$ (assuming we know the index).

### Heap Sort
An in-place comparison-based sorting algorithm.
1.  **Build Max Heap:** $O(N)$.
2.  **Sort Loop:** $N$ times.
    *   Swap Root (Max) with Last element.
    *   Reduce heap size by 1.
    *   `max_heapify(root)`.
3.  **Total Complexity:** $O(N \log N)$ (Best, Average, Worst).
4.  **Space:** $O(1)$ (In-place).

---

## 7. Summary Table

| Operation | Complexity | Note |
| :--- | :--- | :--- |
| `peek_max()` | $O(1)$ | Just return `arr[0]` |
| `insert(k)` | $O(\log N)$ | Add to end, bubble up |
| `extract_max()` | $O(\log N)$ | Swap root/end, bubble down |
| `build_heap()` | $O(N)$ | Bottom-up approach |
| `heap_sort()` | $O(N \log N)$ | Extract max $N$ times |
| `delete(index)` | $O(\log N)$ | If index is known |
| `search(value)` | $O(N)$ | Heaps are not search trees |

---

## 8. Code Implementation (C++ Example)

```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 0-based indexing helper functions
int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

// Maintain Max-Heap property downwards
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = left(i);
    int r = right(i);

    // Compare with left child
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Compare with right child
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If root is not largest, swap and recurse
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Build Heap: O(N)
void buildHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from last non-leaf node and move up
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Heap Sort: O(N log N)
void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildHeap(arr);

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to end
        swap(arr[0], arr[i]);
        // Call maxHeapify on the reduced heap
        maxHeapify(arr, i, 0);
    }
}
```

