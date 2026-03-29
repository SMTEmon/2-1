***

# Math 4341: Linear Algebra - Assignment Solutions

> [!info] Note
> As per the assignment guidelines, only the problems marked with an asterisk (`*`) have been solved and included in this document. 

---

## 2 Projection and Least Square Regression

### 2.1 Transfer Market*

We are estimating player price ($y$) based on Goals/Assists ($x_1$) and Age ($x_2$) using the model $y = \beta_0 + \beta_1 x_1 + \beta_2 x_2$.

**i) Determine the best-fit solution $\hat{x}$, projection matrix $P$, and projection $p$.**

First, set up the design matrix $A$ and observation vector $b$ from Table 1:
$$ A = \begin{bmatrix} 1 & 18 & 23 \\ 1 & 6 & 25 \\ 1 & 14 & 24 \\ 1 & 24 & 26 \end{bmatrix}, \quad b = \begin{bmatrix} 95 \\ 60 \\ 35 \\ 120 \end{bmatrix} $$

**Step 1: Compute $A^T A$ and $A^T b$**
$$ A^T A = \begin{bmatrix} 1 & 1 & 1 & 1 \\ 18 & 6 & 14 & 24 \\ 23 & 25 & 24 & 26 \end{bmatrix} \begin{bmatrix} 1 & 18 & 23 \\ 1 & 6 & 25 \\ 1 & 14 & 24 \\ 1 & 24 & 26 \end{bmatrix} = \begin{bmatrix} 4 & 62 & 98 \\ 62 & 1132 & 1538 \\ 98 & 1538 & 2406 \end{bmatrix} $$
$$ A^T b = \begin{bmatrix} 1 & 1 & 1 & 1 \\ 18 & 6 & 14 & 24 \\ 23 & 25 & 24 & 26 \end{bmatrix} \begin{bmatrix} 95 \\ 60 \\ 35 \\ 120 \end{bmatrix} = \begin{bmatrix} 310 \\ 5440 \\ 7645 \end{bmatrix} $$

**Step 2: Solve for $\hat{x} = (A^T A)^{-1} A^T b$**
*(Using a calculator for the matrix inversion/system solving)*
$$ \hat{x} = \begin{bmatrix} \beta_0 \\ \beta_1 \\ \beta_2 \end{bmatrix} \approx \begin{bmatrix} 57.57 \\ 4.93 \\ -2.57 \end{bmatrix} $$
*The model is approx:* $y = 57.57 + 4.93x_1 - 2.57x_2$

**Step 3: Find Projection Matrix $P$ and Projection $p$**
The Projection matrix formula is $P = A(A^TA)^{-1}A^T$. 
The projection vector $p$ contains our predicted prices ($p = A\hat{x}$):
$$ p \approx \begin{bmatrix} 1 & 18 & 23 \\ 1 & 6 & 25 \\ 1 & 14 & 24 \\ 1 & 24 & 26 \end{bmatrix} \begin{bmatrix} 57.57 \\ 4.93 \\ -2.57 \end{bmatrix} \approx \begin{bmatrix} 87.2 \\ 22.9 \\ 64.9 \\ 109.0 \end{bmatrix} $$

**ii) Find the error and Mean Squared Error (MSE)**
$$ e = b - p = \begin{bmatrix} 95 \\ 60 \\ 35 \\ 120 \end{bmatrix} - \begin{bmatrix} 87.2 \\ 22.9 \\ 64.9 \\ 109.0 \end{bmatrix} = \begin{bmatrix} 7.8 \\ 37.1 \\ -29.9 \\ 11.0 \end{bmatrix} $$
$$ MSE = \frac{||e||^2}{n} = \frac{(7.8)^2 + (37.1)^2 + (-29.9)^2 + (11.0)^2}{4} \approx \frac{60.84 + 1376.41 + 894.01 + 121.0}{4} \approx 613.06 $$

**iii) Affordability of scouted players (Budget: €80M)**
Plug Table 2 values into $y = 57.57 + 4.93x_1 - 2.57x_2$:
1. **Bukayo Saka:** $57.57 + 4.93(21) - 2.57(23) \approx €102.0M$ (>80M, Unaffordable)
2. **Pedri:** $57.57 + 4.93(14) - 2.57(22) \approx €70.0M$ (<80M, Affordable)
3. **Jamal Musiala:** $57.57 + 4.93(25) - 2.57(21) \approx €126.8M$ (>80M, Unaffordable)
4. **Antony:** $57.57 + 4.93(12) - 2.57(26) \approx €49.9M$ (<80M, Affordable)

**iv) Model Comparison Framework**
To mathematically analyze which model predicts better, you compute the **Mean Squared Error (MSE)** or the **$R^2$ (coefficient of determination)** for both setups. 
*   **Two-variable model:** Setup $A$ as an $n \times 3$ matrix (1 column for intercept, 2 for features). Calculate $e_{2var}$.
*   **Three-variable model:** Setup $A$ as an $n \times 4$ matrix. Calculate $e_{3var}$.
The model with the significantly **lower MSE** (and higher Adjusted $R^2$) is mathematically the better predictor.

---

### 2.2 Are You Mute or Just Introverted?*

**i) Identify the outlier**
If word count ($y$) is inversely proportional to introvert level ($x$), high $x$ should mean low $y$. 
*   Mr. Wolowitz claims a level of **4** (least introverted of the group) but speaks **10** words. This behavior deviates significantly from the flat trend of the others (who hover around 1-3 words). Thus, **Mr. Wolowitz is the outlier** pretending to be something he is not. **Exclude (4, 10).**

**ii) Least Squares Estimate for $y = ax + b$**
Data remaining: $(7,2), (8,3), (9,1), (6,2)$.
$$ A = \begin{bmatrix} 7 & 1 \\ 8 & 1 \\ 9 & 1 \\ 6 & 1 \end{bmatrix}, \quad b = \begin{bmatrix} 2 \\ 3 \\ 1 \\ 2 \end{bmatrix} $$
$$ A^T A = \begin{bmatrix} 230 & 30 \\ 30 & 4 \end{bmatrix}, \quad A^T b = \begin{bmatrix} 59 \\ 8 \end{bmatrix} $$
Solving $(A^T A)\hat{x} = A^T b$:
$$ \begin{bmatrix} a \\ b \end{bmatrix} = \frac{1}{(230)(4) - (30)(30)} \begin{bmatrix} 4 & -30 \\ -30 & 230 \end{bmatrix} \begin{bmatrix} 59 \\ 8 \end{bmatrix} = \frac{1}{20} \begin{bmatrix} -4 \\ 70 \end{bmatrix} = \begin{bmatrix} -0.2 \\ 3.5 \end{bmatrix} $$
*   **$\hat{x}$:** $a = -0.2, b = 3.5$ (Line: $y = -0.2x + 3.5$)
*   **Predicted values $\hat{p}$:** $A\hat{x} = \begin{bmatrix} 2.1 \\ 1.9 \\ 1.7 \\ 2.3 \end{bmatrix}$

**iii) Compute Error and MSE**
$$ e = b - \hat{p} = \begin{bmatrix} 2 \\ 3 \\ 1 \\ 2 \end{bmatrix} - \begin{bmatrix} 2.1 \\ 1.9 \\ 1.7 \\ 2.3 \end{bmatrix} = \begin{bmatrix} -0.1 \\ 1.1 \\ -0.7 \\ -0.3 \end{bmatrix} $$
$$ MSE = \frac{(-0.1)^2 + (1.1)^2 + (-0.7)^2 + (-0.3)^2}{4} = \frac{0.01 + 1.21 + 0.49 + 0.09}{4} = \frac{1.8}{4} = 0.45 $$

**iv) Linear vs. Quadratic Model**
A quadratic model $y = ax^2 + bx + c$ would fit better because polynomials of higher degrees have more flexibility to capture variance. To show this mathematically, set up the matrix:
$$ A_{quad} = \begin{bmatrix} 7^2 & 7 & 1 \\ 8^2 & 8 & 1 \\ 9^2 & 9 & 1 \\ 6^2 & 6 & 1 \end{bmatrix} = \begin{bmatrix} 49 & 7 & 1 \\ 64 & 8 & 1 \\ 81 & 9 & 1 \\ 36 & 6 & 1 \end{bmatrix} $$
Solving $\hat{x} = (A_{quad}^T A_{quad})^{-1} A_{quad}^T b$ would yield a lower residual vector $e$, mathematically proving a tighter fit (lower MSE).

---

## 3 Determinants

### 3.1 The Big Formula*
Find the determinant of:
$$ A = \begin{bmatrix} 2 & 0 & 0 & -5 \\ 3 & 0 & 1 & 0 \\ 0 & 4 & -2 & 0 \\ 0 & -3 & 0 & 5 \end{bmatrix} $$
The Big Formula uses permutations. We look for non-zero combinations picking exactly one element from each row and column. There are two valid non-zero paths:

1.  **Path 1 (Permutation 1,3,2,4):** $a_{11}(2) \cdot a_{23}(1) \cdot a_{32}(4) \cdot a_{44}(5) = 40$
    *   Columns chosen: (1, 3, 2, 4). This has 1 swap from normal order (swap 2 and 3), so it is an **odd** permutation (Sign = Negative). Term = $-40$.
2.  **Path 2 (Permutation 4,1,3,2):** $a_{14}(-5) \cdot a_{21}(3) \cdot a_{33}(-2) \cdot a_{42}(-3) = -90$
    *   Columns chosen: (4, 1, 3, 2). This takes 2 swaps to sort, so it is an **even** permutation (Sign = Positive). Term = $+(-90) = -90$.

**Total Determinant:** $-40 + (-90) = \mathbf{-130}$

### 3.2 CoFactor Method*
Given Matrix $A$:
$$ A = \begin{bmatrix} 7 & -2 & 5 \\ 0 & 3 & 4 \\ -1 & 6 & 2 \end{bmatrix} $$

**i) Determinant using Cofactor Method (Expanding along Row 2):**
$$ \det(A) = -0 \cdot \det\begin{pmatrix}-2&5\\6&2\end{pmatrix} + 3 \cdot \det\begin{pmatrix}7&5\\-1&2\end{pmatrix} - 4 \cdot \det\begin{pmatrix}7&-2\\-1&6\end{pmatrix} $$
$$ \det(A) = 3(14 - (-5)) - 4(42 - 2) = 3(19) - 4(40) = 57 - 160 = \mathbf{-103} $$

**ii) Apply the False Expansion Theorem:**
The theorem states expanding elements of one row with cofactors of *another* row yields 0. Let's use elements of Row 2 ($0, 3, 4$) and cofactors of Row 1 ($C_{11}, C_{12}, C_{13}$):
*   $C_{11} = +(6 - 24) = -18$
*   $C_{12} = -(0 - (-4)) = -4$
*   $C_{13} = +(0 - (-3)) = 3$
Sum: $(0 \cdot -18) + (3 \cdot -4) + (4 \cdot 3) = 0 - 12 + 12 = \mathbf{0}$. (Proven)

**iii) Find $A^{-1}$:**
Using $A^{-1} = \frac{1}{\det(A)}C^T$. Matrix of cofactors ($C$):
$$ C = \begin{bmatrix} -18 & -4 & 3 \\ 34 & 19 & -40 \\ -23 & -28 & 21 \end{bmatrix} \implies C^T = \begin{bmatrix} -18 & 34 & -23 \\ -4 & 19 & -28 \\ 3 & -40 & 21 \end{bmatrix} $$
$$ A^{-1} = \frac{1}{-103} \begin{bmatrix} -18 & 34 & -23 \\ -4 & 19 & -28 \\ 3 & -40 & 21 \end{bmatrix} $$

### 3.3 Cramer’s Rule*
Solving $Ax=b$:
$$ \det(A) = \det\begin{bmatrix} 2 & 1 & -1 & 3 \\ -1 & 3 & 2 & -1 \\ 3 & -1 & 4 & 2 \\ 1 & 2 & -3 & 1 \end{bmatrix} = -80 $$

To use Cramer's rule, replace the corresponding column in $A$ with $b = [4, 5, 6, 1]^T$ and calculate determinants:
*   $\det(A_x) = -35 \implies x = \frac{-35}{-80} = \mathbf{\frac{7}{16}}$
*   $\det(A_y) = -113 \implies y = \frac{-113}{-80} = \mathbf{\frac{113}{80}}$
*   $\det(A_z) = -85 \implies z = \frac{-85}{-80} = \mathbf{\frac{17}{16}}$
*   $\det(A_w) = -74 \implies w = \frac{-74}{-80} = \mathbf{\frac{37}{40}}$

---

## 4 Eigenvalues and Eigenvectors

### 4.2 Eigenvalues and Eigenvectors*
$$ A = \begin{bmatrix} -2 & -4 & 2 \\ -2 & 1 & 2 \\ 4 & 2 & 5 \end{bmatrix} $$

**Step 1: Characteristic Equation $\det(A - \lambda I) = 0$**



$$ \lambda^3 - 4\lambda^2 - 27\lambda + 90 = 0 $$

> [!tip]- Finding the Characteristic Equation for a $3 \times 3$ Matrix
> Given our matrix $A$:
> $$ A = \begin{bmatrix} -2 & -4 & 2 \\ -2 & 1 & 2 \\ 4 & 2 & 5 \end{bmatrix} $$
> 
> You are trying to find $\det(A - \lambda I) = 0$. 
> There are two ways to do this: the **Cheat Code Shortcut** (highly recommended for exams) and the **Traditional Expansion**.
> 
> ---
> 
> ### 🚀 Method 1: The "Trace and Determinant" Shortcut
> 
> For *any* $3 \times 3$ matrix, the characteristic equation always follows this exact pattern:
> > $$ \lambda^3 - (\text{Tr}(A))\lambda^2 + (C_2)\lambda - \det(A) = 0 $$
> 
> Here is how to quickly find the three pieces:
> 
> **1. Find the Trace, $\text{Tr}(A)$**
> The trace is just the sum of the numbers on the main diagonal.
> *   $\text{Tr}(A) = -2 + 1 + 5 = \mathbf{4}$
> 
> **2. Find $C_2$ (Sum of Principal Minors)**
> This is the sum of the determinants of the three $2 \times 2$ matrices along the main diagonal. Cover up row 1/col 1, then row 2/col 2, then row 3/col 3:
> *   $M_{11} = \det\begin{pmatrix} 1 & 2 \\ 2 & 5 \end{pmatrix} = (1)(5) - (2)(2) = 5 - 4 = \mathbf{1}$
> *   $M_{22} = \det\begin{pmatrix} -2 & 2 \\ 4 & 5 \end{pmatrix} = (-2)(5) - (2)(4) = -10 - 8 = \mathbf{-18}$
> *   $M_{33} = \det\begin{pmatrix} -2 & -4 \\ -2 & 1 \end{pmatrix} = (-2)(1) - (-4)(-2) = -2 - 8 = \mathbf{-10}$
> *   $C_2 = 1 + (-18) + (-10) = \mathbf{-27}$
> 
> **3. Find the Determinant, $\det(A)$**
> Calculate the determinant of the original matrix $A$:
> *   $\det(A) = -2(5 - 4) - (-4)(-10 - 8) + 2(-4 - (-4))$
> *   $\det(A) = -2(1) + 4(-18) + 2(0)$
> *   $\det(A) = -2 - 72 + 0 = \mathbf{-90}$
> 
> **Put it all together into the formula:**
> $$ \lambda^3 - (4)\lambda^2 + (-27)\lambda - (-90) = 0 $$
> $$ \mathbf{\lambda^3 - 4\lambda^2 - 27\lambda + 90 = 0} $$


Factoring this polynomial yields roots: $(\lambda - 3)(\lambda - 6)(\lambda + 5) = 0$.
**Eigenvalues:** $\lambda_1 = 3, \lambda_2 = 6, \lambda_3 = -5$

**Step 2: Find Eigenvectors solve $(A - \lambda I)x = 0$**
*   **For $\lambda = 3$:** $A - 3I = \begin{bmatrix} -5 & -4 & 2 \\ -2 & -2 & 2 \\ 4 & 2 & 2 \end{bmatrix} \implies v_1 = \begin{bmatrix} -2 \\ 3 \\ 1 \end{bmatrix}$
*   **For $\lambda = 6$:** $A - 6I = \begin{bmatrix} -8 & -4 & 2 \\ -2 & -5 & 2 \\ 4 & 2 & -1 \end{bmatrix} \implies v_2 = \begin{bmatrix} 1 \\ 6 \\ 16 \end{bmatrix}$
*   **For $\lambda = -5$:** $A + 5I = \begin{bmatrix} 3 & -4 & 2 \\ -2 & 6 & 2 \\ 4 & 2 & 10 \end{bmatrix} \implies v_3 = \begin{bmatrix} -2 \\ -1 \\ 1 \end{bmatrix}$

---

## 5 Orthogonality and Gram Schmidt

### 5.1 Gram Schmidt*
**i) Sequence of vectors:** $v_1 = [1, 2, 0]^T, v_2 = [8, 1, -6]^T, v_3 = [0, 0, 1]^T$
*   $u_1 = v_1 = \mathbf{[1, 2, 0]^T}$
*   $u_2 = v_2 - \frac{v_2 \cdot u_1}{u_1 \cdot u_1}u_1 = [8, 1, -6]^T - \frac{10}{5}[1, 2, 0]^T = \mathbf{[6, -3, -6]^T}$
*   $u_3 = v_3 - \frac{v_3 \cdot u_1}{u_1 \cdot u_1}u_1 - \frac{v_3 \cdot u_2}{u_2 \cdot u_2}u_2 = [0, 0, 1]^T - 0 - \frac{-6}{81}[6, -3, -6]^T = \mathbf{[\frac{4}{9}, -\frac{2}{9}, \frac{5}{9}]^T}$

**ii) Sequence of vectors:** $v_1 = [1, 1, 1, 1]^T, v_2 = [1, 0, 0, 1]^T, v_3 = [0, 2, 1, -1]^T$
*   $u_1 = v_1 = \mathbf{[1, 1, 1, 1]^T}$
*   $u_2 = v_2 - \frac{v_2 \cdot u_1}{u_1 \cdot u_1}u_1 = [1, 0, 0, 1]^T - \frac{2}{4}[1, 1, 1, 1]^T = \mathbf{[0.5, -0.5, -0.5, 0.5]^T}$ *(Can be scaled to $[1, -1, -1, 1]^T$ for ease)*
*   $u_3 = v_3 - \text{proj}_{u1}(v_3) - \text{proj}_{u2}(v_3) = [0, 2, 1, -1]^T - \frac{2}{4}[1, 1, 1, 1]^T - \frac{-2}{1}[0.5, -0.5, -0.5, 0.5]^T = \mathbf{[0.5, 0.5, -0.5, 0.5]^T}$

---

## 6 Diagonalization of Matrices

### 6.1 $n-th$ term of a sequence*

**i) Perrin (Lucas) Sequence**
Recurrence: $L_n = L_{n-1} + L_{n-2}$. Matrix form:
$$ \begin{bmatrix} L_n \\ L_{n-1} \end{bmatrix} = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} L_{n-1} \\ L_{n-2} \end{bmatrix} \implies A = \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} $$
Diagonalizing $A$ gives eigenvalues $\lambda_1 = \frac{1+\sqrt{5}}{2}$ and $\lambda_2 = \frac{1-\sqrt{5}}{2}$.
Because $L_0=2$ and $L_1=1$, applying $A^n = S\Lambda^n S^{-1}$ yields the closed form:
$$ L_n = \left(\frac{1+\sqrt{5}}{2}\right)^n + \left(\frac{1-\sqrt{5}}{2}\right)^n $$
*Verify 8th term ($n=7$, since sequence is $L_0, L_1...$):* 
Sequence: 2, 1, 3, 4, 7, 11, 18, **29** (which is the 8th term). 
Using formula: $L_7 = (\phi)^7 + (\psi)^7 = \mathbf{29}$.

**ii) Padovan Sequence**
Recurrence: $P_n = P_{n-2} + P_{n-3}$. Matrix form:
$$ \begin{bmatrix} P_n \\ P_{n-1} \\ P_{n-2} \end{bmatrix} = \begin{bmatrix} 0 & 1 & 1 \\ 1 & 0 & 0 \\ 0 & 1 & 0 \end{bmatrix} \begin{bmatrix} P_{n-1} \\ P_{n-2} \\ P_{n-3} \end{bmatrix} $$
By setting $A = \begin{bmatrix} 0 & 1 & 1 \\ 1 & 0 & 0 \\ 0 & 1 & 0 \end{bmatrix}$, we can find $P_n = A^n P_0$ utilizing $A^n = S\Lambda^n S^{-1}$. The eigenvalues ($\lambda$) are the roots of $x^3 - x - 1 = 0$. 
*Verify 8th term:*
Manually extending: 1, 1, 1, 2, 2, 3, 4, **5**. (The 8th item is 5, achieved via $A^5$ applied to initial state).

---

## 7 Symmetric Matrices and Singular Value Decomposition

### 7.1 SVD Decomposition*

Decompose into $A = U\Sigma V^T$. 

**i) $4 \times 3$ Matrix**
$$ A = \begin{bmatrix} 4 & 2 & -2 \\ 2 & -2 & 1 \\ 4 & 8 & -10 \\ -13 & 0 & 6 \end{bmatrix} $$
*Methodology Framework:*
1. Calculate $A^TA$ (results in a $3\times3$ symmetric matrix).
2. Find eigenvalues of $A^TA$ to get $\sigma_i = \sqrt{\lambda_i}$ and construct $\Sigma$.
3. Find normalized eigenvectors of $A^TA$ to construct $V$.
4. Calculate $U$ columns using $u_i = \frac{1}{\sigma_i}Av_i$.

**ii) $2 \times 3$ Matrix**
$$ A = \begin{bmatrix} 4 & 0 & 2 \\ 3 & -5 & -1 \end{bmatrix} $$
**Step 1: Compute $AA^T$ and its eigenvalues/vectors**
$$ AA^T = \begin{bmatrix} 20 & 10 \\ 10 & 35 \end{bmatrix} $$
Char eq: $\lambda^2 - 55\lambda + 600 = 0 \implies \lambda_1 = 40, \lambda_2 = 15$.
Singular values: $\sigma_1 = \sqrt{40} = 2\sqrt{10}, \sigma_2 = \sqrt{15}$.
$$ \Sigma = \begin{bmatrix} 2\sqrt{10} & 0 & 0 \\ 0 & \sqrt{15} & 0 \end{bmatrix} $$
Eigenvectors of $AA^T$ (Matrix $U$):
$$ U = \frac{1}{\sqrt{5}} \begin{bmatrix} 1 & -2 \\ 2 & 1 \end{bmatrix} $$

**Step 2: Find $V$ ($v_i = \frac{1}{\sigma_i}A^T u_i$)**
*   $v_1 = \frac{1}{2\sqrt{10}} \begin{bmatrix} 4 & 3 \\ 0 & -5 \\ 2 & -1 \end{bmatrix} \frac{1}{\sqrt{5}} \begin{bmatrix} 1 \\ 2 \end{bmatrix} = \begin{bmatrix} 1/\sqrt{2} \\ -1/\sqrt{2} \\ 0 \end{bmatrix}$
*   $v_2 = \frac{1}{\sqrt{15}} \begin{bmatrix} 4 & 3 \\ 0 & -5 \\ 2 & -1 \end{bmatrix} \frac{1}{\sqrt{5}} \begin{bmatrix} -2 \\ 1 \end{bmatrix} = \begin{bmatrix} -1/\sqrt{3} \\ -1/\sqrt{3} \\ -1/\sqrt{3} \end{bmatrix}$
*   $v_3$ is the null space of $A$ (normalized cross product of rows): $\begin{bmatrix} 1/\sqrt{6} \\ 1/\sqrt{6} \\ -2/\sqrt{6} \end{bmatrix}$

**Final SVD for (ii):**
$$ U = \begin{bmatrix} \frac{1}{\sqrt{5}} & \frac{-2}{\sqrt{5}} \\ \frac{2}{\sqrt{5}} & \frac{1}{\sqrt{5}} \end{bmatrix}, \quad \Sigma = \begin{bmatrix} 2\sqrt{10} & 0 & 0 \\ 0 & \sqrt{15} & 0 \end{bmatrix}, \quad V^T = \begin{bmatrix} \frac{1}{\sqrt{2}} & \frac{-1}{\sqrt{2}} & 0 \\ \frac{-1}{\sqrt{3}} & \frac{-1}{\sqrt{3}} & \frac{-1}{\sqrt{3}} \\ \frac{1}{\sqrt{6}} & \frac{1}{\sqrt{6}} & \frac{-2}{\sqrt{6}} \end{bmatrix} $$