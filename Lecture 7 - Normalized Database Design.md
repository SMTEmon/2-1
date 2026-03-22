
***


> [!abstract] What is this chapter about?
> When building a database, you could just throw all your data into **One Big Table** (a "Mega-Schema"). But doing this creates massive problems. **Normalization** is the step-by-step process of breaking down that One Big Table into smaller, highly efficient tables to prevent data corruption.

## 1. The Problem with "One Big Table" (Anomalies)
Why not just put everything (Students, Courses, Teachers, Budgets) into one massive table? Because Joins are computationally expensive, right? 

While Joins *are* expensive, keeping everything in one table creates **Anomalies** (data corruption). **Data Integrity > Performance.** We accept the cost of Joins to guarantee data correctness.

There are 3 types of Anomalies:
* **Insertion Anomaly:** You cannot add a new fact until you have other information. *Example: You can't add a new "Robotics" department to the database until you hire at least one teacher for it (because TeacherID is the primary key).*
* **Update Anomaly:** To change one piece of information, you have to update multiple rows. *Example: If the CS department budget changes, you have to find every single CS teacher's row and update the budget. If you miss one, your database is corrupted (inconsistent).*
* **Deletion Anomaly:** Deleting a row accidentally deletes completely unrelated facts. *Example: If John is the only teacher in the New York office, and John retires (so you delete his row), you completely lose the address and phone number of the New York office.*

---

## 2. Lossy vs. Lossless Decomposition
To fix the anomalies, we **decompose** (split) the big table into smaller tables. But we have to split it correctly.

> [!check] Lossless Decomposition (The Goal)
> If you split Table A into Table B and Table C, you MUST be able to `NATURAL JOIN` B and C back together to get the exact original Table A. 
> * **Rule:** The column you use to connect the two new tables (the intersection) **must be a Superkey (Primary Key)** for at least one of the new tables.

> [!danger] Lossy Decomposition (The Nightmare)
> If you split a table badly (e.g., using "First Name" as the connecting column), when you join them back together, the database gets confused by people with the same name. It creates fake, incorrect rows called **Spurious Tuples**. You have more rows, but *less accurate information*.

---

## 3. Functional Dependencies (FDs)
This is the core math of Normalization. A Functional Dependency is just a strict real-world business rule. 

**Notation:** $\alpha \rightarrow \beta$ (Read as: "Alpha functionally determines Beta").
**Plain English:** "If I know the value of Alpha, I uniquely know the value of Beta."
* *Example:* `StudentID -> StudentName`. (If I know your ID is 101, I know for an absolute fact your name is Tariq).

### The 4 Types of FDs
1. **Trivial:** Tells you nothing new. $\alpha \rightarrow \beta$ where $\beta$ is a subset of $\alpha$. 
   * *Example:* `StudentID, Name -> StudentID`
2. **Non-Trivial:** Tells you 100% new information. $\alpha$ and $\beta$ share no columns.
   * *Example:* `StudentID -> CGPA`
3. **Semi-Trivial:** A mix of old and new info.
   * *Example:* `StudentID, Name -> Name, CGPA`
4. **Transitive:** A chain reaction. 
   * *Example:* If `StudentID -> Dept`, and `Dept -> Budget`, then `StudentID -> Budget`.

---

## 4. Keys (Superkey vs. Candidate Key)
You must know the difference between these two to pass this class.

> [!info] Superkey (SK)
> A set of columns that uniquely identifies a row. It guarantees uniqueness, but it might contain extra, fat, useless columns.
> * *Example:* `{StudentID}` is a superkey. But so is `{StudentID, EyeColor, FavoriteFood}`. 

> [!star] Candidate Key (CK)
> A Superkey that has **absolutely no redundant columns**. It is the absolute minimum number of columns needed to identify a row. If you take even one column away, it stops being a key.
> * *Example:* `{StudentID}` is a Candidate Key. 

**Terminology Check:**
* **Prime Attribute:** Any column that is part of *any* Candidate Key.
* **Non-Prime Attribute:** A regular column that is NOT part of any Candidate Key.

---

## 5. Armstrong's Axioms
When you design a database, you are given a few starting rules (FDs). But those rules mathematically create "Hidden Rules." Armstrong's Axioms are 6 math shortcuts used to prove all the hidden rules (the "Closure" of the rules, written as $F^+$).

**The Primary Rules:**
1. **Reflexivity:** `If B is inside A, then A -> B`. (Trivial rule).
2. **Augmentation:** `If A -> B, then AC -> BC`. (Adding the same context to both sides is legal).
3. **Transitivity:** `If A -> B and B -> C, then A -> C`. (Chain reaction).

**The Secondary Rules (Shortcuts):**
4. **Union:** `If A -> B and A -> C, then A -> BC`. (Combine the outputs).
5. **Decomposition:** `If A -> BC, then A -> B and A -> C`. (Split the outputs. **WARNING: NEVER SPLIT THE LEFT SIDE**).
6. **Pseudotransitivity:** `If A -> B and BC -> D, then AC -> D`. 

---

## 6. Finding Candidate Keys (The Optimized Method 3)
*This is the most important algorithm in the chapter. You need Candidate Keys to check Normal Forms. Do not guess randomly. Use this step-by-step method.*

**The Goal:** Find the absolute minimum set of columns (Candidate Key) that can determine every other column in the table.

**Example Scenario:**
Table Columns: `R(A, B, C, D, E)`
Given Rules: `A -> B`, `B -> C`, `C -> D`, `D -> E`

### Phase 1: The Discard Process (Find your first Key)
1. Start with a "basket" containing every column: `{A, B, C, D, E}`
2. Look at the right side of your rules (the outputs). If a column is on the right side of a rule, it can be generated by something else. **Throw it out of your basket.**
   * `A -> B` (Throw away B) -> Basket is `{A, C, D, E}`
   * `B -> C` (Throw away C) -> Basket is `{A, D, E}`
   * `C -> D` (Throw away D) -> Basket is `{A, E}`
   * `D -> E` (Throw away E) -> Basket is `{A}`
3. You can't throw anything else away. Your Reduced Set is `{A}`.
4. **Conclusion:** `{A}` is your first **Candidate Key**.

### Phase 2: The Replacement Process (Find alternative Keys)
Sometimes a table has multiple valid Candidate Keys. You must check for them.
1. Create a list of your **Prime Attributes** (Columns in the Candidate key you just found). Here: `{A}`.
2. Create a list of **Dependent Attributes** (All columns on the right side of your given rules). Here: `{B, C, D, E}`.
3. Check the intersection: Does `{A}` exist in `{B, C, D, E}`? 
4. **No (Empty).** Since there is no overlap, you cannot swap anything. `{A}` is the ONLY Candidate Key for this table.
*(Note: If there was an overlap, say `C` was in both lists, and you had a rule `B -> C`, you would swap `C` for `B` to create a new key. See Slides 99-105 for a visual of this).*

---

## 7. The Normal Forms
Normalization is a ladder. To be in 3NF, you must first pass 1NF and 2NF.

### 1st Normal Form (1NF): "The Atomic Rule"
* **The Rule:** Every cell must hold a single, atomic value. No lists, no arrays, no sub-parts.
* **Violation:** A "Phone Number" column that contains `0176543, 0176548` in a single cell.
* **Fix:** Create a separate Phone Number table, or add a new row for every phone number.

### 2nd Normal Form (2NF): "The Partial Dependency Rule"
* **The Rule:** Must be in 1NF. AND there must be **NO Partial Dependencies**.
* **What is a Partial Dependency?** When a non-key column depends on *only a part* of a composite Primary Key.
* **Violation Example:** Primary Key is `(StudentID, CourseID)`. You have a column called `StudentName`. `StudentName` only depends on `StudentID`. It doesn't care about the `CourseID`. This is a partial dependency.
* **Fix:** Break it into two tables. One for Students, one for Course Enrollments.

### 3rd Normal Form (3NF): "The Transitive Rule"
* **The Rule:** Must be in 2NF. AND there must be **NO Transitive Dependencies between Non-Prime Attributes**. 
* **Simplified Rule:** Non-key columns cannot depend on other non-key columns. (`Non-Prime -> Non-Prime` is illegal).
* **Violation Example:** Primary key is `StudentID`. You have columns `Department` and `DepartmentBudget`. `StudentID -> Department`, and `Department -> DepartmentBudget`. The Budget depends on the Department, not the Student. 
* **Fix:** Split into a Student table and a Department table.

### Boyce-Codd Normal Form (BCNF): "The Strict Rule"
*Also known as 3.5 NF.*
* **The Rule:** Must be in 3NF. AND for *every* non-trivial rule $X \rightarrow Y$ in your table, **$X$ MUST be a Superkey**.
* **Why do we need this?** 3NF is usually enough. But 3NF has a loophole: it allows Prime Attributes to be determined by Non-Prime attributes. This causes anomalies if a table has *overlapping composite Candidate Keys*.
* **Violation Example:** (Slide 143). Students take courses. A course can have many teachers, but a teacher only teaches one course. 
  * Candidate Key is `(StudentID, CourseID)`.
  * Rule: `TeacherID -> CourseID`.
  * `TeacherID` is NOT a Superkey (because a teacher can have many students). Therefore, it violates BCNF.
* **Fix:** Decompose into `(StudentID, TeacherID)` and `(TeacherID, CourseID)`.

> [!tip] Cheat Sheet for Normal Form Rules
> * **2NF Forbids:** `Part of Key -> Non-Key Attribute`
> * **3NF Forbids:** `Non-Key Attribute -> Non-Key Attribute`
> * **BCNF Forbids:** `ANYTHING -> Anything` (Unless the left side is a Superkey).