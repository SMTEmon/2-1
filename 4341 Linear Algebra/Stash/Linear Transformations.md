## 1. What is a Linear Transformation?

A **Linear Transformation** $T$ is a function that maps a vector space to another (or to itself), preserving linear combinations. Geometrically, this means:
*   **Lines remain lines.**
*   **The origin remains fixed.**
*   **Grid lines remain parallel and evenly spaced.**

For any vectors $v, w$ and scalar $c$:
1.  $T(v + w) = T(v) + T(w)$ (Additivity)
2.  $T(cv) = cT(v)$ (Homogeneity)

---

## 2. How to Transform (The Operation)

In finite dimensions, every linear transformation can be represented by a **matrix**. To "transform" a vector $x$, you simply multiply it by the transformation matrix $A$.

$$ T(x) = Ax $$

**Example:**
If $A$ transforms $\mathbb{R}^2 \to \mathbb{R}^2$:
$$ \begin{bmatrix} a & b \\ c & d \end{bmatrix} \begin{bmatrix} x \\ y \end{bmatrix} = \begin{bmatrix} ax + by \\ cx + dy \end{bmatrix} $$

---

## 3. How to Find the "Transformer" (The Matrix)

The key insight to finding the matrix $A$ representing a transformation $T$ is to watch where the **basis vectors** go.

Let standard basis vectors be:
$$ \hat{i} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}, \quad \hat{j} = \begin{bmatrix} 0 \\ 1 \end{bmatrix} $$

The columns of matrix $A$ are simply the images of these basis vectors:
$$ A = \begin{bmatrix} | & | \\ T(\hat{i}) & T(\hat{j}) \\ | & | \end{bmatrix} $$

**Recipe:**
1.  Apply the transformation to $\hat{i}$ (input $\begin{bmatrix}1\\0\end{bmatrix}$). The result is Column 1.
2.  Apply the transformation to $\hat{j}$ (input $\begin{bmatrix}0\\1\end{bmatrix}$). The result is Column 2.

---

## 4. Visual Example: 90 Degree Rotation

Let's find the matrix for rotating a vector by $90^°$ counter-clockwise.

**Visualizing the Basis Vectors:**

1.  **Original:**
    *   $\hat{i}$ points Right $\rightarrow$ $(1, 0)$
    *   $\hat{j}$ points Up $\uparrow$ $(0, 1)$

2.  **Transformed ($90^°$ turn):**
    *   Where does $\hat{i}$ go? It now points Up.
        $$ T(\hat{i}) = \begin{bmatrix} 0 \\ 1 \end{bmatrix} $$
    *   Where does $\hat{j}$ go? It now points Left.
        $$ T(\hat{j}) = \begin{bmatrix} -1 \\ 0 \end{bmatrix} $$

**Constructing the Matrix:**
$$ A = \begin{bmatrix} 0 & -1 \\ 1 & 0 \end{bmatrix} $$

**Testing (How to Transform):**
Let's rotate the vector $v = \begin{bmatrix} 2 \\ 1 \end{bmatrix}$.
$$ Av = \begin{bmatrix} 0 & -1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} 2 \\ 1 \end{bmatrix} = \begin{bmatrix} (0)(2) + (-1)(1) \\ (1)(2) + (0)(1) \end{bmatrix} = \begin{bmatrix} -1 \\ 2 \end{bmatrix} $$

Visually, $(2, 1)$ (Right 2, Up 1) becomes $(-1, 2)$ (Left 1, Up 2), which is exactly a $90^°$ rotation.

---

## 5. Another Example: Shear

A "Shear" pushes the top of the box sideways while the bottom stays fixed.

1.  $\\hat{i} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$ stays fixed $\to \begin{bmatrix} 1 \\ 0 \end{bmatrix}$.
2.  $\hat{j} = \begin{bmatrix} 0 \\ 1 \end{bmatrix}$ leans right $\to \begin{bmatrix} 1 \\ 1 \end{bmatrix}$.

**Matrix:**
$$ A = \begin{bmatrix} 1 & 1 \\ 0 & 1 \end{bmatrix} $$

---

## 6. Finding A from Arbitrary Vectors

What if you are given **arbitrary vectors** and their transformed versions, rather than the standard basis vectors?

**The Rule:** To uniquely determine the matrix $A$ in $n$ dimensions, you need $n$ **linearly independent** input vectors and their outputs.

**Method:**
If you know that $T(v_1) = w_1$ and $T(v_2) = w_2$:
1.  Form the **Input Matrix** $V = \begin{bmatrix} v_1 & v_2 \end{bmatrix}$.
2.  Form the **Output Matrix** $W = \begin{bmatrix} w_1 & w_2 \end{bmatrix}$.
3.  The relationship is $AV = W$.
4.  Solve for $A$ by multiplying by the inverse of $V$:
    $$ A = W V^{-1} $$

**Example:**
Find the matrix $T$ that maps $\begin{bmatrix}1\\1\end{bmatrix} \to \begin{bmatrix}2\\0\end{bmatrix}$ and $\begin{bmatrix}0\\1\end{bmatrix} \to \begin{bmatrix}1\\1\end{bmatrix}$.

1.  Identify $V$ and $W$:
    $$ V = \begin{bmatrix} 1 & 0 \\ 1 & 1 \end{bmatrix}, \quad W = \begin{bmatrix} 2 & 1 \\ 0 & 1 \end{bmatrix} $$

2.  Find $V^{-1}$:
    $$ \det(V) = (1)(1) - (0)(1) = 1 $$
    $$ V^{-1} = \frac{1}{1} \begin{bmatrix} 1 & 0 \\ -1 & 1 \end{bmatrix} = \begin{bmatrix} 1 & 0 \\ -1 & 1 \end{bmatrix} $$

3.  Calculate $A = W V^{-1}$:
    $$ A = \begin{bmatrix} 2 & 1 \\ 0 & 1 \end{bmatrix} \begin{bmatrix} 1 & 0 \\ -1 & 1 \end{bmatrix} = \begin{bmatrix} (2)(1)+(1)(-1) & (2)(0)+(1)(1) \\ (0)(1)+(1)(-1) & (0)(0)+(1)(1) \end{bmatrix} $$
    $$ A = \begin{bmatrix} 1 & 1 \\ -1 & 1 \end{bmatrix} $$

**Check:**
*   $A \begin{bmatrix}1\\1\end{bmatrix} = \begin{bmatrix} 1(1)+1(1) \\ -1(1)+1(1) \end{bmatrix} = \begin{bmatrix} 2 \\ 0 \end{bmatrix}$ ✅
*   $A \begin{bmatrix}0\\1\end{bmatrix} = \begin{bmatrix} 1(0)+1(1) \\ -1(0)+1(1) \end{bmatrix} = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$ ✅
