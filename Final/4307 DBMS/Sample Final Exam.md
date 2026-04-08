***

# 📝 Sample Final Exam: Database Management Systems (CSE 4307)
**Total Marks:** 120
**Time constraint:** 2.5 - 3 Hours
**Instructions:** Keep answers short and keyword-focused. Skip and return to difficult questions if needed.

---

## 📌 Question 1: Advanced SQL & Programming (30 Marks)
*Focus: Chapter 5 (Coding, PL/pgSQL, JDBC, OLAP)*

**1a. Database Security & JDBC (6 Marks)**
A junior developer wrote the following Java JDBC code to retrieve a user's profile:
```java
String query = "SELECT * FROM users WHERE username = '" + userInput + "'";
Statement stmt = conn.createStatement();
ResultSet rs = stmt.executeQuery(query);
```
1. Identify the critical security vulnerability in this code. *(2 marks)*
2. What specific input (`userInput`) could an attacker provide to bypass the authentication and access all data? *(2 marks)*
3. Write the corrected line(s) of Java code to fix this vulnerability. *(2 marks)*

**1b. PL/pgSQL Triggers (12 Marks)**
You have two tables: `employee(emp_id, name, salary, dept_id)` and `department(dept_id, dept_name, total_salary_expense)`.
Write a **Row-Level Trigger** (both the function and the trigger definition) in PostgreSQL that automatically updates the `total_salary_expense` in the `department` table whenever an employee receives a salary increase (an `UPDATE` operation). 

**1c. Advanced Aggregation (OLAP) (7 Marks)**
Given a table `sales(date, item, revenue)`:
Write a single SQL query using **Window Functions** to calculate the **Running Total** of `revenue` for each individual `item`, ordered by `date`.

**1d. Recursive Queries (5 Marks)**
According to the slides, a recursive query (using `WITH RECURSIVE`) consists of two structural components combined by a `UNION`. Name these two components and briefly state the stop condition for the recursion (when does it terminate?).

---

## 📌 Question 2: Database Design & Closures (30 Marks)
*Focus: Chapter 7 Part 1 (FDs, Armstrong's Axioms, Candidate Keys)*

**Scenario for Q2:**
You are given a relation schema $R(A, B, C, D, E)$ and the following set of Functional Dependencies ($F$):
1. $A \rightarrow B$
2. $B \rightarrow C$
3. $C \rightarrow D$
4. $D \rightarrow E$

**2a. Attribute Closure (10 Marks)**
Calculate the attribute closure of $\{A\}^+$ step-by-step using Armstrong's Axioms. State which rule (e.g., Reflexivity, Transitivity, Union) you are applying at each step.

**2b. Finding Candidate Keys using Method 3 (10 Marks)**
Using **Method 3 (The Optimized Approach / Basket Algorithm)** from the lectures:
1. Perform **Phase 1 (The Discard Process)** to find the initial Candidate Key. Show the discarded attributes.
2. Perform **Phase 2 (The Replacement Process)** to check if alternative keys exist. List the *Prime Attributes*, *Dependent Attributes*, and their intersection. Does an alternative key exist?

**2c. Lossless Decomposition (10 Marks)**
Suppose we decompose relation $R(A, B, C, D, E)$ into two relations: $R_1(A, B, C)$ and $R_2(C, D, E)$.
Using the mathematical condition for Lossless Decomposition ($R_1 \cap R_2 \rightarrow R_1$ OR $R_1 \cap R_2 \rightarrow R_2$), prove whether this decomposition is **Lossy** or **Lossless**.

---

## 📌 Question 3: Normalization Verifications (30 Marks)
*Focus: Chapter 7 Part 2 (1NF, 2NF, 3NF, BCNF)*

**3a. 1NF and 2NF (10 Marks)**
Consider the following table schema: `StudentCourse(StudentID, CourseID, StudentName, CourseFee)`
*   **Primary Key:** `(StudentID, CourseID)`
*   **FD 1:** `StudentID -> StudentName`
*   **FD 2:** `CourseID -> CourseFee`
1. Why does this table violate 2NF? Define the specific type of dependency occurring here. *(4 marks)*
2. Decompose this table into a set of 2NF-compliant tables. *(6 marks)*

**3b. 3NF Verification (10 Marks)**
Given relation $R(W, X, Y, Z)$ with Candidate Key: $W$.
Functional Dependencies: $W \rightarrow X, X \rightarrow Y, Y \rightarrow Z$.
1. Is this relation in 3NF? Yes or No. *(2 marks)*
2. Prove your answer by explicitly defining the 2nd condition of 3NF and showing which specific FDs violate it. *(8 marks)*

**3c. BCNF (10 Marks)**
1. What is the fundamental difference between 3NF and BCNF? *(4 marks)*
2. State the condition required for a non-trivial functional dependency $\alpha \rightarrow \beta$ to be valid in BCNF. *(6 marks)*

---

## 📌 Question 4: Indexing & Trees (30 Marks)
*Focus: Chapter 14 (B/B+ Trees, Bitmaps, Index properties)*

**4a. B+ Tree Construction (12 Marks)**
Construct a **B+ Tree** of order **m = 3** (Max 2 keys per node, Max 3 children). 
Insert the following keys in this exact order: `10, 20, 30, 40, 15`.
*Note: Draw/describe the final tree. Explicitly show the linked list connecting the leaf nodes.*

**4b. B-Tree vs. B+ Tree Operations (8 Marks)**
1. In a B+ Tree, what happens to the "middle key" during a node split compared to a standard B-Tree? *(4 marks)*
2. Why does a B+ Tree drastically outperform a standard B-Tree for SQL `BETWEEN` (Range) queries? *(4 marks)*

**4c. Bitmap Indexing (10 Marks)**
You have a table `Employees` with 5 records. 
The `Department` column has values: 
*   Row 1: HR
*   Row 2: IT
*   Row 3: IT
*   Row 4: HR
*   Row 5: Finance

1. Draw the distinct Bitmap Vectors for the `Department` attribute. *(6 marks)*
2. Show the bitwise operation and result for the query: `SELECT COUNT(*) FROM Employees WHERE Department = 'HR' OR Department = 'IT';` *(4 marks)*

---
---

# 🗝️ Answer Key & Marking Guide (For Self-Evaluation)

> [!success]- Answer Key: Question 1
> **1a.** 
> 1. Vulnerability: SQL Injection (String concatenation).
> 2. Attacker input: `X' OR 'Y'='Y` (or `' OR 1=1 --`)
> 3. Fix: Use `PreparedStatement`. 
>    `PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM users WHERE username = ?"); pstmt.setString(1, userInput);`
> 
> **1b.**
> ```sql
> -- Function
> CREATE OR REPLACE FUNCTION update_budget() RETURNS TRIGGER AS $$
> BEGIN
>    IF NEW.salary <> OLD.salary THEN
>       UPDATE department 
>       SET total_salary_expense = total_salary_expense + (NEW.salary - OLD.salary)
>       WHERE dept_id = NEW.dept_id;
>    END IF;
>    RETURN NEW;
> END;
> $$ LANGUAGE plpgsql;
> 
> -- Trigger
> CREATE TRIGGER trg_salary_change
> AFTER UPDATE OF salary ON employee
> FOR EACH ROW EXECUTE PROCEDURE update_budget();
> ```
> 
> **1c.** 
> ```sql
> SELECT date, item, 
>        SUM(revenue) OVER (PARTITION BY item ORDER BY date ROWS UNBOUNDED PRECEDING) as running_total
> FROM sales;
> ```
> 
> **1d.**
> 4. Base Case (Non-recursive starting point)
> 5. Recursive Step (Query joining view with itself).
> *Termination:* It stops when an iteration produces **zero new rows** (Fixed Point).

> [!success]- Answer Key: Question 2
> **2a.** 
> *   Start: $\{A\}^+$
> *   $A \rightarrow B$ (Given) $\Rightarrow \{A, B\}^+$
> *   $B \rightarrow C$ (Transitivity) $\Rightarrow \{A, B, C\}^+$
> *   $C \rightarrow D$ (Transitivity) $\Rightarrow \{A, B, C, D\}^+$
> *   $D \rightarrow E$ (Transitivity) $\Rightarrow \{A, B, C, D, E\}^+$
> *   Final using Union: $\{A, B, C, D, E\}$
> 
> **2b.**
> *   **Phase 1:** Start with $\{A,B,C,D,E\}$. 
>     *   $A \rightarrow B$ (discard B) $\Rightarrow \{A,C,D,E\}$
>     *   $B \rightarrow C$ (discard C, via Transitivity $A \rightarrow C$) $\Rightarrow \{A,D,E\}$
>     *   $C \rightarrow D$ (discard D, via Transitivity $A \rightarrow D$) $\Rightarrow \{A,E\}$
>     *   $D \rightarrow E$ (discard E, via Transitivity $A \rightarrow E$) $\Rightarrow \{A\}$.
>     *   *First Candidate key:* $A$.
> *   **Phase 2:**
>     *   Prime Attributes: $\{A\}$
>     *   Dependent Attributes (Outputs): $\{B, C, D, E\}$
>     *   Intersection: $\{A\} \cap \{B, C, D, E\} = \emptyset$
>     *   *Conclusion:* No other Candidate Keys exist.
> 
> **2c.**
> *   $R_1 \cap R_2 = \{A, B, C\} \cap \{C, D, E\} = \{C\}$
> *   Does $C \rightarrow ABC$? No.
> *   Does $C \rightarrow CDE$? Yes! Because $C \rightarrow D$ and $D \rightarrow E$, therefore $C \rightarrow DE$ (Transitivity & Union).
> *   *Conclusion:* It is a **Lossless Decomposition** because the intersection $C$ is a superkey for $R_2$.

> [!success]- Answer Key: Question 3
> **3a.**
> 1. **Violation:** Partial Dependency. A non-prime attribute depends on only *part* of the composite primary key (e.g., `StudentName` depends only on `StudentID`, not `CourseID`).
> 2. **Decomposition:**
>    *   `Students(StudentID, StudentName)`
>    *   `Courses(CourseID, CourseFee)`
>    *   `Enrollment(StudentID, CourseID)`
> 
> **3b.** 
> 1. No, it is not in 3NF.
> 2. **3NF Condition 2:** No Transitivity Dependency for Non-Prime Attributes (NonPA $\rightarrow$ NonPA is forbidden). 
>    *   Key is $W$. 
>    *   $X$, $Y$, $Z$ are Non-Prime Attributes.
>    *   $X \rightarrow Y$ and $Y \rightarrow Z$ violate this rule because both sides of the dependencies are Non-Prime Attributes.
> 
> **3c.**
> 1. BCNF (3.5NF) is stricter. 3NF allows anomalies if a relation has multiple overlapping candidate keys. BCNF eliminates this by strictly enforcing the left-hand side of an FD.
> 2. **Condition:** For every non-trivial functional dependency $\alpha \rightarrow \beta$, $\alpha$ **MUST be a Superkey**.

> [!success]- Answer Key: Question 4
> **4a.** 
> *Simulation tracking (Order m=3 means max 2 keys, split at 3 keys):*
> *   Insert 10, 20: `[10 | 20]`
> *   Insert 30: Node full `[10 | 20 | 30]`. Split. Middle key (20) copies up. 
>     * Root: `[20]` 
>     * Leaves: `[10]` -> `[20 | 30]`
> *   Insert 40: Goes to right leaf. Full `[20 | 30 | 40]`. Split. Middle (30) copies up.
>     * Root: `[20 | 30]`
>     * Leaves: `[10]` -> `[20]` -> `[30 | 40]`
> *   Insert 15: Goes to middle leaf. 
>     * Root: `[20 | 30]`
>     * Leaves: `[10 | 15]` -> `[20]` -> `[30 | 40]` (All leaves connected by pointers).
> 
> **4b.**
> 1. **B-Tree:** Middle key *moves up* to the parent and disappears from the child. **B+ Tree:** Middle key *copies up* to the parent, but *stays* in the leaf node (data is duplicated).
> 2. **Range Queries:** In a B+ Tree, all leaf nodes are connected via a linked list. To do a `BETWEEN` query, you traverse the tree once to find the start value, then simply walk the linked list horizontally. A B-Tree requires traversing up and down the tree for every value.
> 
> **4c.**
> 1. **Vectors:**
>    *   `Dept='HR'`      : `1 0 0 1 0`
>    *   `Dept='IT'`      : `0 1 1 0 0`
>    *   `Dept='Finance'` : `0 0 0 0 1`
> 2. **Operation:** 
>    * `1 0 0 1 0` (HR) **OR** `0 1 1 0 0` (IT) = `1 1 1 1 0`
>    * **Result:** Count the 1s $\rightarrow$ Answer is **4**. (No disk access needed).