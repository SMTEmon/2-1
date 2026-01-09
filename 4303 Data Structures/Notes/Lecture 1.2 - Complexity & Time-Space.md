---
course: CSE 4303 - Data Structures
lecture: 1.2
date: 2025-11-15
instructor: Asaduzzaman Herok
tags:
  - algorithm
  - complexity
  - big-o
  - cs-theory
---

# Complexity and Time-Space Trade-off

---

## 1. Introduction to Complexity
Complexity analysis estimates the running time or space requirements of an algorithm with respect to the **input size**.

### Why do we care?
*   Large input sizes require efficient algorithms.
*   **Time-Space Trade-off:** Often, increasing memory usage (space) can reduce execution time, and vice-versa.

```
#Solution 1
for i = 2 to n - 1
	if i divides n
		n is not a prime
```

```
#Solution 2
for i = 2 to sqrt(n)
	if i divides n 
		n is not a prime
```

*   *Example:* Checking if $n$ is prime.
    *   **Solution 1:** Loop 2 to $n-1$. Worst case: $n-2$ divisions.
    *   **Solution 2:** Loop 2 to $\sqrt{n}$. Worst case: $\sqrt{n}-1$ divisions.
    *   *Impact:* For $n=10^{10}$, Solution 1 takes ~115 days, Solution 2 takes ~1.66 mins.

### Program Judgement:
- Original specification of task
- work correctly
- Contains documentations
- Code readability
### Performance Judgement:
- Efficient use of primary (RAM) and secondary (SSD/ HDD) storage.
- Acceptable running time

---

## 2. Types of Complexity

### Space Complexity
Amount of memory needed to run the program to completion.
$$S(P) = C + S_p(I)$$
*   **Fixed Space ($C$):** Independent of input size (code size, constants, variables).
*   **Variable Space ($S_p(I)$):** Depends on the particular instance $I$ of the problem $P$ (recursion stack, dynamic memory).

### Time Complexity
Amount of computer time needed to run to completion.
*   We do **not** measure actual time in seconds (hardware dependent).
*   We measure how the time requirement grows as **input size ($n$)** increases.
*   $$T(P) = C + T(I)$$

---

## 3. Time Complexity Analysis

### Basic Approach
1.  **Instruction Counting:** Assign a cost to each line of code.
2.  **Frequency:** Count how many times each line executes based on $n$.
3.  **Growth Rate:** Focus on the rate of growth, ignoring constants and lower-order terms.

**Example: Sum of List**
```cpp
sumOfList(A, n) {
    total = 0;          // 1 unit (once)
    for i=0 to n-1      // n+1 checks (1 extra checking for breaking the condition)
        total += A[i];  // n iterations * 2 units
    return total;       // 1 unit
}
```
*   Total Cost equation: $T(n) = 4n + 4$.
*   Since we ignore constants ($c, c'$), $T(n) \approx cn$.
*   Complexity: **Linear**, or $O(n)$.

### Running Time on Operations
*   **$O(1)$ Constant Time:**
    *   Variable assignment (`=`).
    *   Integer/Bitwise operations (`+`, `-`, `*`, `/`, `%`, `&`, `|`).
    *   Relational/Logical operations (`<`, `>`, `==`, `&&`).
    *   Memory allocation (`new`, `delete`).

---

## 4. Asymptotic Analysis
Evaluating performance in terms of input size (not on actual running time), specifically describing the "mathematical bound" of the curve.

(An algorithm that is asymptotically more efficient will be the best choice for all but very small inputs)

### The Big 'O' Notation ($O$)
*   **Upper Bound** (Worst Case).
*   Measures the longest amount of time an algorithm could possibly take.
*   **Formal Definition:** $f(n) = O(g(n))$ if there exist constants $n_0$ and $c$ such that:
    $$f(n) \leq c \cdot g(n) \quad \text{for all } n > n_0$$
*   *Example:* $2n + 8 = O(n)$ (Linear).

### The Big Omega Notation ($\Omega$)
*   **Lower Bound** (Best Case).
*   Describes the best that can happen.
*   **Formal Definition:** $f(n) = \Omega(g(n))$ if there exist constants $n_0$ and $c$ such that:
    $$f(n) \geq c \cdot g(n) \quad \text{for all } n > n_0$$

### The Big Theta Notation ($\Theta$)
*   **Tight Bound**.
*   Bounded from both top and bottom by the same function type.
*   **Formal Definition:** $f(n) = \Theta(g(n))$ if $f(n) = O(g(n))$ AND $f(n) = \Omega(g(n))$.

---

## 5. Growth Functions (Ranked)
From fastest to slowest growth:

1.  **$\Theta(1)$** - Constant
2.  **$\Theta(\log n)$** - Logarithmic
3.  **$\Theta(n)$** - Linear
4.  **$\Theta(n \log n)$** - Linearithmic
5.  **$\Theta(n^2)$** - Quadratic
6.  **$\Theta(n^3)$** - Cubic
7.  **$2^n, e^n$** - Exponential

$$\Theta(1)< \Theta(\log(n))<\Theta(n)<\Theta(n\log(n))<\Theta(n^2)<\Theta(n^3)<\Theta(2^n)$$

> [!TIP] Dominant Terms
> When calculating complexity, take the dominant term.
> *   $n^6 - 23n^5 + ...$ $\rightarrow$ **$O(n^6)$**
> *   $O(n \log n + n^{1.5})$ $\rightarrow$ **$O(n^{1.5})$**

---

## 6. Analyzing Control Structures

### Blocks of Code
Sequence of statements: Sum of the complexities.
$$Total = \max(Complexity_{block1}, Complexity_{block2})$$

### Conditional Statements (If/Else)
```cpp
if (condition) {
    // true body
} else {
    // false body
}
```
$$Runtime = Cost(condition) + \max(Cost(true\_body), Cost(false\_body))$$

### Condition Controlled Loops (For/While)
*   Initialization, condition checking, and increment are usually $O(1)$.
*   $$Runtime = \text{Iterations} \times \text{Cost of Body}$$
*   **Nested Loops:** Usually multiplicative.
    *   Inner loop runs $N$ times, Outer loop runs $N$ times $\rightarrow O(N^2)$.

---

## 7. Analysis Cases
When data is non-deterministic (e.g., searching a list), runtime varies.

*   **Best Case:** Data is arranged ideally (e.g., item found at index 0). Runtime: $O(1)$.
*   **Worst Case:** Data is arranged in the least ideal way (e.g., item at last index or not present). Runtime: $O(n)$.
*   **Average Case:** Probabilistic expectation.
    *   Assume $1/n$ probability for each location.
    *   Sum of probabilities usually results in the same order as worst case for linear search. Runtime: $O(n)$.
