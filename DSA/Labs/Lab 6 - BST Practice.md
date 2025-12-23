
These tasks follow the progression of the lecture: **Insertion/Construction**  **Deletion**  **Utility/Analysis**.

---

### **Islamic University of Technology**

**Lab 06: Binary Search Tree (BST)**
**CSE 4304: Data Structures Lab****

---

### **Task 1: BST Construction & Sorted Traversal**

In this task, you will implement a **Binary Search Tree (BST)** where the structure is determined implicitly by the order of insertion, maintaining the BST property: `Left < Root < Right`.

Unlike the previous lab where you were told exactly where to put a node (Left/Right), here you must find the correct position for every value using the BST insertion logic.

**Requirements:**

1. Define a `Node` structure with `int data`, `left`, and `right` pointers.
2. Implement the `insert(int val)` function:
* If the tree is empty, create a new node.


* If `val < current_node`, recurse Left.


* If `val > current_node`, recurse Right.




3. Implement an **In-order Traversal**. In a valid BST, this traversal *must* yield the values in sorted (ascending) order.



**Input Format:**

* The first line contains an integer , the number of nodes to insert.
* The second line contains  distinct integers to be inserted into the BST in the given order.

**Sample Input:**

```text
6
39 27 45 18 29 40

```

(Note: 39 is the first value, so it becomes the Root ).

**Visual Representation (Reference Slide 3):**

```text
      39
     /  \
   27    45
  /  \   /
18   29 40

```



**Sample Output:**

```text
Inorder Traversal: 18 27 29 39 40 45
Root Node: 39

```

---

### **Task 2: The Resignation (BST Deletion)**

A BST is efficient for data that changes frequently (dynamic sets). In this task, you must handle the removal of nodes while preserving the BST property. You need to implement the **deletion logic** covering all three specific cases discussed in the lecture.

**Requirements:**

1. Implement `deleteNode(int val)` handling these scenarios:
* 
**Case 1 (Leaf Node):** Simply remove the node.


* 
**Case 2 (One Child):** The child replaces the parent.


* 
**Case 3 (Two Children):** Find the **In-order Predecessor** (largest value in the left sub-tree), replace the target value with the predecessor's value, and then delete the predecessor node.
(Note: Slide 22 uses the Predecessor method, though Successor is also valid).





**Input Format:**

* The input from Task 1 (Tree Construction).
* An integer  (number of deletion queries).
*  lines, each containing an integer value to delete.

**Sample Input:**

```text
6
39 27 45 18 29 40
3
18
45
39

```

**Explanation of Deletions:**

1. **Delete 18:** Case 1 (Leaf). 27's left becomes NULL.


2. **Delete 45:** Case 2 (One Child: 40). 40 replaces 45.


3. **Delete 39 (Root):** Case 3 (Two Children). Predecessor is 29. Replace 39 with 29. Delete old 29.



**Sample Output:**

```text
After Deleting 18: 27 29 39 40 45
After Deleting 45: 27 29 39 40
After Deleting 39: 27 29 40
Final Inorder: 27 29 40

```

---

### **Task 3: Efficiency Analytics (Utility & Skewness)**

The efficiency of a BST depends heavily on its **Height**. In the worst case (Skewed Tree), operations take , while in the average case (Balanced), they take .

You must implement utility functions to analyze the "health" of your tree and perform quick lookups.

**Requirements:**

1. 
**`findMin(Node* root)`**: Traverse to the absolute left to find the smallest value.


2. 
**`findMax(Node* root)`**: Traverse to the absolute right to find the largest value.


3. 
**`calcHeight(Node* root)`**: recursively calculate the height of the tree.


4. **`checkSkewed(Node* root)`**: Determine if the tree is skewed.
* 
*Logic:* If , the tree is effectively a Linked List (Skewed).





**Input Format:**

* Standard Tree Construction Input.
* A request to print analytics.

**Sample Input 1 (Balanced-ish):**

```text
7
39 27 45 18 29 40 54

```

**Sample Output 1:**

```text
Minimum: 18
Maximum: 54
Height: 2
Status: Normal BST

```

**Sample Input 2 (Skewed):**

```text
4
10 20 30 40

```

(Reference Slide 5 for visualization of this input )

**Sample Output 2:**

```text
Minimum: 10
Maximum: 40
Height: 3
Status: Skewed Tree (Inefficient)

```



The implementation strictly follows the logic provided in your lecture slides, specifically using the **Predecessor** for deletion 1and the specific **Height** calculation formula2.

### **Complete C++ Solution**

C++

```cpp
// ==========================================
// TASK 1: Structure & Insertion
// ==========================================

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Logic based on Slide 10 [cite: 215-227]
Node* insert(Node* root, int val) {
    // 1. If tree is empty, return a new node
    if (root == nullptr) {
        return new Node(val);
    }
    // 2. Otherwise, recur down the tree
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // 3. Return the (unchanged) node pointer
    return root;
}

// In-order traversal to verify sorted order (Left -> Root -> Right)
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ==========================================
// TASK 2: Deletion (The Resignation)
// ==========================================

// Helper to find the largest node in the left subtree (Predecessor)
// Logic based on Slide 22 [cite: 508]
Node* findLargestNode(Node* root) {
    if (root == nullptr || root->right == nullptr) {
        return root;
    }
    return findLargestNode(root->right);
}

// Logic based on Slide 13-17 [cite: 330-345, 360, 528]
Node* deleteNode(Node* root, int val) {
    if (root == nullptr) return root;

    // Navigate to the node
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    } else {
        // Node found. Handle the 3 cases:
        
        // Case 1 & 2: Leaf node or One child 
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two Children [cite: 340]
        // Find In-order Predecessor (Largest in Left Subtree)
        Node* temp = findLargestNode(root->left);

        // Copy predecessor's content to this node [cite: 528]
        root->data = temp->data;

        // Delete the predecessor [cite: 550]
        root->left = deleteNode(root->left, temp->data);
    }
    return root;
}

// ==========================================
// TASK 3: Efficiency Analytics
// ==========================================

// Logic based on Slide 25 [cite: 572-574]
int findMin(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return -1;
    }
    if (root->left == nullptr) {
        return root->data;
    }
    return findMin(root->left);
}

// Logic based on Slide 28 [cite: 639-641]
int findMax(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return -1;
    }
    if (root->right == nullptr) {
        return root->data;
    }
    return findMax(root->right);
}

// Logic based on Slide 30 [cite: 687-721]
// Note: This implementation counts nodes on the longest path (Node-based height)
int calcHeight(Node* root) {
    if (root == nullptr) return 0;
    
    int leftHeight = calcHeight(root->left);
    int rightHeight = calcHeight(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void checkSkewed(Node* root) {
    int h = calcHeight(root);
    int n = countNodes(root);
    
    cout << "Height: " << h << endl;
    
    // Logic based on Slide 23: In a skewed tree, h = n 
    // (Assuming height is calculated as number of nodes along the path)
    if (h == n && n > 1) { 
        cout << "Status: Skewed Tree (Inefficient)" << endl;
    } else {
        cout << "Status: Normal BST" << endl;
    }
}

// ==========================================
// Main Function to Test All Tasks
// ==========================================

int main() {
    Node* root = nullptr;
    int N, val;

    // --- TASK 1 INPUT ---
    // Sample Input: 6 nodes -> 39 27 45 18 29 40
    cout << "Enter number of nodes (N): ";
    cin >> N;
    cout << "Enter " << N << " values: ";
    for (int i = 0; i < N; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\n--- Task 1: Inorder Traversal ---" << endl;
    inorder(root);
    cout << endl;

    // --- TASK 3 ANALYTICS (Running this before deletion to see full stats) ---
    cout << "\n--- Task 3: Analytics ---" << endl;
    if (root != nullptr) {
        cout << "Minimum: " << findMin(root) << endl;
        cout << "Maximum: " << findMax(root) << endl;
        checkSkewed(root);
    }

    // --- TASK 2 INPUT ---
    // Sample Deletions: 18, 45, 39
    int Q;
    cout << "\nEnter number of values to delete (Q): ";
    cin >> Q;
    cout << "Enter values to delete: ";
    for (int i = 0; i < Q; i++) {
        cin >> val;
        cout << "\nDeleting " << val << "..." << endl;
        root = deleteNode(root, val);
        cout << "Inorder after deletion: ";
        inorder(root);
        cout << endl;
    }
    
    return 0;
}
```

### **Explanation of Solutions**

1. **Task 1 (Construction):**
    
    - We use the recursive `insert` logic from **Slide 10**.
        
    - If the new value is smaller, it goes left; if larger, it goes right. This automatically sorts the data, which is confirmed by the `inorder` function printing values in ascending order3.
        
2. **Task 2 (Deletion):**
    
    - We handle **Case 1 & 2** (Leaf or One Child) by simply bypassing the node (returning `root->left` or `root->right`)4.
        
    - For **Case 3** (Two Children), we strictly follow **Slide 13** and **Slide 22** by finding the **Predecessor** (largest in the left subtree) using `findLargestNode(root->left)`5555. We replace the target node's data with the predecessor's data and then recursively delete the predecessor.
        
3. **Task 3 (Analytics):**
    
    - **Min/Max:** We traverse as far left as possible for the minimum 6and as far right as possible for the maximum7.
        
    - **Skewed Check:** As per **Slide 23**, a tree is skewed if its height equals the number of nodes ($h = n$)8. This indicates it has degenerated into a Linked List, offering $O(n)$ performance instead of $O(\log n)$9.


---

### **Problem 1: The Conflict Resolution (Lowest Common Ancestor)**

Concept: Hierarchy & Ancestry

Difficulty: Medium

CP Link: LeetCode 235: Lowest Common Ancestor of a BST

Problem Statement:

In a large corporate hierarchy structured as a BST (where IDs are inserted based on seniority), you are given the Employee IDs of two conflicting employees, P and Q.

To resolve the conflict, you must report it to their **lowest ranking common superior**. This is the deepest node in the tree that has both `P` and `Q` as descendants (where a node can be a descendant of itself).

**Input Format:**

- Standard BST construction input (N nodes followed by values).
    
- Two integers: `P` and `Q`.
    

Logic/Hint:

You do not need to store parent pointers or trace paths. Use the BST property:

- Start at the `Root`.
    
- If both `P` and `Q` are **smaller** than `Root`, the answer lies in the **Left** subtree2.
    
- If both `P` and `Q` are **greater** than `Root`, the answer lies in the **Right** subtree3.
    
- If the `Root` is between `P` and `Q` (or equal to one of them), **Current Root** is the split point (the answer).
    

**Sample Input:**

Plaintext

```
6
Root: 20
20 10 30 5 15 25
Query: 5 15
```

**Sample Output:**

Plaintext

```
Lowest Common Superior: 10
```

---

### **Problem 2: The Smart Database Query (Range Sum)**

Concept: Pruning Search Space

Difficulty: Easy-Medium

CP Link: LeetCode 938: Range Sum of BST

Problem Statement:

You are managing a database of salaries stored in a BST. To analyze the budget, you need to calculate the sum of all salaries that fall within a specific range [Low, High] (inclusive).

Standard traversal is $O(N)$, but since this is a BST, you must optimize the search to skip subtrees that cannot possibly contain valid data4.

**Input Format:**

- Standard BST construction input.
    
- Two integers: `Low` and `High`.
    

Logic/Hint:

Write a recursive function getRangeSum(node, low, high):

1. If `node` is `NULL`, return 0.
    
2. If `node->data < Low`: The current node and everything to its **Left** are too small. **Only** recurse Right.
    
3. If `node->data > High`: The current node and everything to its **Right** are too large. **Only** recurse Left.
    
4. Otherwise (node is inside range): Return `node->data` + recurse Left + recurse Right.
    

**Sample Input:**

Plaintext

```
6
Root: 10
10 5 15 3 7 18
Range: 7 15
```

**Sample Output:**

Plaintext

```
Sum: 32  (Values 7 + 10 + 15)
```

---

### **Problem 3: The K-th Ranked Officer (Order Statistics)**

Concept: In-order Traversal

Difficulty: Medium

CP Link: LeetCode 230: Kth Smallest Element in a BST

Problem Statement:

Your system stores user scores in a BST. You need to identify the user with the $k$-th lowest score in the entire system.

**Input Format:**

- Standard BST construction input.
    
- An integer `k` (1-based index).
    

Logic/Hint:

Recall from the lecture that a BST's structure allows for sorted data retrieval5.

- Perform an **In-order Traversal** (Left $\to$ Root $\to$ Right).
    
- Keep a counter. Increment it every time you _visit_ (print/access) a node.
    
- When the counter equals `k`, stop and return that value.
    
- _Optimization:_ You don't need to store the array; just return as soon as you hit the count.
    

**Sample Input:**

Plaintext

```
5
Root: 3
3 1 4 2 5
k: 3
```

_Visual Tree:_

Plaintext

```
    3
   / \
  1   4
   \   \
    2   5
```

**Sample Output:**

Plaintext

```
3rd Smallest: 3
(Sorted order is: 1, 2, 3, 4, 5)
```

### **Solution 1: Lowest Common Ancestor (LCA)**

**Logic:** This solution utilizes the core BST property described in the slides: Left Subtree $<$ Root $<$ Right Subtree 1.

- If both conflicting IDs (`p` and `q`) are **smaller** than the current root, the common ancestor must be in the **Left** subtree.
    
- If both are **larger**, it must be in the **Right** subtree.
    
- If they are on different sides (one smaller, one larger), or if one matches the current root, then the **current root** is the split point (the LCA).
    

C++

```cpp
// ==========================================
// Problem 1: Lowest Common Ancestor
// ==========================================
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Standard BST Insertion
Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// Logic: Use BST property to direct the search
Node* findLCA(Node* root, int p, int q) {
    if (root == nullptr) return nullptr;

    // If both values are smaller than root, LCA is in the left subtree
    if (p < root->data && q < root->data) {
        return findLCA(root->left, p, q);
    }

    // If both values are greater than root, LCA is in the right subtree
    if (p > root->data && q > root->data) {
        return findLCA(root->right, p, q);
    }

    // We have found the split point, or one of the nodes is the root itself
    return root;
}

int main() {
    Node* root = nullptr;
    int N, val, p, q;

    // Input Format: N, then N values, then p and q
    // Example Input: 6 20 10 30 5 15 25 5 15
    cout << "Enter number of nodes: ";
    cin >> N;
    cout << "Enter values: ";
    for(int i=0; i<N; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "Enter two values (p and q) to find LCA: ";
    cin >> p >> q;

    Node* lca = findLCA(root, p, q);
    if (lca != nullptr) {
        cout << "Lowest Common Ancestor of " << p << " and " << q << " is: " << lca->data << endl;
    } else {
        cout << "Tree is empty or values not found." << endl;
    }

    return 0;
}
```

---

### **Solution 2: Range Sum of BST**

**Logic:** This applies the concept of "Search Efficiency" mentioned in the slides 2. Instead of visiting every node ($O(N)$), we "prune" (skip) subtrees that cannot possibly contain valid data.

- If `root->data < Low`, we don't need to check the Left child (everything there is even smaller).
    
- If `root->data > High`, we don't need to check the Right child.
    

C++

```cpp
// ==========================================
// Problem 2: Range Sum of BST
// ==========================================
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// Logic: Prune the search based on range boundaries
int getRangeSum(Node* root, int low, int high) {
    if (root == nullptr) return 0;

    // Optimization 1: Current node is too small. 
    // Everything in the left subtree is also too small. Skip Left.
    if (root->data < low) {
        return getRangeSum(root->right, low, high);
    }

    // Optimization 2: Current node is too big.
    // Everything in the right subtree is also too big. Skip Right.
    if (root->data > high) {
        return getRangeSum(root->left, low, high);
    }

    // Current node is inside the range. Include it and check both children.
    return root->data + getRangeSum(root->left, low, high) + getRangeSum(root->right, low, high);
}

int main() {
    Node* root = nullptr;
    int N, val, low, high;

    // Example Input: 6 10 5 15 3 7 18 7 15
    cout << "Enter number of nodes: ";
    cin >> N;
    cout << "Enter values: ";
    for(int i=0; i<N; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "Enter Range (Low High): ";
    cin >> low >> high;

    cout << "Sum of values in range [" << low << ", " << high << "] is: " 
         << getRangeSum(root, low, high) << endl;

    return 0;
}
```

---

### **Solution 3: K-th Smallest Element**

**Logic:** This relies on the property that **In-order Traversal** of a BST yields data in sorted order3.

- We traverse the tree In-order (Left $\rightarrow$ Root $\rightarrow$ Right).
    
- We maintain a counter. Every time we visit a node, we increment the counter.
    
- When `counter == k`, we have found the $k$-th smallest value.
    

C++

```cpp
// ==========================================
// Problem 3: K-th Smallest Element
// ==========================================
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// Helper function for In-order traversal
// We use pass-by-reference (&) for count and result to maintain state across recursion
void findKth(Node* root, int k, int &count, int &result) {
    if (root == nullptr || count >= k) return;

    // 1. Go Left
    findKth(root->left, k, count, result);

    // 2. Visit Node
    count++;
    if (count == k) {
        result = root->data;
        return; // Stop processing once found
    }

    // 3. Go Right
    findKth(root->right, k, count, result);
}

int kthSmallest(Node* root, int k) {
    int count = 0;
    int result = -1; // Default value if not found
    findKth(root, k, count, result);
    return result;
}

int main() {
    Node* root = nullptr;
    int N, val, k;

    // Example Input: 5 3 1 4 2 5 3
    cout << "Enter number of nodes: ";
    cin >> N;
    cout << "Enter values: ";
    for(int i=0; i<N; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "Enter k: ";
    cin >> k;

    int ans = kthSmallest(root, k);
    cout << "The " << k << "-th smallest element is: " << ans << endl;

    return 0;
}
```