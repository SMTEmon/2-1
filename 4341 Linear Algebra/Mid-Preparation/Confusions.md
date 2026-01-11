
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
### Example 2: 
#### **(a) False: $A$ and $A^T$ have the same nullspace.**

Why it's false:

The nullspace of $A$ consists of vectors $x$ such that $Ax=0$. The nullspace of $A^T$ consists of vectors $y$ such that $A^T y = 0$.

1. **Dimensions:** If $A$ is $m \times n$ (rectangular), the nullspace of $A$ is in $\mathbb{R}^n$, while the nullspace of $A^T$ is in $\mathbb{R}^m$. They live in completely different dimensions, so they cannot be the same.
    
2. **Direction:** Even if the matrix is square ($n \times n$), the nullspaces usually point in different directions unless the matrix is symmetric ($A = A^T$).
    

Counterexample:

Let $A = \begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix}$.

- Nullspace of $A$:
    
    Solve $\begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix} \begin{bmatrix} x_1 \\ x_2 \end{bmatrix} = \begin{bmatrix} 0 \\ 0 \end{bmatrix}$.
    
    This gives $x_2 = 0$. The vector is $\begin{bmatrix} 1 \\ 0 \end{bmatrix}$ (the x-axis).
    
- Nullspace of $A^T$:
    
    $A^T = \begin{bmatrix} 0 & 0 \\ 1 & 0 \end{bmatrix}$.
    
    Solve $\begin{bmatrix} 0 & 0 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} x_1 \\ x_2 \end{bmatrix} = \begin{bmatrix} 0 \\ 0 \end{bmatrix}$.
    
    This gives $x_1 = 0$. The vector is $\begin{bmatrix} 0 \\ 1 \end{bmatrix}$ (the y-axis).
    

**Conclusion:** The x-axis is not the y-axis. They are different.

---

#### **(b) False: $A$ and $A^T$ have the same free variables.**

Why it's false:

Free variables are determined by which columns do not have pivots. Transposing a matrix swaps rows and columns, which completely changes the pivot positions and the count of free variables.

Counterexample:

Let $A = \begin{bmatrix} 1 & 1 \end{bmatrix}$ (a $1 \times 2$ matrix).

- **For $A$:**
    
    - Pivot in Column 1.
        
    - **Free Variable:** $x_2$ (Column 2 has no pivot).
        
- **For $A^T$:**
    
    - $A^T = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$.
        
    - Pivot in Row 1, Column 1.
        
    - **Free Variables:** None. (There is only 1 column, and it has a pivot).
        

**Conclusion:** $A$ has 1 free variable, $A^T$ has 0.

---

#### **(c) False: If $R = \text{rref}(A)$, then $R^T = \text{rref}(A^T)$.**

Why it's false:

The Reduced Row Echelon Form (RREF) must have zeros below the pivots (creating an upper triangular shape). If you take the transpose of an upper triangular matrix, you get a lower triangular matrix, which violates the definition of RREF.
**Counterexample:**
Let's use the same matrix $A = \begin{bmatrix} 1 & 1 \end{bmatrix}$.

1. Find $R$:    
    The matrix is already in reduced form. $R = \begin{bmatrix} 1 & 1 \end{bmatrix}$.
        
2. Find $R^T$:    
    $$R^T = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$$    
    Is this the RREF of $A^T$? No.    
    - Row 2 of this matrix is $\begin{bmatrix} 1 \end{bmatrix}$.        
    - To be in RREF, we would need to eliminate that 1 using the row above it.
        
3. Actual $\text{rref}(A^T)$:
    
    Start with $A^T = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$.    
    Subtract Row 1 from Row 2: $\begin{bmatrix} 1 \\ 0 \end{bmatrix}$.
    

**Conclusion:** $R^T = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$ is not the same as $\text{rref}(A^T) = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$.

### Example 3:

If N(A) = all multiples of x = (2, 1, 0, 1), what is R and what is its rank?
#### **Part 1: Finding the Rank**

The key to solving this is the Rank-Nullity Theorem (also called the Counting Theorem).

$$\text{Rank} + \text{Nullity} = n$$

1. Find $n$ (Total Columns):

Look at the vector given in the nullspace: $x = (2, 1, 0, 1)$.

Since the vector has 4 components, the matrix must have 4 columns.

$$n = 4$$

2. Find the Nullity (Dimension of Nullspace):

The problem states the nullspace is "all multiples of $x$".

- "All multiples of **one** vector" describes a **line**.
    
- A line is **1-dimensional**.
    
- Therefore, the **Nullity is 1**. (This also means there is exactly **1 free variable**).
    

3. Calculate the Rank:

Using the theorem:

$$\text{Rank} + 1 = 4$$

$$\text{Rank} = 3$$

---

#### **Part 2: Finding Matrix $R$**

Since the Rank is 3, the Reduced Row Echelon Form ($R$) must have **3 Pivot Columns** (columns from the Identity Matrix) and **1 Free Column**.

Step 1: Assign Columns

Usually, the free variable corresponds to the last non-zero entry in the nullspace vector. In $x = (2, 1, 0, \mathbf{1})$, the last component corresponds to column 4.

- **Free Column:** Column 4.
    
- **Pivot Columns:** Columns 1, 2, and 3.
    

This sets up the "Identity" skeleton of our matrix:

$$R = \begin{bmatrix} \mathbf{1} & 0 & 0 & ? \\ 0 & \mathbf{1} & 0 & ? \\ 0 & 0 & \mathbf{1} & ? \end{bmatrix}$$

Step 2: Calculate the Missing Column

We know that $R x = 0$. Let's plug in our vector $x = (2, 1, 0, 1)$ and solve for the missing column (let's call the unknowns $a, b, c$).

$$\begin{bmatrix} 1 & 0 & 0 & a \\ 0 & 1 & 0 & b \\ 0 & 0 & 1 & c \end{bmatrix} \begin{bmatrix} 2 \\ 1 \\ 0 \\ 1 \end{bmatrix} = \begin{bmatrix} 0 \\ 0 \\ 0 \end{bmatrix}$$

This creates three simple equations:

1. **(Row 1):** $1(2) + 0(1) + 0(0) + a(1) = 0 \implies 2 + a = 0 \implies \mathbf{a = -2}$
    
2. **(Row 2):** $0(2) + 1(1) + 0(0) + b(1) = 0 \implies 1 + b = 0 \implies \mathbf{b = -1}$
    
3. **(Row 3):** $0(2) + 0(1) + 1(0) + c(1) = 0 \implies 0 + c = 0 \implies \mathbf{c = 0}$
    

**The Final Matrix $R$:**

$$R = \begin{bmatrix} 1 & 0 & 0 & \mathbf{-2} \\ 0 & 1 & 0 & \mathbf{-1} \\ 0 & 0 & 1 & \mathbf{0} \end{bmatrix}$$

**Summary:**

- **Rank:** 3
    
- **Matrix $R$:** The $3 \times 4$ matrix shown above.

## Transformation

### Example 1

Let T : R3 → R3 be the linear transformation defined by $$T([x1, x2, x3]) = [2x1 + 3x2, x3, 4x1 − 2x2]$$. Find the standard matrix representation of T. Is T invertible? If so, find a formula for $T ^ {-1}$
### Solution: 
The standard matrix representation of $T$ is $A = \begin{bmatrix} 2 & 3 & 0 \\ 0 & 0 & 1 \\ 4 & -2 & 0 \end{bmatrix}$.

$A^{-1} = \begin{bmatrix} 1/8 & 0 & 3/16 \\ 1/4 & 0 & -1/8 \\ 0 & 1 & 0 \end{bmatrix}$. Since $A$ is invertible, $T$ is invertible. $$T^{-1}([x_1, x_2, x_3]) = [\frac{1}{8}x_1 + \frac{3}{16}x_3, \frac{1}{4}x_1 - \frac{1}{8}x_3, x_2]$$
### Example 2 
