# Matrix Operations: A Deeper Look

**Context:** Supplements Lecture 2 (Elimination). Focuses on interpreting elementary matrices and the order of multiplication.

[[2. Elimination with Matrices]]

---

## 1. Decoding Elementary Matrix Coordinates
When looking at an Elementary Matrix (a matrix close to the Identity $I$), the position of any non-zero, non-diagonal number tells you exactly what operation it performs.

For a value $x$ located at **Row $i$, Column $j$**:
*   **Row $i$ (Target):** The row that is being modified.
*   **Column $j$ (Source):** The row being used to modify the target.

### Example: The "Subtract 2" Matrix
$$ E_{32} = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & \mathbf{-2} & 1 \end{bmatrix} $$

*   **Location:** Row 3, Column 2.
*   **Translation:** "Change **Row 3** using **Row 2**."
*   **Operation:** Subtract $2 \times (\text{Row } 2)$ from Row 3.
*   **Equation:** $\text{Row}_3 = \text{Row}_3 - 2(\text{Row}_2)$.

### Visual Comparison Table
Changing the position of the multiplier changes the entire operation.

| Matrix with $-2$ at... | Position | Instruction | Equation |
| :--- | :--- | :--- | :--- |
| $\begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & \mathbf{-2} & 1 \end{bmatrix}$ | **Row 3, Col 2** | Change Row 3 using Row 2 | $R_3 = R_3 - 2(R_2)$ |
| $\begin{bmatrix} 1 & 0 & 0 \\ \mathbf{-2} & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}$ | **Row 2, Col 1** | Change Row 2 using Row 1 | $R_2 = R_2 - 2(R_1)$ |
| $\begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ \mathbf{-2} & 0 & 1 \end{bmatrix}$ | **Row 3, Col 1** | Change Row 3 using Row 1 | $R_3 = R_3 - 2(R_1)$ |

---

## 2. The Golden Rule: $EA$ vs $AE$
Matrix multiplication is **not commutative** ($AB \neq BA$). The side on which you multiply an elementary matrix ($E$) determines whether you are manipulating rows or columns.

| Operation | Multiplication | Effect | Mnemonic |
| :--- | :--- | :--- | :--- |
| **Row Operation** | $E \times A$ | Modifies the **Rows** of $A$ | **Pre**-multiply for Rows |
| **Column Operation** | $A \times E$ | Modifies the **Columns** of $A$ | **Post**-multiply for Columns |

*   **$EA$ (Left Multiplication):**
    *   This takes linear combinations of **rows**.
    *   This is what we use for Gaussian Elimination (solving systems of equations).
*   **$AE$ (Right Multiplication):**
    *   This takes linear combinations of **columns**.
    *   This is less common in standard elimination but fundamental in other factorizations.
