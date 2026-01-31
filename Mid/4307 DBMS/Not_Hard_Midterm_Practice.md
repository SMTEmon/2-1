# 🧠 Hard Midterm Practice Problems (DBMS)

**Focus:** Intermediate SQL, Transactions, and ERD Conversion.
**Date:** Friday, January 16, 2026

---

## 🚀 Problem 1: The "Super-Student" (Relational Division)
**Topic:** *Advanced Subqueries & Set Difference*

**Question:** 
Using the university schema, find the `ID` and `name` of all students who have taken **every** course offered by the 'Biology' department that is worth **more than 3 credits**.

> [!danger] Constraint
> You **cannot** use `COUNT()`. You must use logic that ensures specific course matching (The "Double Negation" pattern).

> [!success]- Solution
> ```sql
> SELECT S.ID, S.name
> FROM student S
> WHERE NOT EXISTS (
>     -- 1. Find all courses that fit the criteria
>     (SELECT course_id 
>      FROM course 
>      WHERE dept_name = 'Biology' AND credits > 3)
>     
>     EXCEPT
>     
>     -- 2. Subtract the courses the specific student has actually taken
>     (SELECT T.course_id 
>      FROM takes T 
>      WHERE T.ID = S.ID)
> );
> ```
> **Logic:** "Find students for whom there is *no* Biology course (>3 credits) that they have *not* taken."

---

## 🔄 Problem 2: The "Circular Marriage" Trap
**Topic:** *Transactions & Deferrable Constraints*

**Scenario:** 
You have a table `person` where `spouse_id` is `NOT NULL` and references `person(id)`.

```sql
CREATE TABLE person (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    spouse_id INT NOT NULL REFERENCES person(id)
);
```

**Task:** Write a transaction to insert Alice (ID 1) and Bob (ID 2) as a married couple.

> [!tip] Visualizing the Deadlock
> Alice needs Bob to exist $\leftarrow$ Bob needs Alice to exist.
> Standard `INSERT` statements will fail regardless of order.

> [!success]- Solution
> ```sql
> BEGIN;
> 
> -- Temporary 'blindfold' for the database
> SET CONSTRAINTS ALL DEFERRED;
> 
> INSERT INTO person (id, name, spouse_id) VALUES (1, 'Alice', 2);
> INSERT INTO person (id, name, spouse_id) VALUES (2, 'Bob', 1);
> 
> -- Database checks all references NOW
> COMMIT;
> ```

---

## 👻 Problem 3: The "Ghost Row" (Natural Join Trap)
**Topic:** *Join Logic & Column Matching*

**Scenario:** 
You are performing a join across three tables. 

| Table | Columns | 
| :--- | :--- |
| **student** | `id`, `name`, **`dept_name`** |
| **takes** | `id`, `course_id` |
| **course** | `course_id`, `title`, **`dept_name`** |

**Data:** Alice is in **'CS'**. She takes **'Music-101'** (which is in the **'Music'** dept).

**Question:** Why does the following query return **zero** rows for Alice?
```sql
SELECT name, title FROM student NATURAL JOIN takes NATURAL JOIN course;
```

> [!info]- Visual Explanation
> ```mermaid
> graph TD
>     A[student] -- "Matches ID" --> B[takes]
>     B -- "Matches course_id" --> C[course]
>     A -. "TRAP: Also matches dept_name" .-> C
> ```
> **The Problem:** `NATURAL JOIN` finds **all** common columns. 
> 1. It links `student` and `takes` via `id`.
> 2. It then links that result to `course` using **BOTH** `course_id` AND `dept_name`.
> 3. Since Alice's `dept_name` (CS) $\neq$ Course `dept_name` (Music), the row is deleted.

---

## 🏗️ Problem 4: ERD to Schema (Complex Mapping)
**Topic:** *Weak Entities & Ternary Relationships*

**Scenario:** 
Convert the following requirements into SQL Tables:
1. **Dependent:** A weak entity of `Employee`. Unique by `name` only within that employee's context.
2. **Supply:** A ternary relationship between `Supplier`, `Part`, and `Project`.

> [!tip] Conceptual Visual
> ```mermaid
> erDiagram
>     EMPLOYEE ||--o{ DEPENDENT : "has (Weak)"
>     SUPPLIER ||--o{ SUPPLY : "provides"
>     PART ||--o{ SUPPLY : "is provided"
>     PROJECT ||--o{ SUPPLY : "receives"
> ```

> [!success]- Solution (SQL DDL)
> ```sql
> -- 1. Weak Entity Implementation
> CREATE TABLE Dependent (
>     emp_id INT REFERENCES Employee(id) ON DELETE CASCADE,
>     dep_name VARCHAR(50),
>     PRIMARY KEY (emp_id, dep_name) -- Composite PK
> );
> 
> -- 2. Ternary Relationship Implementation
> CREATE TABLE Supply (
>     s_id INT REFERENCES Supplier(id),
>     p_id INT REFERENCES Part(id),
>     proj_id INT REFERENCES Project(id),
>     quantity INT,
>     PRIMARY KEY (s_id, p_id, proj_id) -- Triple Composite PK
> );
> ```

---

## ⚡ Quick-Fire Strategy for Today
1. **Aggregates:** If you `SELECT` it and it's not in an `AVG/SUM`, it **must** be in the `GROUP BY`.
2. **Outer Joins:** Use `LEFT JOIN` if you want to keep the "Main" list (like Students) even if they have no matches (like Grades).
3. **ERD:** Foreign Keys always go on the **"Many"** side of a 1:N relationship.
4. **Dates:** Use `AGE(timestamp1, timestamp2)` or `INTERVAL '1 day'` for arithmetic.
