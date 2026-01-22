
**
### 🎓 Part 1: Learning the Concepts

#### 1. The Problem: Why do we need Heaps?

We use a **Priority Queue** when we need to manage tasks where some are more important than others (e.g., CPU scheduling).

- **Naive Approach:** If we use a simple sorted array, inserting a new item is slow ($O(N)$). If we use an unsorted array, finding the highest priority item is slow ($O(N)$)1.
    
- **The Solution:** The Binary Heap balances these operations, allowing us to Insert and Extract the maximum element both in **$O(\log N)$** time2.
    

#### 2. What is a Binary Heap?

It is a binary tree that satisfies two strict properties:

1. **Heap Property (Max-Heap):** The value of every parent node is greater than or equal to its children ($Parent \ge Children$). This guarantees the largest element is always at the **Root**.
    
2. **Shape Property:** It must be a **Complete Binary Tree**. This means all levels are fully filled, except possibly the last level, which is filled from left to right.
    

#### 3. How is it Implemented?

Instead of using pointers (like a standard Linked List tree), we use an **Array**. This is possible because the tree is "complete."

- **Navigation:** For any node at index $i$ (using 1-based indexing from the slides 5):
    
    - **Left Child:** $2 \times i$        
    - **Right Child:** $(2 \times i) + 1$        
    - **Parent:** $\lfloor i/2 \rfloor$
        
- **Leaves:** In a heap of size $N$, nodes from $\lfloor N/2 \rfloor + 1$ to $N$ are always leaf nodes6.
#### 4. Key Operations

**A. Heapify Down (Fixing Violations)*

If a parent is smaller than a child (violating the Max-Heap property), we "demote" it.

- **Rule:** Swap the parent with the **largest** of its two children7.    
- **Repeat:** Continue swapping down until the node fits or becomes a leaf.    

**B. Build Heap (The "Bottom-Up" Magic)**

- **Naive way (Top-Down):** Inserting elements one by one or calling heapify from the root fails because the bottom remains unordered8.    
- **Correct way (Bottom-Up):** Start from the last internal node (index $\lfloor N/2 \rfloor$) and move backwards to index 1, calling `max_heapify` on each9.    
- **Complexity:** Surprisingly, this takes **$O(N)$** linear time, not $O(N \log N)$, because most nodes (the leaves) require 0 work10101010.
    

**C. Heap Sort**

1. Build a Max Heap from the array ($O(N)$).    
2. Swap the Root (max) with the Last element.    
3. Reduce heap size by 1 (the max is now "sorted" at the end).    
4. Heapify the new Root.    
5. Repeat until the heap is empty.
    
    - **Total Complexity:** $O(N \log N)$.        


---

## 1. Definition
A **Binary Heap** is a complete binary tree that satisfies the **Heap Property**.
* **Max-Heap:** $Parent(i) \ge Children(i)$. Root is the maximum.
* **Min-Heap:** $Parent(i) \le Children(i)$. Root is the minimum.
* **Array Storage:** * Root at index 1.
    * Left Child: $2i$
    * Right Child: $2i+1$
    * Parent: $\lfloor i/2 \rfloor$

### 2. Complexity Overview

| Operation | Complexity | Note |
| :--- | :--- | :--- |
| **Insert** | $O(\log N)$ | [cite_start]Add to end, Percolate Up (Swap with parent) [cite: 582] |
| **Extract Max** | $O(\log N)$ | [cite_start]Swap Root/Last, remove Last, Percolate Down [cite: 582] |
| **Peek Max** | $O(1)$ | [cite_start]Return `A[1]` [cite: 582] |
| **Build Heap** | **$O(N)$** | [cite_start]Efficient bottom-up construction [cite: 430] |
| **Heap Sort** | $O(N \log N)$ | [cite_start]In-place sorting  |

### 3. Key Algorithms

### Build Heap (Bottom-Up)
Instead of starting at the root, start at the **last internal node** and walk backwards.
"Fix the small sub-trees first, then move up."

**Why is it $O(N)$?**
* Sum of heights of all nodes.
* 50% of nodes are leaves (height 0, cost 0).
* 25% of nodes are height 1.
* Mathematically converges to $O(N)$ rather than $O(N \log N)$.

### Deletion (Arbitrary Node)
1.  **Find Node:** $O(N)$ (Heaps are not sorted like BSTs, so we must scan).
2.  **Delete:** Swap with last element, remove last, then fix up (`Percolate Up`) or fix down (`Heapify`) depending on the value replaced.

### 4. Formulas
* **Internal Nodes:** indices $1 \dots \lfloor N/2 \rfloor$.
* **Leaf Nodes:** indices $\lfloor N/2 \rfloor + 1 \dots N$.

---

### 💻 Part 3: C++ Implementation

This implementation follows the logic from the slides.

_Note: The slides use **1-based indexing**. The code below uses standard C++ **0-based indexing**, so the formulas are slightly adjusted (Left = $2i+1$, Right = $2i+2$, Parent = $(i-1)/2$)._

C++

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> // For swap

using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // Helper: Get Parent Index (0-based)
    int parent(int i) { return (i - 1) / 2; }

    // Helper: Get Left Child Index (0-based)
    int left(int i) { return (2 * i) + 1; }

    // Helper: Get Right Child Index (0-based)
    int right(int i) { return (2 * i) + 2; }

    // Core Logic: Heapify Down (Fix violations downwards)
    // Time: O(log N)
    void max_heapify(int i, int n) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        // Compare with Left Child
        if (l < n && heap[l] > heap[largest]) {
            largest = l;
        }
        // Compare with Right Child
        if (r < n && heap[r] > heap[largest]) {
            largest = r;
        }

        // If violation exists (Parent is not the largest)
        if (largest != i) {
            swap(heap[i], heap[largest]); // Swap parent with largest child
            max_heapify(largest, n);      // Recursively fix the affected sub-tree
        }
    }

public:
    // Constructor
    MaxHeap() {}

    // Build Heap from an arbitrary vector
    // Time: O(N) [cite: 430]
    void buildHeap(const vector<int>& input) {
        heap = input;
        int n = heap.size();
        // Start from the last internal node and go up to the root
        // Last internal node formula (0-based): (n/2) - 1
        for (int i = (n / 2) - 1; i >= 0; i--) {
            max_heapify(i, n);
        }
    }

    // Insert a new key
    // Time: O(log N) [cite: 445]
    void insert(int key) {
        heap.push_back(key); // 1. Shape First: Insert at end
        
        // 2. Order Second: Percolate Up
        int i = heap.size() - 1;
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Extract Max (Remove Root)
    // Time: O(log N) [cite: 479]
    int extractMax() {
        if (heap.size() == 0) return -1; // Error

        int maxVal = heap[0];
        
        // 1. Swap Root with Last Leaf
        heap[0] = heap.back();
        
        // 2. Remove Last
        heap.pop_back();

        // 3. Fix the Root (Heapify Down)
        max_heapify(0, heap.size());

        return maxVal;
    }

    // Heap Sort
    // Time: O(N log N) 
    static void heapSort(vector<int>& arr) {
        MaxHeap tempHeap;
        tempHeap.buildHeap(arr); // Step 1: Build Heap (O(N))

        int n = arr.size();
        
        // Use the internal heapify logic to sort in-place
        // Note: For strict in-place sort, we would operate directly on 'arr'
        // This demonstrates the logic described in slide 27
        for (int i = n - 1; i > 0; i--) {
            // Swap root (max) with end
            swap(tempHeap.heap[0], tempHeap.heap[i]);
            
            // "Remove" element by reducing the scope of heapify to i
            tempHeap.max_heapify(0, i);
        }
        arr = tempHeap.heap;
    }

    void print() {
        for (int val : heap) cout << val << " ";
        cout << endl;
    }
};

int main() {
    MaxHeap h;
    
    // Test Build Heap
    vector<int> data = {10, 20, 15, 30, 40};
    cout << "Input Array: ";
    for(int i : data) cout << i << " ";
    cout << endl;

    h.buildHeap(data);
    cout << "After Build Heap: ";
    h.print(); // Expected Root: 40

    // Test Insert
    cout << "Inserting 50..." << endl;
    h.insert(50);
    cout << "Heap: ";
    h.print(); // Expected Root: 50

    // Test Extract Max
    cout << "Extracted Max: " << h.extractMax() << endl; // Should be 50
    cout << "Heap after extraction: ";
    h.print();

    return 0;
}
```