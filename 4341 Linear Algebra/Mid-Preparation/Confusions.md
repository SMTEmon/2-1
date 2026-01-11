
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

### **Step 1: Identify the RREF**

The problem asks to start by finding the Reduced Row Echelon Form (RREF). The solution in the image provides this for us:

$$\text{rref}(A) = R = \begin{bmatrix} \mathbf{1} & 0 & 0 & 1 \\ 0 & \mathbf{1} & 0 & 1 \\ 0 & 0 & \mathbf{1} & 1 \\ 0 & 0 & 0 & 0 \end{bmatrix}$$

From this matrix $R$, we can identify the key variables:

- **Pivot Columns:** Columns 1, 2, and 3 (columns with the leading 1s).
    
- **Free Column:** Column 4 (no leading 1).
    

---

### **Step 2: Basis for the Row Space**

The basis for the row space is simply the **non-zero rows of the RREF matrix**. These rows are linearly independent and span the same space as the original rows.

**Basis vectors:**

$$\left\{ \begin{bmatrix} 1 \\ 0 \\ 0 \\ 1 \end{bmatrix}, \begin{bmatrix} 0 \\ 1 \\ 0 \\ 1 \end{bmatrix}, \begin{bmatrix} 0 \\ 0 \\ 1 \\ 1 \end{bmatrix} \right\}$$

---

### **Step 3: Basis for the Column Space**

The basis for the column space consists of the **pivot columns from the original matrix $A$** (not the RREF matrix). Since columns 1, 2, and 3 are the pivot columns in $R$, we pick columns 1, 2, and 3 from $A$.

$$A = \begin{bmatrix} \mathbf{3} & \mathbf{4} & \mathbf{0} & 7 \\ \mathbf{1} & \mathbf{-5} & \mathbf{2} & -2 \\ \mathbf{-1} & \mathbf{4} & \mathbf{0} & 3 \\ \mathbf{1} & \mathbf{-1} & \mathbf{2} & 2 \end{bmatrix}$$

**Basis vectors:**

$$\left\{ \begin{bmatrix} 3 \\ 1 \\ -1 \\ 1 \end{bmatrix}, \begin{bmatrix} 4 \\ -5 \\ 4 \\ -1 \end{bmatrix}, \begin{bmatrix} 0 \\ 2 \\ 0 \\ 2 \end{bmatrix} \right\}$$

---

### **Step 4: Basis for the Null Space**

To find the null space, we solve $Ax = 0$ (or $Rx = 0$). We write the equations from the non-zero rows of the RREF and solve for the pivot variables in terms of the free variable ($x_4$).

1. **Equations from RREF:**
    
    - $x_1 + 1x_4 = 0 \implies x_1 = -x_4$
        
    - $x_2 + 1x_4 = 0 \implies x_2 = -x_4$
        
    - $x_3 + 1x_4 = 0 \implies x_3 = -x_4$
        
2. Form the vector:
    
    Let the free variable $x_4 = 1$.
    
    $$x = \begin{bmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{bmatrix} = \begin{bmatrix} -1 \\ -1 \\ -1 \\ 1 \end{bmatrix}$$
    

**Basis vector:**

$$\left\{ \begin{bmatrix} -1 \\ -1 \\ -1 \\ 1 \end{bmatrix} \right\}$$