
# Huffman Coding & Trees

**Tags:** #algorithm #compression #datastructures #greedy #cs
**Date:** 2025-12-24

---

## 1. Overview
**Huffman Coding** is a popular algorithm used for **lossless data compression**. It reduces the size of data without losing any details.

* **Core Idea:** Assign shorter binary codes to characters that appear frequently and longer binary codes to characters that appear rarely.
* **Type:** Greedy Algorithm.
* **Structure:** Uses a binary tree (Huffman Tree) to determine the codes.
* **Property:** It creates **Prefix Codes** (no code is a prefix of another), which ensures there is no ambiguity during decoding.

---

## 2. How it Works (The Algorithm)

1.  **Count Frequencies:** Calculate the frequency of each character in the string.
2.  **Create Leaf Nodes:** Create a leaf node for each character containing its frequency.
3.  **Priority Queue:** Put all nodes into a priority queue (min-heap), sorted by frequency (lowest first).
4.  **Build the Tree:**
    * Extract the two nodes with the **smallest** frequencies ($min_1$ and $min_2$).
    * Create a new internal parent node. Its frequency is the sum of the two extracted nodes: $freq = freq(min_1) + freq(min_2)$.
    * Make $min_1$ the left child and $min_2$ the right child.
    * Insert the new parent node back into the priority queue.
5.  **Repeat:** Repeat step 4 until only **one** node remains in the queue. This node is the **root**.
6.  **Assign Bits:** Traverse the tree from the root. Assign `0` for left edges and `1` for right edges.

---

## 3. Step-by-Step Example

**Input String:** `"BEEP BOOP BEER!"` (ignoring spaces/punctuation for simplicity, let's use a standard frequency set).

**Dataset Example:**
Let's use the following characters and their frequencies:

| Character | Frequency |
| :--- | :--- |
| **A** | 5 |
| **B** | 9 |
| **C** | 12 |
| **D** | 13 |
| **E** | 16 |
| **F** | 45 |

### Construction Steps:

1.  **Sort:** `[A:5, B:9, C:12, D:13, E:16, F:45]`
2.  **Merge A (5) + B (9):**
    * Sum = 14.
    * New List: `[C:12, D:13, (AB):14, E:16, F:45]`
3.  **Merge C (12) + D (13):**
    * Sum = 25.
    * New List: `[(AB):14, E:16, (CD):25, F:45]`
4.  **Merge (AB) (14) + E (16):**
    * Sum = 30.
    * New List: `[(CD):25, (ABE):30, F:45]`
5.  **Merge (CD) (25) + (ABE) (30):**
    * Sum = 55.
    * New List: `[F:45, (CDABE):55]`
6.  **Merge F (45) + (CDABE) (55):**
    * Sum = 100.
    * **Tree Complete.**

---

## 4. Visualizing the Tree (Mermaid)

> [!TIP]
> **Reading the Code:** Left edges are `0`, Right edges are `1`.

```mermaid
graph TD
    Root((100)) --> F[F: 45]
    Root --> Node55((55))
    
    Node55 --0--> Node25((25))
    Node55 --1--> Node30((30))
    
    Node25 --0--> C[C: 12]
    Node25 --1--> D[D: 13]
    
    Node30 --0--> Node14((14))
    Node30 --1--> E[E: 16]
    
    Node14 --0--> A[A: 5]
    Node14 --1--> B[B: 9]
    
    style Root fill:#f9f,stroke:#333,stroke-width:2px
    style F fill:#bbf
    style C fill:#bbf
    style D fill:#bbf
    style E fill:#bbf
    style A fill:#bbf
    style B fill:#bbf
````

### Generated Codes

| **Character** | **Path**                        | **Binary Code** | **Bit Length** |
| ------------- | ------------------------------- | --------------- | -------------- |
| **F**         | Left (0)                        | `0`             | 1              |
| **C**         | Right -> Left -> Left           | `100`           | 3              |
| **D**         | Right -> Left -> Right          | `101`           | 3              |
| **A**         | Right -> Right -> Left -> Left  | `1100`          | 4              |
| **B**         | Right -> Right -> Left -> Right | `1101`          | 4              |
| **E**         | Right -> Right -> Right         | `111`           | 3              |

_Notice: 'F' is the most frequent (45) and gets the shortest code (1 bit). 'A' is the least frequent (5) and gets the longest code (4 bits)._

---

## Decoding (The Reverse Process)

Decoding a Huffman encoded string is simple because of the **Prefix Property** (no code overlaps with the start of another).

**Algorithm:**

1. Start at the **Root** of the Huffman Tree.    
2. Read the encoded binary string bit by bit.    
3. **If the bit is '0':** Move to the **Left** child.    
4. **If the bit is '1':** Move to the **Right** child.
    
5. **Check Node:**
    
    - If the current node is a **Leaf Node** (it has no children), you have found a character!        
    - Print/Store the character.        
    - Reset your position back to the **Root** to decode the next character.        
    - Repeat until the string ends.
        

**Example Trace:**

- **Encoded String:** `1001101`    
- **Tree:** (Refer to diagram above)    
    1. Start at Root. Read `1` -> Go Right (Node 55).        
    2. Read `0` -> Go Left (Node 25).        
    3. Read `0` -> Go Left (Node C). **Leaf Found!** Output: **C**. Reset to Root.        
    4. Read `1` -> Go Right (Node 55).        
    5. Read `1` -> Go Right (Node 30).        
    6. Read `0` -> Go Left (Node 14).        
    7. Read `1` -> Go Right (Node B). **Leaf Found!** Output: **B**. Reset to Root.
        
- **Final Output:** `CB`
## 5. Complexity Analysis

- **Time Complexity:** $O(n \log n)$    
    - $n$ is the number of unique characters.        
    - The priority queue operations (insert/extract) take $\log n$. We do this $2n-1$ times.
        
- **Space Complexity:** $O(n)$    
    - To store the tree nodes.

---

### **Summary of Key Concepts**

* **Prefix Rule:** No code is a prefix of another (e.g., if A is `0`, B cannot be `01`). This allows us to decode the stream `01...` instantly as `A` then `...` without waiting for more bits.
* 
* **Compression Ratio:** Huffman coding typically saves 20% to 90% space depending on the data's redundancy.


```cpp

// A Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Comparison object to order the Min-Heap
struct Compare {
    bool operator()(Node* l, Node* r) {
        // Higher frequency items have lower priority in the queue
        // so the lowest frequency comes to the top (Min-Heap behavior)
        return l->freq > r->freq;
    }
};

// Recursive function to print codes
void printCodes(Node* root, string str) {
    if (!root) return;

    // If this node is a leaf (it has a character data), print it
    // Internal nodes are initialized with '$'
    if (root->ch != '$') {
        cout << root->ch << ": " << str << "\n";
    }
    
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct Node *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new Node(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted
        // node as left and right children of this new node.
        // '$' is a special value for internal nodes (not used)
        top = new Node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    cout << "Huffman Codes:\n";
    printCodes(minHeap.top(), "");
}

// Driver Code
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    
    int size = sizeof(arr) / sizeof(arr[0]);
    
    HuffmanCodes(arr, freq, size);
    
    return 0;
}
```


## 7. Benefits & Comparison

| Feature            | Fixed-Length (ASCII)                | Variable-Length (Huffman)                   |
| :----------------- | :---------------------------------- | :------------------------------------------ |
| **Bit Assignment** | All chars get equal bits (e.g., 8). | Frequent chars get few bits; Rare get more. |
| **Total Size**     | Large (Wasteful).                   | Small (Efficient).                          |
| **Complexity**     | Simple to implement.                | Requires building a tree.                   |
| **Use Case**       | RAM/Memory access (Arrays).         | Storage & Transmission (Zip, JPEG).         |

**Real World Example:**
Compressing the word **"BANANA"**:
* **Standard (8-bit):** 48 bits total.
* **Huffman:** ~9 bits total.
* **Savings:** ~81% reduction.