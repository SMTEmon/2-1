---
course: CSE 4303 - Data Structures
lecture: 01
instructor: Asaduzzaman Herok
date: 2025-11-09
tags:
  - data-structures
  - cse
  - introduction
  - memory-allocation
---

# Lecture 01: Introduction & Elementary Structures

## 1. What is a Data Structure?

### Definitions
*   **Data**: Simply values, sets of values, raw facts, or figures without specific meaning.
*   **Data Structure (DS)**: The **logical or mathematical model** of a particular organization of data.
    *   It is a specific way of organizing, storing, and managing data in a computer's memory.
    *   **Focus**:
        1.  **Structure**: How to store data.
        2.  **Efficiency**: How to perform operations on it.

### The "What" vs. The "How"

> [!NOTE] Key Distinction
> **ADT** defines the behavior (interface), while **DS** defines the implementation.

| Abstract Data Type (ADT) | Data Structure (DS) |
| :--- | :--- |
| **The "What"** | **The "How"** |
| Mathematical model defining data set & operations. | Concrete implementation of data storage. |
| Specifies *what* operations are performed. | Specifies *how* operations are performed efficiently. |
| *Example:* Stack (push, pop) | *Example:* Array vs. Linked List implementation. |

---

## 2. Why Study Data Structures?

Efficient data structures are critical for solving real-world problems.
*   **File Systems**: Mapping file names to hard drive sectors.
*   **Search Engines**: Google maps keywords to web pages.
*   **Bioinformatics**: DNA sub-sequence matching.P
*   **Geographic Systems**: Location data management.
*   **Blockchain**: Uses [[Linked Lists]].
*   **Maps**: Finding shortest paths (Distance/Time).
*   **Compression**: Huffman’s encoding.

---

## 3. How We Study Data Structures

We focus on three main pillars:
1.  **Logical Structure**: How elements relate to each other (e.g., file system hierarchy).
2.  **Operations**:
    *   Reading
    *   Searching
    *   Inserting
    *   Deleting
    *   Sorting
3.  **Efficiency**: Time complexity of operations.
    *   *Example:* Searching an unsorted array $\rightarrow O(n)$.
    *   *Example:* Searching a balanced binary search tree $\rightarrow O(\log n)$.

---

## 4. Classification of Data Structures

*   **Primitive**:
    *   Integer, Real Number, Boolean, Character.
*   **Non-Primitive**:
    *   **Linear**: Elements arranged sequentially.
        *   [[Arrays]], [[Linked List]], [[Stack]], [[Queue]].
    *   **Non-Linear**: Elements arranged hierarchically or interconnected.
        *   [[Graph]], [[Tree]].

---

## 5. Elementary Structures Review

### A. Arrays
A collection of elements of the **same type** stored in **contiguous** memory locations.
*   **Pros**:
    *   Fast access via index ($O(1)$).
    *   Simple memory allocation.
*   **Cons**:
    *   Fixed size (static).
    *   Costly insertion/deletion in the middle (requires shifting).

### B. Records (Structures)
A collection of related data items of **different types** grouped under a single name.
*   **Characteristics**: Models real-world entities, stores heterogeneous data.
*   **Pros**: Groups related data, improves readability.
*   **Cons**: Access requires dot operator; not suitable for large collections without being in an array.

### C. Pointers
A variable that stores the **memory address** of another variable.
*   **Pros**:
    *   Enables [[Dynamic Memory Allocation]].
    *   Essential for linked structures (Lists, Trees).
    *   Pass large structures to functions without copying.
*   **Cons**:
    *   Risk of memory leaks.
    *   Unsafe pointer arithmetic.

---

## 6. Memory Allocation Strategies

### 1. Contiguous Memory Allocation
Stores $n$ objects in a single contiguous block (e.g., Array).
*   **Feature**: Direct Random Access.
*   **Drawback**: Resizing is expensive (requires copying data to a new, larger block). The OS cannot guarantee the "next" memory slot is free.

### 2. Linked Memory Allocation
Associates two pieces of data per item: **The Object** + **Reference to next**.
*   **Feature**: Dynamic size.
*   **Drawback**: No Random Access (must traverse from the start). Address is only known by the previous node.

### 3. Indexed Memory Allocation
An **array of pointers** (Index Block) links to a sequence of allocated memory locations.
*   **Mechanism**: `Index Block` -> Points to `Data Block 1`, `Data Block 2`, etc.
*   **Pros**:
    *   **No external fragmentation**: Data blocks don't need to be contiguous.
    *   **Direct Access**: Accessible via the index block.
    *   **Scalability**: Easy to grow large files.
*   **Cons**:
    *   **Overhead**: Extra memory required for the index block.
    *   **Access Time**: Slight delay (must read index block first).