---
course: CSE 4303 - Data Structures
lecture: 2.1
date: 2025-11-17
instructor: Asaduzzaman Herok
tags:
  - Array
  - LinkedLists
---

***

## 1. Arrays

### Problem Scenario
*   **Context:** Storing marks for 20 students.
*   **Primitive Approach:** Creating 20 distinct integer variables (`mark1`, `mark2`...). This requires 20 input statements and 20 output statements.
*   **Array Approach:** Use an array of integers. Best for working with **homogeneous data** (similar kind of data).

### Complexity of Array Operations

| Operation           | Front / 1st | Arbitrary Position |      Back / $n^{th}$      |
| :------------------ | :---------: | :----------------: | :-----------------------: |
| **Find (Unsorted)** | $\Theta(1)$ |    $\Theta(n)$     |        $\Theta(n)$        |
| **Find (Sorted)**   | $\Theta(1)$ |  $\Theta(\log n)$  |        $\Theta(n)$        |
| **Insert**          | $\Theta(n)$ |    $\Theta(n)$     | $\Theta(1)$ (if not full) |
| **Erase**           | $\Theta(n)$ |    $\Theta(n)$     |        $\Theta(1)$        |

> **Note:** Array insertion/deletion at the front or middle is slow ($\Theta(n)$) because elements must be shifted.

---

## 2. Linked List (Singly)

### Motivation: Music Player Playlist
Scenario: A playlist module (like Spotify).
**Requirements:**
*   Add song before/after current.
*   Remove currently playing song.
*   Reorder songs dynamically.
*   Handle large playlists without performance issues.
*   *Conclusion:* Arrays are inefficient for these dynamic operations; Linked Lists are preferred.

### Definition
A linear collection of data elements called **nodes**.
*   **Node Structure:** `[ Data | Next Pointer ]`
*   **Visual:** `[Start|Null] -> [10|->] -> [20|->] -> [30|X]`

### Pros & Cons

| Pros | Cons |
| :--- | :--- |
| ✅ Dynamic Size | ❌ Random access is not possible (must traverse) |
| ✅ Efficient insertion and deletion | ❌ Extra memory overhead for pointer variables |
| ✅ No wasted memory (allocate as needed) | ❌ Searching is slow |
| ✅ Easily used for complex data structures | ❌ Dynamic memory allocation is generally slower than static |

---

## 3. Linked List Operations

### A. Traversing
Accessing nodes in order to process them.

**Pseudo Code:**
```text
Step 1: SET PTR = START
Step 2: Repeat Steps 3 and 4 while PTR != NULL
Step 3:     Apply Process to PTR -> DATA
Step 4:     SET PTR = PTR -> NEXT
        [END OF LOOP]
Step 5: EXIT
```
*   **Complexity:** $O(n)$

### B. Searching
Finding a particular element. Returns address if found.

**Pseudo Code:**
```text
Step 1: SET PTR = START
Step 2: Repeat Steps 3 and 4 while PTR != NULL
Step 3:     IF VAL == PTR -> DATA
                SET POS = PTR
                Go To Step 5
            ELSE
                SET PTR = PTR -> NEXT
            [END OF IF]
        [END OF LOOP]
Step 5: EXIT
```
*   **Complexity:** $O(n)$

### C. Insertion

#### Case 1: Insert at Beginning
New node becomes the new Head/Start.
*   **Complexity:** $\Theta(1)$

**Pseudo Code:**
1. Check `AVAIL` (Overflow).
2. `SET NEW_NODE = AVAIL`
3. `SET NEW_NODE -> DATA = VAL`
4. `SET NEW_NODE -> NEXT = START`
5. `SET START = NEW_NODE`

#### Case 2: Insert at End
Traverse to the last node and link the new node.
*   **Complexity:** $\Theta(n)$ (if traversing from start) or $\Theta(1)$ (if keeping a Tail pointer).

**Pseudo Code:**
1. Initialize `NEW_NODE`.
2. `SET NEW_NODE -> NEXT = NULL`
3. `SET PTR = START`
4. Loop `while PTR -> NEXT != NULL`:
    * `SET PTR = PTR -> NEXT`
5. `SET PTR -> NEXT = NEW_NODE`

#### Case 3: Insert After a Given Node
Insert logic requires maintaining a `PREPTR` (Previous Pointer).
*   **Complexity:** $\Theta(1)$ *assuming we are already at the specific node*, otherwise $O(n)$ to find it.

**Pseudo Code:**
1. Traverse to find the node containing `NUM`.
2. `SET PREPTR -> NEXT = NEW_NODE`
3. `SET NEW_NODE -> NEXT = PTR` (where PTR is the node after PREPTR)

---

### D. Deletion

#### Case 1: Delete First Node
Update Start to point to the second node.
*   **Complexity:** $\Theta(1)$

**Pseudo Code:**
1. `IF START = NULL` (Underflow).
2. `SET PTR = START`
3. `SET START = START -> NEXT`
4. `FREE PTR`

#### Case 2: Delete Last Node
Traverse to the *second to last* node to set its next pointer to NULL.
*   **Complexity:** $O(n)$ (Must traverse to find the end).

**Pseudo Code:**
1. `SET PTR = START`
2. Loop `while PTR -> NEXT != NULL`:
    * `SET PREPTR = PTR`
    * `SET PTR = PTR -> NEXT`
3. `SET PREPTR -> NEXT = NULL`
4. `FREE PTR`

#### Case 3: Delete Node After Given Node `NUM`
Find the node `NUM` and bypass the node immediately following it.

**Pseudo Code:**
1. Traverse until `PREPTR -> DATA != NUM`.
2. `SET TEMP = PTR` (Node to be deleted)
3. `SET PREPTR -> NEXT = PTR -> NEXT` (Bypass TEMP)
4. `FREE TEMP`

---

## 4. Complexity Summary (Linked List)

| Operation | Front / 1st Node | $k^{th}$ Node | Back / $n^{th}$ Node |
| :--- | :---: | :---: | :---: |
| **Find** | $\Theta(1)$ | $O(n)$ | $\Theta(1)^*$ |
| **Insert Before** | $\Theta(1)$ | $\Theta(n)$ | $\Theta(n)$ |
| **Insert After** | $\Theta(1)$ | $\Theta(1)^\dagger$ | $\Theta(1)^*$ |
| **Replace** | $\Theta(1)$ | $\Theta(1)^\dagger$ | $\Theta(1)$ |
| **Erase** | $\Theta(1)$ | $O(n)$ | $O(n)$ |
| **Next** | $\Theta(1)$ | $\Theta(1)^\dagger$ | (n/a) |
| **Previous** | (n/a) | $\Theta(n)$ | $\Theta(n)$ |

*   `*` : Assuming keeping a **tail pointer**.
*   `†` : Assuming you are currently **at** the $k^{th}$ node (have the pointer).

---

## References
*   **Textbook:** *Data Structures Using C* (2nd Edition) by Reema Thareja.
*   **Chapters:** 6.1, 6.2 (Covered topics only).