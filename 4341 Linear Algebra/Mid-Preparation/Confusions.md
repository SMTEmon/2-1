
## Basis Vectors 

If the null space consists of all linear combinations of 2 vectors (let's call them $\mathbf{v}_1$ and $\mathbf{v}_2$), then **those two vectors themselves are the basis vectors**.

The Basis:

$$\left\{ \mathbf{v}_1, \mathbf{v}_2 \right\}$$

### **Why?**

A "basis" is just the smallest list of vectors required to generate the entire space.

- If you say the space is made of "all combinations of vector A and vector B," you have already identified the ingredients.
    
- As long as vector A is not a multiple of vector B (meaning they point in different directions), they are the basis.


### **Example Interpretation**

Imagine solving a system $Ax=0$ and getting a final answer that looks like this:

$$\begin{bmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{bmatrix} = c_1 \begin{bmatrix} 1 \\ 0 \\ 2 \\ 0 \end{bmatrix} + c_2 \begin{bmatrix} 0 \\ 1 \\ -3 \\ 1 \end{bmatrix}$$

- Here, the null space is described as "combinations of two vectors."
    
- This means there were **2 Free Variables** ($c_1$ and $c_2$).
    
- The Basis for the Null Space is simply the set of those two special solutions:
    
    $$\text{Basis} = \left\{ \begin{bmatrix} 1 \\ 0 \\ 2 \\ 0 \end{bmatrix}, \begin{bmatrix} 0 \\ 1 \\ -3 \\ 1 \end{bmatrix} \right\}$$
    

### **Visualizing it**

- **1 Basis Vector:** The null space is a **Line**. (Like the problem you just solved).
    
- **2 Basis Vectors:** The null space is a **Plane** (a flat 2D sheet slicing through multidimensional space).
    
- **3 Basis Vectors:** The null space is a **3D Hyperplane** (a 3D space inside a larger dimension).
    

### **One Important Rule (The "Gotcha")**

The two vectors must be Linearly Independent.

If your two vectors are multiples of each other (e.g., $\mathbf{v}_1 = (1,1)$ and $\mathbf{v}_2 = (2,2)$), then they define the same line. In that case, the basis is just one of them, not both. However, in Gaussian elimination problems, the "Special Solutions" you find are always independent.

## Row Exchange

Yes, absolutely. You can **always** exchange (swap) rows in an augmented matrix during elimination.

In fact, swapping rows is one of the three "Elementary Row Operations" allowed in linear algebra (along with scaling a row and adding one row to another).

### **Why is this allowed?**

Think about what the augmented matrix represents. Each row is just an equation.
If you have a system of two equations:

1. $2x + 3y = 5$    
2. $4x - y = 7$
    
If you swap them, you get:
1. $4x - y = 7$    
2. $2x + 3y = 5$
    
Did the math change? **No.** The lines still intersect at the exact same point. You just listed them in a different order.
### **The One Golden Rule**

When you swap rows in an augmented matrix $[A|b]$, you must swap the **entire row**, extending all the way across the vertical line.

- **Correct:** Swap the coefficients (left side) AND the answer values (right side).    
- **Incorrect:** Swapping only the left side ($A$) while leaving the right side ($b$) untouched. This would essentially be assigning Equation 1's answer to Equation 2's logic, which destroys the system.
    
### **When should you swap rows?**

There are three main reasons you would want to do this:
1. To avoid a Zero Pivot (Mandatory):    
    If your pivot position has a 0 in it, you must swap with a row below it. You cannot divide by zero or use zero to eliminate other numbers.    
    $$\begin{bmatrix} 0 & 2 & 1 \\ 3 & 4 & 5 \end{bmatrix} \rightarrow \text{Impossible to start. Swap rows!} \rightarrow \begin{bmatrix} 3 & 4 & 5 \\ 0 & 2 & 1 \end{bmatrix}$$
    
2. To avoid Fractions (Strategic):    
    This is what I did in the previous solution.
    
    - Row 1 started with a `3`. Eliminating with `3` would introduce fractions like $1/3$.        
    - Row 2 started with a `1`.        
    - By swapping, the pivot became `1`, making the math much cleaner integers.
    - 
3. For Precision (Computer Science):    
    Computers always swap rows to put the largest possible number in the pivot position (called "Partial Pivoting"). Dividing by a tiny number (like $0.00001$) causes massive rounding errors, so swapping for a larger number keeps the answer accurate.


## Four Fundamental Spaces

Find a basis for the row space, column space, and null space of the matrix given below: 
### **The Original Matrix**

$$A = \begin{bmatrix} 3 & 4 & 0 & 7 \\ 1 & -5 & 2 & -2 \\ -1 & 4 & 0 & 3 \\ 1 & -1 & 2 & 2 \end{bmatrix}$$

---

### **Step 1: Get a Leading 1 (Pivot) in Row 1**

To avoid dealing with fractions early on (like dividing the first row by 3), we can swap **Row 1** and **Row 2**.
- **Operation:** $R_1 \leftrightarrow R_2$    

$$\begin{bmatrix} \mathbf{1} & -5 & 2 & -2 \\ 3 & 4 & 0 & 7 \\ -1 & 4 & 0 & 3 \\ 1 & -1 & 2 & 2 \end{bmatrix}$$

### **Step 2: Clear Column 1**

Now, use the pivot in Row 1 (the bold **1**) to eliminate the numbers below it ($3$, $-1$, and $1$).

- $R_2 \leftarrow R_2 - 3R_1$    
- $R_3 \leftarrow R_3 + R_1$    
- $R_4 \leftarrow R_4 - R_1$    

**Calculations:**

- $R_2$: $[3-3, 4-(-15), 0-6, 7-(-6)] \rightarrow [0, 19, -6, 13]$    
- $R_3$: $[-1+1, 4-5, 0+2, 3-2] \rightarrow [0, -1, 2, 1]$    
- $R_4$: $[1-1, -1-(-5), 2-2, 2-(-2)] \rightarrow [0, 4, 0, 4]$
    

$$\begin{bmatrix} 1 & -5 & 2 & -2 \\ 0 & 19 & -6 & 13 \\ 0 & -1 & 2 & 1 \\ 0 & 4 & 0 & 4 \end{bmatrix}$$

### **Step 3: Get a Pivot in Row 2**

We need a simple pivot for the second column. Notice that **Row 4** $[0, 4, 0, 4]$ is divisible by 4. Let's divide it and then swap it into the second row position.

- **Operation 1:** $R_4 \leftarrow R_4 / 4$ (Result: $[0, 1, 0, 1]$)    
- **Operation 2:** Swap $R_2 \leftrightarrow R_4$    

$$\begin{bmatrix} 1 & -5 & 2 & -2 \\ 0 & \mathbf{1} & 0 & 1 \\ 0 & -1 & 2 & 1 \\ 0 & 19 & -6 & 13 \end{bmatrix}$$

### **Step 4: Clear Column 2**

Use the new pivot in Row 2 to eliminate the entries below it ($-1$ and $19$) and above it ($-5$).

- $R_3 \leftarrow R_3 + R_2$    
- $R_4 \leftarrow R_4 - 19R_2$    
- $R_1 \leftarrow R_1 + 5R_2$
    

**Calculations:**

- $R_3$: $[0, -1+1, 2+0, 1+1] \rightarrow [0, 0, 2, 2]$
    
- $R_4$: $[0, 19-19, -6-0, 13-19] \rightarrow [0, 0, -6, -6]$
    
- $R_1$: $[1, -5+5, 2+0, -2+5] \rightarrow [1, 0, 2, 3]$
    

$$\begin{bmatrix} 1 & 0 & 2 & 3 \\ 0 & 1 & 0 & 1 \\ 0 & 0 & 2 & 2 \\ 0 & 0 & -6 & -6 \end{bmatrix}$$

### **Step 5: Normalize and Clear Column 3**

First, turn the pivot in Row 3 into a **1**.

- **Operation:** $R_3 \leftarrow R_3 / 2$
    

$$\begin{bmatrix} 1 & 0 & 2 & 3 \\ 0 & 1 & 0 & 1 \\ 0 & 0 & \mathbf{1} & 1 \\ 0 & 0 & -6 & -6 \end{bmatrix}$$

Now, eliminate the entries below ($-6$) and above ($2$).

- $R_4 \leftarrow R_4 + 6R_3$    
- $R_1 \leftarrow R_1 - 2R_3$    

**Calculations:**

- $R_4$: $[0, 0, -6+6, -6+6] \rightarrow [0, 0, 0, 0]$    
- $R_1$: $[1, 0, 2-2, 3-2] \rightarrow [1, 0, 0, 1]$
    

---

### **Final Reduced Row Echelon Form (RREF)**

$$R = \begin{bmatrix} 1 & 0 & 0 & 1 \\ 0 & 1 & 0 & 1 \\ 0 & 0 & 1 & 1 \\ 0 & 0 & 0 & 0 \end{bmatrix}$$

This matches the solution provided in the image.