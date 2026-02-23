***

# 📊 Range Queries: Prefix Sum & Sparse Table

> [!info] Core Idea
> Efficiently querying information (Sum, Min, Max, GCD) over a continuous subarray `[L, R]` without recalculating from scratch every time.

---

## 1. Prefix Sum
Used to efficiently compute the **sum of elements** in a static subarray. It answers queries in constant time by precalculating cumulative sums.

*   **Best for**: Range sum queries, cumulative frequencies.
*   **Limitation**: Does **not** work for Min/Max. Does **not** support updates.
*   **Time Complexity**: $O(N)$ Preprocessing | $O(1)$ Query.

### Precomputation & Formula
To handle 0-based arrays easily, the `pref` array is usually 1-indexed (shifted by 1), starting with a `0`.
*   **Precompute**: `pref[i] = pref[i-1] + a[i-1]`
*   **Query**: `Sum(L, R) = pref[R+1] - pref[L]`

### Example
**Array `a`**:

| idx | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **a[i]** | 3 | 2 | 1 | 3 | 1 | 4 | 2 |

**Prefix Array `pref`**:

| idx | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **pref[i]** | 0 | 3 | 5 | 6 | 9 | 10 | 14 | 16 |

> **Query Example:** `Sum(2, 5)`
> Formula: `pref[5+1] - pref[2] = pref[6] - pref[2]`
> Result: `14 - 5 = 9` (Verification: 1+3+1+4 = 9)

---

## 2. Sparse Table
Used to efficiently answer **idempotent** range queries (Min, Max, GCD) on an **immutable** (static) array. 

*   **Best for**: Range Minimum Query (RMQ), Range Maximum Query, GCD/LCA.
*   **Limitation**: Does **not** support updates (use Segment Trees for updates).
*   **Time Complexity**: $O(N \log N)$ Preprocessing | $O(1)$ Query.
*   **Space Complexity**: $O(N \log N)$.

### Core Concept: Powers of 2
Instead of storing answers for every possible range, a Sparse Table stores precomputed answers for overlapping ranges of lengths that are **powers of 2**.
*   `table[i][j]` represents the answer for the range starting at index `i` with length $2^j$.
*   *Meaning*: It covers the range `[i, i + 2^j - 1]`.
*   *Example*: `table[3][2]` covers a length of $2^2=4$, starting at index 3 $\rightarrow$ Range `[3, 6]`.

### Precomputation Formula
We build the table using dynamic programming. A range of length $2^j$ is split into two halves of length $2^{j-1}$.
> ==**`table[i][j] = min(table[i][j-1], table[i + 2^(j-1)][j-1])`**==

### How $O(1)$ Queries Work (Overlapping Intervals)
To find `min(L, R)` where the window width is $W = R - L + 1$:
1. Find the largest power of 2 that fits inside the window: $j = \lfloor \log_2(W) \rfloor$.
2. Take the minimum of two overlapping blocks of size $2^j$:
   * One starting at the left boundary: `L`
   * One ending at the right boundary: `R`

> [!check] Why Overlap is OK
> Since operations like Min, Max, and GCD are idempotent (e.g., `min(a, a) = a`), overlapping the center of the range doesn't change the final answer!

> ==**`min(L, R) = min(table[L][j], table[R - 2^j + 1][j])`**==

### Example Query Concept
**Query `min(5, 26)`:**
* Width $W = 26 - 5 + 1 = 22$
* Largest power of 2 less than 22 is $16 \rightarrow 2^4$ (so $j = 4$)
* Block 1 (Starts at L): `table[5][4]` (covers 5 to 20)
* Block 2 (Ends at R): `table[26 - 16 + 1][4] = table[11][4]` (covers 11 to 26)
* Output: `min(table[5][4], table[11][4])`

---

## 💻 C++ Code Template (Sparse Table RMQ)

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 100005;
const int LOG = 17; // roughly log2(100005)
int a[MAXN];
int table[MAXN][LOG];

// --- 1. PREPROCESSING O(N log N) ---
void buildSparseTable(int n) {
    // Base case: intervals of length 2^0 = 1
    for(int i = 0; i < n; i++) {
        table[i][0] = a[i];
    }
    
    // Build for intervals of length 2^j
    for(int j = 1; j < LOG; j++) {
        for(int i = 0; i + (1 << j) - 1 < n; i++) {
            // min of left half and right half
            table[i][j] = min(table[i][j-1], table[i + (1 << (j-1))][j-1]);
        }
    }
}

// --- 2. ANSWER QUERIES O(1) ---
int query(int L, int R) {
    int window = R - L + 1;
    // Find largest power of 2 fitting in the window
    int j = log2(window); 
    
    // Overlap the two precomputed intervals
    return min(table[L][j], table[R - (1 << j) + 1][j]);
}
```

> [!warning] Quick Exam Checklists
> - **Sum Query?** Use Prefix Sum. Is it 1-indexed properly to avoid `pref[-1]` out-of-bounds?
> - **Min/Max Query?** Use Sparse Table.
> - **Updates required?** Neither will work well. You need a Segment Tree.
> - **Bitwise Shifts:** `1 << j` is equivalent to $2^j$.