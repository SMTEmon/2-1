#LinearAlgebra #Matrices #SpectralTheorem #MIT1806

## 1. The Core Properties

For a **Real Symmetric Matrix** ($A = A^T$), two "miracles" always happen:

1. **Real Eigenvalues:** The eigenvalues ($\lambda$) are always real, never complex.
    
2. **Orthonormal Eigenvectors:** The eigenvectors ($q$) are naturally perpendicular. We can scale them to length 1, forming an **orthonormal matrix $Q$**.
    

> [!TIP] The $Q$ Advantage
> 
> Because $Q$ is orthonormal, its inverse is its transpose:
> 
> **$Q^{-1} = Q^T$**

---

## 2. The Great Factorization

The standard diagonalization $A = S\Lambda S^{-1}$ transforms into the **Spectral Theorem** for symmetric matrices:

$$\huge A = Q \Lambda Q^T$$

Where:

- **$Q$**: Matrix with orthonormal eigenvectors as columns.
    
- **$\Lambda$**: Diagonal matrix of real eigenvalues.
    
- **$Q^T$**: The transpose (which is the inverse).
    

---

## 3. The Column-Row Expansion

Instead of thinking of matrix multiplication as "Row $\times$ Column" (which results in a single number), Professor Strang views $A = Q\Lambda Q^T$ as a **sum of layers**.

### The Mathematical Breakdown

If $Q = [q_1, q_2, \dots, q_n]$, then:

$$A = \lambda_1 q_1 q_1^T + \lambda_2 q_2 q_2^T + \dots + \lambda_n q_n q_n^T$$

> [!ABSTRACT] Why it works: The Summation Formula
> 
> The fundamental rule for any matrix product $C = AB$ is:
> 
> $$C_{ij} = \sum_{k=1}^{n} A_{ik} B_{kj}$$
> 
> - **Row-Col View:** Fix $i$ and $j$, sum over $k \rightarrow$ Get one number.
>     
> - **Col-Row View:** Fix $k$, see the matrix produced $\rightarrow$ Get one "layer."
>     

---

## 4. Visual Example (2x2)

Let’s see how a matrix is "built" from these layers.

### Step 1: Standard Multiplication (Row $\times$ Col)

To get the top-left entry of $\begin{bmatrix} a & b \\ c & d \end{bmatrix} \begin{bmatrix} e & f \\ g & h \end{bmatrix}$:

$$\text{Row}_1 \cdot \text{Col}_1 = (a \cdot e) + (b \cdot g)$$

### Step 2: The Strang Way (Col $\times$ Row)

We treat the multiplication as the sum of two "mini-matrices":

**Layer 1 (Col 1 $\times$ Row 1):**

$$\begin{bmatrix} a \\ c \end{bmatrix} \begin{bmatrix} e & f \end{bmatrix} = \begin{bmatrix} ae & af \\ ce & cf \end{bmatrix}$$

**Layer 2 (Col 2 $\times$ Row 2):**

$$\begin{bmatrix} b \\ d \end{bmatrix} \begin{bmatrix} g & h \end{bmatrix} = \begin{bmatrix} bg & bh \\ dg & dh \end{bmatrix}$$

**Final Result (The Sum):**

$$\begin{bmatrix} ae & af \\ ce & cf \end{bmatrix} + \begin{bmatrix} bg & bh \\ dg & dh \end{bmatrix} = \begin{bmatrix} ae+bg & af+bh \\ ce+dg & cf+dh \end{bmatrix}$$

---

## 5. Physical Meaning: Projection Matrices

In the expansion $\lambda_1 q_1 q_1^T$, the term **$q_i q_i^T$** is a **Projection Matrix**.

> [!INFO] Geometric Interpretation
> 
> A symmetric matrix takes a vector, breaks it into components along its eigenvectors ($q_i$), and then multiplies (scales) each component by its eigenvalue ($\lambda_i$).
> 
> **$A$ is just a weighted sum of perpendicular projections.**

---

