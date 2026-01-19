# 🔥 Hard DBMS Midterm Practice (Level 2)

**Scope:** Advanced Relational Algebra, Complex SQL Logic, Schema Design constraints.
**Date:** Friday, January 16, 2026

---

## 📚 Exam Schema Reference
*Refer to this schema for all questions below.*

- **student** (`ID` PK, `name`, `dept_name`, `tot_cred`)
- **instructor** (`ID` PK, `name`, `dept_name`, `salary`)
- **course** (`course_id` PK, `title`, `dept_name`, `credits`)
- **prereq** (`course_id` FK, `prereq_id` FK) *-- Composite PK (course_id, prereq_id)*
- **section** (`course_id`, `sec_id`, `semester`, `year`, `building`, `room_number`, `time_slot_id`) *-- PK is (course_id, sec_id, semester, year)*
- **takes** (`ID` FK, `course_id`, `sec_id`, `semester`, `year`, `grade`) *-- PK includes all except grade*
- **teaches** (`ID` FK, `course_id`, `sec_id`, `semester`, `year`)

---

## 💀 Challenge 1: The "Elite Departments" Query
**Topic:** *Aggregation with Nested Subqueries in HAVING*

**Question:**
Find the name of every department where the **average** salary of its instructors is **higher** than the average salary of **all** instructors in the university.
**Condition:** You must ONLY include departments that have **at least 3** instructors.

> [!tip] Hint
> You need a `GROUP BY` with a `HAVING` clause. The `HAVING` clause will contain *two* conditions: one for the count, and one containing a subquery for the global average.

> [!success]- Solution
> ```sql
> SELECT dept_name 
> FROM instructor 
> GROUP BY dept_name 
> HAVING COUNT(ID) >= 3 
>    AND AVG(salary) > (SELECT AVG(salary) FROM instructor);
> ```

---

## 🕵️ Challenge 2: The "Specific Mentor" (Relational Division)
**Topic:** *Double Negation Logic*

**Question:**
Find the IDs of students who have taken **every single course** that is taught by instructor **'Einstein'**.
*(Assume Einstein's ID is '10101')*.

> [!tip] Logic Check
> Rephrase: Find students where *there is no course* taught by Einstein that the student *has not taken*.

> [!success]- Solution
> ```sql
> SELECT S.ID 
> FROM student S 
> WHERE NOT EXISTS (
>     -- Set of courses taught by Einstein
>     (SELECT DISTINCT course_id 
>      FROM teaches 
>      WHERE ID = '10101')
>     
>     EXCEPT
>     
>     -- Set of courses taken by this student
>     (SELECT course_id 
>      FROM takes 
>      WHERE ID = S.ID)
> );
> ```

---

## ⏳ Challenge 3: Temporal Analysis
**Topic:** *Self-Joins & Date Logic*

**Question:**
Find the `course_id` and `title` of courses that were offered in **Fall 2023** AND **Spring 2024**, but were NOT offered in **Fall 2024**.

> [!tip] Hint
> This is a classic Set Operation question. `(Set A INTERSECT Set B) EXCEPT Set C`.

> [!success]- Solution
> ```sql
> (SELECT course_id FROM section WHERE semester = 'Fall' AND year = 2023
>  INTERSECT
>  SELECT course_id FROM section WHERE semester = 'Spring' AND year = 2024)
> EXCEPT
> SELECT course_id FROM section WHERE semester = 'Fall' AND year = 2024;
> ```
> *Note: Wrap this in a subquery or join with `course` table if you need the `title` as well.*

---

## 🛡️ Challenge 4: Security Hierarchy
**Topic:** *RBAC & Grant Options*

**Scenario:**
1. **Admin** executes: `GRANT SELECT ON student TO Prof_A WITH GRANT OPTION;`
2. **Prof_A** executes: `GRANT SELECT ON student TO TA_Bob;`
3. **Admin** executes: `REVOKE SELECT ON student FROM Prof_A CASCADE;`

**Question:**
Does **TA_Bob** still have access to the `student` table? Why or why not?

> [!success]- Answer
> **No.**
> Because `CASCADE` was used, the revocation ripples down to everyone Prof_A granted the privilege to. If Admin had used `RESTRICT`, the revoke command itself would have failed.

---

## 🏗️ Challenge 5: Complex DDL Constraints
**Topic:** *Schema Design & Checks*

**Question:**
Write the SQL `CREATE TABLE` statement for a table named **`Project`** with the following strict requirements:
1. `project_id`: Primary Key.
2. `start_date` and `end_date`: Dates.
3. **Constraint:** `end_date` must be after `start_date`.
4. `budget`: Numeric.
5. `status`: Text, can only be 'Proposed', 'Active', or 'Finished'.
6. **Constraint:** If `status` is 'Active', `budget` CANNOT be NULL. (This requires a logical implication check).

> [!tip] Logic for Implication
> "If A then B" is logically equivalent to "NOT A OR B".
> So: "Status is NOT Active OR Budget is NOT NULL".

> [!success]- Solution
> ```sql
> CREATE TABLE Project (
>     project_id INT PRIMARY KEY,
>     start_date DATE,
>     end_date DATE,
>     budget NUMERIC,
>     status VARCHAR(20),
>     
>     CONSTRAINT check_dates CHECK (end_date > start_date),
>     CONSTRAINT valid_status CHECK (status IN ('Proposed', 'Active', 'Finished')),
>     
>     -- The Hard Constraint:
>     CONSTRAINT active_needs_budget CHECK (
>         status != 'Active' OR budget IS NOT NULL
>     )
> );
> ```
