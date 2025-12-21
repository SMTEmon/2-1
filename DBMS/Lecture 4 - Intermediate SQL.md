# L4: Intermediate SQL

*Date: December 19, 2025*
*Course: CSE 4307: Database Management Systems*
*Lecturer: Md. Tariquzzaman*

---

## Chapter Overview

This lecture covers more complex forms of SQL queries and essential database management features.

-   **Join Expressions**: Combining data from multiple tables using `NATURAL JOIN`, `INNER JOIN`, and `OUTER JOIN`.
-   **Views**: Creating virtual relations and understanding materialized views for performance.
-   **Transactions**: Ensuring atomic units of work with `COMMIT` and `ROLLBACK`.
-   **Integrity Constraints**: Enforcing data consistency using various constraints.
-   **Data Types**: Handling `Date/Time`, Large Objects (LOBs), and User-Defined types.
-   **Authorization**: Managing user privileges and roles for security.

---

## Reference: Tables Used in This Lecture

The examples in this lecture use different sets of tables depending on the concept being demonstrated. Refer to this section to avoid confusion.

> [!example] Set A: Main Sample Data (Joins & Views)
> *Used in Sections 1.1, 1.2, 1.5 - 1.7, and 2.*
>
> **`student`**
>
> | ID  | Name  | Dept |
> | :-- | :---- | :--- |
> | 101 | Alice | CS   |
> | 102 | Bob   | EE   |
> | 103 | Carol | CS   |
> | 104 | Dave  | Bio  |
>
> **`takes`**
>
> | ID  | Course | Grade |
> | :-- | :----- | :---- |
> | 101 | CS-101 | A     |
> | 101 | CS-102 | B     |
> | 102 | EE-200 | A     |
> | 999 | Unknown| C     |

> [!danger] Set B: The "Natural Join Trap" Data
> *Used in Section 1.3 only.*
> *Notice the matching `dept_name` column between `student` and `course`.*
>
> **`student` (Modified)**
>
> | id  | name  | **dept_name** |
> | :-- | :---- | :------------ |
> | 101 | Alice | CS            |
> | 102 | Bob   | EE            |
>
> **`course`**
>
> | course_id | title        | **dept_name** |
> | :--------- | :----------- | :------------ |
> | CS-101    | Intro to CS  | CS            |
> | EE-200    | Circuits     | EE            |
> | MUS-101   | Music Theory | Music         |
>
> **`takes`**
>
> | id  | course_id |
> | :-- | :-------- |
> | 101 | CS-101    |
> | 101 | MUS-101   |
> | 102 | EE-200    |

> [!info] Set C: Constraints & Transactions Data
> *Used in Sections 3, 4, and 5.*
>
> -   **`instructors`**: Used for `CHECK` constraints (Salary > 0).
> -   **`department` & `course`**: Used for Foreign Keys (`ON DELETE CASCADE`).
> -   **`person`**: Used for Deferrable Constraints (Circular dependency between spouses).

---

## 1. Join Expressions

### 1.1 Introduction to Joins

**Why do we need Joins?**

In previous chapters, we combined relations using the **Cartesian product** (e.g., `FROM student, takes`). A Cartesian product pairs *every* row from table A with *every* row from table B. This is often inefficient and requires a `WHERE` clause to filter for meaningful combinations (e.g., `WHERE student.id = takes.id`).

**The Solution: Join Operations**

-   Join operations allow programmers to write queries in a more natural, readable, and optimized way.
-   They help express logic that is difficult or verbose with just Cartesian products. The database optimizer can better understand the query's intent.

### 1.2 The Natural Join

The `NATURAL JOIN` matches tuples with the same value on **all** attributes that share the same name in both relations.

**Behavior**:

-   It considers only pairs of tuples where common attributes match.
-   Common attributes (like `ID` in `student` and `takes`) appear only **once** in the result.
-   **Implicit**: You do not need to specify the join columns; SQL finds them automatically based on matching column names.

**SQL Syntax**:

```sql
SELECT name, course
FROM student NATURAL JOIN takes;
```

**Result**:

| name  | course |
| ----- | ------ |
| Alice | CS-101 |
| Alice | CS-102 |
| Bob   | EE-200 |

> [!warning] 
> `NATURAL JOIN` can be dangerous and is often avoided in production code.

### 1.3 The Trap of Natural Join

`NATURAL JOIN` equates **all** common attributes. This can lead to critical logic errors if schemas share unrelated attribute names.

> [!error] Natural Join Trap: A Concrete Example
> Let's imagine our university database has these three tables. Notice that `student` and `course` both have a `dept_name` column.
>
> **`student` table:**
> 
> | id  | name  | dept_name |
> | :-- | :---- | :-------- |
> | 101 | Alice | CS        |
> | 102 | Bob   | EE        |
>
> **`course` table:**
> 
> | course_id | title        | dept_name |
> | :--------- | :----------- | :--------- |
> | CS-101    | Intro to CS  | CS        |
> | EE-200    | Circuits     | EE        |
> | MUS-101   | Music Theory | Music     |
>
> **`takes` table:**
> 
> | id  | course_id |
> | :-- | :--------- |
> | 101 | CS-101    |
> | 101 | MUS-101   |
> | 102 | EE-200    |
>
> Now, let's run the "trap query." The goal is to see which courses each student takes.
>
> ```sql
> -- This query contains a hidden trap!
> SELECT name, title
> FROM student
> NATURAL JOIN takes
> NATURAL JOIN course;
> ```
>
> **How the Trap Springs:**
> 1.  `student` is correctly joined with `takes` using the common `id` column.
> 2.  The result is then joined with `course`. The database sees two common columns: `course_id` and `dept_name`.
> 3.  It therefore joins where **both** columns match: `result.course_id = course.course_id` AND `result.dept_name = course.dept_name`.
>
> > [!info] Understanding the "Result" Table
> > You might wonder: *"Where is this 'result' table coming from?"*
> > In step 2, `result` refers to the **intermediate table** created by the first part of the query `(student NATURAL JOIN takes)`.
> > 
> > 1.  **Step 1:** The database runs `student NATURAL JOIN takes`. This creates a temporary, invisible table (let's call it **Intermediate Table A**) with columns: `id`, `name`, `dept_name` (from student), and `course_id` (from takes).
> > 2.  **Step 2:** It then joins **Intermediate Table A** with the `course` table. It finds **two** matching column names: `course_id` and `dept_name`.
> > 3.  Because Alice is a "CS" student (her `dept_name` is CS), but the Music Theory course belongs to the "Music" department, the second condition (`CS = Music`) fails, and the row is dropped.
>
> **The Incorrect Result:**
>
> | name  | title       |
> | :---- | :---------- |
> | Alice | Intro to CS |
> | Bob   | Circuits    |
>
> Alice's enrollment in "Music Theory" (`MUS-101`) has vanished! This is because her department (`CS`) does not match the course's department (`Music`), so the `NATURAL JOIN` condition fails and the row is silently discarded.

**The Correct Query and Result:**

By using an explicit `JOIN ON` clause, we tell the database exactly how to link the tables, avoiding the unintended `dept_name` match.

```sql
SELECT s.name, c.title
FROM student s
JOIN takes t ON s.id = t.id
JOIN course c ON t.course_id = c.course_id;
```

**Correct Result:**

| name  | title        |
|:------|:-------------|
| Alice | Intro to CS  |
| **Alice** | **Music Theory** |
| Bob   | Circuits     |

This result is correct and complete, demonstrating why explicit joins are safer.

### 1.4 The `USING` Clause

To avoid the `NATURAL JOIN` trap, use `JOIN ... USING`. It specifies exactly which columns to equate, even if other columns share the same name.

**Corrected Query**:

```sql
SELECT name, title
FROM (student NATURAL JOIN takes) -- This is safe as only 'ID' matches
JOIN course USING (course_id); -- Explicitly join only on course_id
```

**Why this works**:

-   This forces the join to match **only** on `course_id`.
-   `dept_name` is allowed to differ between `student` and `course`, preserving electives.

### 1.5 The `ON` Clause (Inner Join)

The `ON` condition is the most versatile and recommended way to join tables. It allows any general predicate (boolean expression). When just `JOIN` is used, it defaults to `INNER JOIN`.

**Syntax**:

```sql
SELECT name, course, grade
FROM student
JOIN takes ON student.id = takes.id;
```

This is equivalent to:

```sql
SELECT name, course, grade
FROM student
INNER JOIN takes ON student.id = takes.id;
```

**Result (Inner Join)**: An inner join returns only the rows where the join condition is met.

| Name  | Course | Grade |
| ----- | ------ | ----- |
| Alice | CS-101 | A     |
| Alice | CS-102 | B     |
| Bob   | EE-200 | A     |

> [!note] 
> Dave (ID 104) is missing because he has no matching ID in the `takes` table. This is expected data loss in an inner join.

### 1.6 Outer Joins

**Inner Join Limitation**: Tuples without matches are lost (e.g., student "Dave" disappeared).

**Outer Join Solution**: Preserves tuples that would be lost by padding the missing columns with `NULL` values.

**Three Main Types**:

1.  **`LEFT OUTER JOIN`**: Preserves all tuples from the **left** relation.
2.  **`RIGHT OUTER JOIN`**: Preserves all tuples from the **right** relation.
3.  **`FULL OUTER JOIN`**: Preserves all tuples from **both** relations.

#### `LEFT OUTER JOIN` Example

**Goal**: List ALL students, even if they haven't taken a course.

```sql
SELECT name, course, grade
FROM student
LEFT OUTER JOIN takes ON student.id = takes.id;
```

**Result**:

| Name  | Course | Grade |
| ----- | ------ | ----- |
| Alice | CS-101 | A     |
| Alice | CS-102 | B     |
| Bob   | EE-200 | A     |
| **Dave**  | `NULL`   | `NULL`  |
| Carol | `NULL` | `NULL` |

> *Dave and Carol are preserved. The missing course info is filled with `NULL`.*

#### `FULL OUTER JOIN` Example

**Goal**: Keep ALL students AND all course records, even unmatched ones (orphaned records).

```sql
SELECT name, course, grade
FROM student
FULL OUTER JOIN takes ON student.id = takes.id;
```

**Result**:

| Name  | Course | Grade |
| ----- | ------ | ----- |
| Alice | CS-101 | A     |
| Alice | CS-102 | B     |
| Bob   | EE-200 | A     |
| Dave  | `NULL` | `NULL`|
| Carol | `NULL` | `NULL`|
| `NULL`| Unknown| C     |

> *ID 999 (the "Unknown" course) is preserved from the right table. Since it doesn't match a student, its `name` is `NULL`.*

### 1.7 Additional Join Types (Self Join & Cross Join)

#### Self Join

A self join is a regular join, but the table is joined with itself. This is useful for querying hierarchical data or comparing rows within the same table.

**Example**: Find all pairs of students living in the same department.

```sql
SELECT A.name AS Student1, B.name AS Student2, A.dept
FROM student A
JOIN student B ON A.dept = B.dept AND A.id < B.id;
```

> [!tip] 
> The `A.id < B.id` condition prevents duplicate pairs (Alice, Carol) and (Carol, Alice) and prevents a student from being paired with themselves.

#### Cross Join

A `CROSS JOIN` produces the full Cartesian product of two tables. It's equivalent to the old `FROM table1, table2` syntax.

**Example**: Combine every student with every possible course (rarely useful without filtering).

```sql
SELECT s.name, t.course
FROM student s
CROSS JOIN takes t;
```

---

## 2. Views

### 2.1 Views Overview

Normally, relations are stored physically in the database. SQL allows a **virtual relation** to be defined by a query, which is called a **View**.

**Definition**:

-   A view is **not precomputed or stored**. It's a stored query.
-   It is computed **"on the fly"** by executing the query whenever the view is accessed.

**Key Functions of a View**:

1.  **Security & Access Control**: Hide sensitive data. For example, you can create a view that shows employee names and departments but hides their salary from a clerk.
2.  **Abstraction**: Present a simplified model to end-users. You can hide complex joins and calculations behind a simple view.

### 2.2 Creating and Using a View

**Scenario**: We want a list of CS students only.

```sql
CREATE VIEW cs_students AS
SELECT name, dept
FROM student
WHERE dept = 'CS';
```

**Usage**: Users can now treat `cs_students` like a normal table.

```sql
SELECT * FROM cs_students;
```

**Virtual Result**:

| Name  | Dept |
| ----- | ---- |
| Alice | CS   |
| Carol | CS   |

### 2.3 Updatability of Views

**Can we `INSERT`, `UPDATE`, or `DELETE` on a view?** Generally, **NO**, with some exceptions for simple views.

**The Problem**:
If you insert into a view, the database must unambiguously know how to insert into the underlying base table. If the database cannot clearly figure out how to create that row in the base table, the operation fails.

> [!info] Detailed Explanation: Why INSERT fails on Views
> 
> #### 1. The "Missing NOT NULL Column" Problem
> 
> **Scenario**: Imagine you have the `student` base table where `ID` is the Primary Key (cannot be `NULL`).
> 
> **Base Table: `student`**
> 
> | ID (PK) | Name  | Dept |
> | :------ | :---- | :--- |
> | 101     | Alice | CS   |
> 
> Now, you create a view to hide the student IDs for privacy, showing only names and departments.
> 
> ```sql
> CREATE VIEW public_student_list AS
> SELECT Name, Dept
> FROM student;
> ```
> 
> **The Failed Operation**: You try to add a new student named "Eve" through this view.
> 
> ```sql
> INSERT INTO public_student_list (Name, Dept)
> VALUES ('Eve', 'Music');
> ```
> 
> **Why it fails**:
> The database tries to run `INSERT INTO student (Name, Dept) VALUES ('Eve', 'Music');`.
> It stops and asks: **"What is Eve's ID?"** Since `ID` is `NOT NULL` and wasn't provided (because it wasn't in the view), the database refuses to guess, and the insert fails.
> 
> #### 2. The "Aggregates" Problem
> 
> **Scenario**: You create a view that summarizes data, such as counting students per department.
> 
> **View: `dept_counts`**
> 
> ```sql
> CREATE VIEW dept_counts AS
> SELECT Dept, COUNT(*) as Student_Count
> FROM student
> GROUP BY Dept;
> ```
> 
> **Virtual Result**:
> 
> | Dept | Student_Count |
> | :--- | :------------ |
> | CS   | 2             |
> | EE   | 1             |
> 
> **The Failed Operation**: You try to "insert" a new statistic.
> 
> ```sql
> INSERT INTO dept_counts (Dept, Student_Count)
> VALUES ('History', 5);
> ```
> 
> **Why it fails**:
> You are asking the database to make the `Student_Count` for History equal to 5. The database looks at the underlying `student` table and gets confused:
> *   "To make the count 5, I need to insert 5 rows into `student`."
> *   "Who are these 5 students? What are their IDs? What are their Names?"
> 
> Because a single row in an aggregate view represents **multiple** rows in the base table, there is no logical way to reverse-engineer a single `INSERT` statement back into the complex data required for the base table.

### 2.4 Conditions for Updatable Views

Most SQL standards (including Postgres) allow updates only on **Simple Views**. A view is simple and updatable if:

1.  The `FROM` clause has only **one** database relation.
2.  The `SELECT` clause contains only attribute names (no expressions, aggregates, or `DISTINCT`).
3.  Any attribute not listed in the `SELECT` clause must be nullable or have a default value in the base table.
4.  There are no `GROUP BY` or `HAVING` clauses.

> [!example] Examples of Updatable vs. Non-Updatable Views
>
> **1. Single Relation Rule**
> *   **Updatable**: `CREATE VIEW v1 AS SELECT name FROM student;` (One table)
> *   **Not Updatable**: `CREATE VIEW v2 AS SELECT s.name, t.course_id FROM student s JOIN takes t ON s.ID = t.ID;` (Two tables joined)
>
> **2. No Expressions/Aggregates Rule**
> *   **Updatable**: `CREATE VIEW v3 AS SELECT salary FROM instructor;`
> *   **Not Updatable**: `CREATE VIEW v4 AS SELECT salary + 1000 FROM instructor;` (Expression cannot be reversed to find original salary)
> *   **Not Updatable**: `CREATE VIEW v5 AS SELECT MAX(salary) FROM instructor;` (Aggregate)
>
> **3. Unlisted Columns Rule**
> *   **Scenario**: `student` table has `ID` (PK, Not Null), `Name` (Not Null), `Dept` (Nullable).
> *   **Updatable**: `CREATE VIEW v6 AS SELECT ID, Name FROM student;` (Missing `Dept` is fine as it can be NULL).
> *   **Not Updatable**: `CREATE VIEW v7 AS SELECT Name, Dept FROM student;` (Missing `ID` which is Not Null and has no default).
>
> **4. No Grouping Rule**
> *   **Not Updatable**: `CREATE VIEW v8 AS SELECT dept, COUNT(*) FROM student GROUP BY dept;` (Cannot insert into a group).

### 2.5 Materialized Views

**Definition**: Unlike standard views, **Materialized Views** physically store the result of the query.

**Use Case**: Ideal for queries that aggregate large amounts of data (e.g., calculating total sales by department for a dashboard). Materializing avoids re-computing the sum every time the view is accessed, significantly improving performance.

**PostgreSQL Syntax**:

```sql
CREATE MATERIALIZED VIEW dept_stats AS
SELECT dept, COUNT(*) as num_students
FROM student
GROUP BY dept;
```

**Maintenance**: The data can become stale. You must update it explicitly.

```sql
REFRESH MATERIALIZED VIEW dept_stats;
```

---

## 3. Transactions

### 3.1 Transaction Theory

A **Transaction** is a sequence of query and/or update statements that make up a single logical unit of work.

**The ACID Properties**: Transactions guarantee data integrity through the ACID properties.

-   **A - Atomicity**: "All or Nothing". Either all steps of the transaction complete successfully, or none of them do. If any step fails, the entire transaction is rolled back.
-   **C - Consistency**: The database moves from one valid state to another. Transactions ensure all integrity constraints (like foreign keys) are satisfied at the end of the transaction.
-   **I - Isolation**: Transactions running concurrently do not interfere with each other. Each transaction feels like it's the only one running on the system.
-   **D - Durability**: Once a transaction is committed, its changes are permanent and will survive system failures (like a power outage).

**SQL Commands**:

-   `COMMIT`: Makes updates permanent.
-   `ROLLBACK`: Undoes all updates performed by the transaction.

### 3.2 Transaction Example: Bank Transfer

**Scenario**: Transfer $100 from Account A (ID 1) to Account B (ID 2).

**Step 1: Start and Deduct**

```sql
BEGIN;
UPDATE accounts SET balance = balance - 100
WHERE id = 1;
```

> [!danger] System Crash Risk
> If the power fails here, money is deducted from Account A but not added to Account B. The bank has lost money. **Atomicity** prevents this.

**Step 2: Add and Commit**

```sql
UPDATE accounts SET balance = balance + 100
WHERE id = 2;
COMMIT;
```

> The `COMMIT` ensures both updates happen together as a single atomic unit. If a failure occurred before the `COMMIT`, the `ROLLBACK` (which happens automatically on crash recovery) would undo the first `UPDATE`.

---

## 4. Integrity Constraints

Constraints are rules that guard against accidental damage to the database. They ensure **Data Consistency**.

**Where to enforce?**

-   **UI Design (Frontend)**: Good for immediate user feedback (e.g., "Password is too short"), but is easily bypassable by malicious users or other applications.
-   **Database (Backend)**: **Essential**. Ensures that no authorized or unauthorized changes can result in data loss or inconsistency.

### 4.1 Types of Constraints

1.  **`NOT NULL`**: Attribute cannot be null (e.g., a student's `Name`).
2.  **`UNIQUE`**: Values in the column (or a set of columns) must be unique across all rows (e.g., email address). These are candidate keys.
3.  **`PRIMARY KEY`**: Uniquely identifies a row. It's a combination of `NOT NULL` and `UNIQUE`.
4.  **`CHECK (P)`**: Ensures a predicate (condition) `P` is satisfied for every row.
5.  **`FOREIGN KEY`**: Enforces referential integrity.

### 4.2 `CHECK` Constraint Example

**Scenario**: Salary must be positive, and Department must be one of the allowed values.

```sql
CREATE TABLE instructors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    salary NUMERIC,
    dept_name VARCHAR(20),

    CONSTRAINT positive_salary CHECK (salary > 0),
    CONSTRAINT valid_dept CHECK (dept_name IN ('CS', 'EE', 'Bio'))
);
```

> [!warning] 
> Attempting to insert a negative salary (`-5000`) or an invalid department (`'Music'`) will trigger a database error.

### 4.3 Referential Integrity (Foreign Keys)

**Definition**: Ensures that a value appearing in one relation (the referencing or child table) also exists in another relation (the referenced or parent table).

**Cascading Actions**: What happens if the referenced data is deleted?

-   `ON DELETE NO ACTION`: Default behavior. Rejects the deletion if any child rows reference the parent row.
-   `ON DELETE CASCADE`: Deletes the referencing (child) rows too.
-   `ON DELETE SET NULL`: Sets the referencing foreign key column in the child rows to `NULL`.

#### Cascading Delete Example

**Scenario**: If a Department is deleted, delete all its Courses automatically.

```sql
CREATE TABLE course (
    course_id VARCHAR(10) PRIMARY KEY,
    dept_name VARCHAR(20),

    FOREIGN KEY (dept_name)
        REFERENCES department(dept_name)
        ON DELETE CASCADE
);
```

**Operation**:
`DELETE FROM department WHERE dept_name = 'History';`

**Result**: The database automatically finds all 'History' courses and deletes them to maintain integrity.

### 4.4 Advanced: Deferrable Constraints

**The Circular Dependency Problem**: How do we insert a married couple if each `person` must reference a `spouse_id` that already exists? We cannot insert the husband because the wife doesn't exist yet, and vice versa.

```sql
CREATE TABLE person (
    ID int PRIMARY KEY,
    spouse_id int REFERENCES person(ID)
);
```

**Solution**: Deferrable constraints are checked only at `COMMIT` time, allowing temporary inconsistency within a transaction.

```sql
BEGIN;
SET CONSTRAINTS ALL DEFERRED;

-- Insert Husband with a temporary NULL or dummy spouse_id
INSERT INTO person (ID, spouse_id) VALUES (1, NULL);

-- Insert Wife, pointing to the husband
INSERT INTO person (ID, spouse_id) VALUES (2, 1);

-- Update Husband with the real spouse_id
UPDATE person SET spouse_id = 2 WHERE ID = 1;

COMMIT; -- All constraints are checked here.
```

---

## 5. Date and Time

### 4.5.1 Date and Time Types (Postgres)

The SQL standard supports several date and time types:

-   `DATE`: Stores year, month, and day (e.g., `'2025-10-25'`).
-   `TIME`: Stores hours, minutes, and seconds.
-   `TIMESTAMP`: Stores date and time combined. `TIMESTAMPTZ` includes timezone information.

**Getting the Current Time**:
-   Oracle: `SYSDATE`
-   PostgreSQL: `CURRENT_DATE`, `NOW()`

### 4.5.2 Date Conversion and Formatting

-   `TO_CHAR()`: Formats a date/time value into a string.
    ```sql
    SELECT TO_CHAR(NOW(), 'DD-Mon-YYYY HH24:MI');
    -- Output: 19-Dec-2025 14:30
    ```
-   `TO_DATE()`: Converts a string into a date.
    ```sql
    SELECT TO_DATE('05 Jan 2017', 'DD Mon YYYY');
    -- Output: 2017-01-05
    ```

**Common `TO_CHAR` Format Specifiers**:

| Specifier | Meaning                         |
| --------- | ------------------------------- |
| `YYYY`      | 4-digit year                    |
| `YY`        | 2-digit year                    |
| `MONTH`     | Full month name (e.g., January) |
| `MM`        | Month number (1-12)             |
| `DD`        | Day of month (1-31)             |
| `DY`        | Abbreviated day name (Sun-Sat)  |
| `Day`       | Full day name (e.g., Sunday)    |
| `HH24`      | Hour (0-23)                     |
| `HH` or `HH12` | Hour (1-12)                     |
| `MI`        | Minutes (0-59)                  |
| `SS`        | Seconds (0-59)                  |

### 4.5.3 Date Arithmetic (Intervals)

PostgreSQL uses `INTERVAL` for date math instead of specific functions like `ADD_MONTHS`.

**Examples**:
```sql
-- Add 7 days to the current date
SELECT CURRENT_DATE + INTERVAL '7 days';

-- Add 1 year and 3 months
SELECT CURRENT_DATE + INTERVAL '1 year 3 months';

-- Calculate Age
SELECT AGE('2025-01-01', '2000-01-01');
-- Output: 25 years
```

### 4.5.4 Large Objects (LOBs)

Used to store large data items, from kilobytes to gigabytes.

-   **`CLOB` (Character Large Object)**: Used for large text (e.g., book chapters, XML files). Postgres uses the `TEXT` type for this.
-   **`BLOB` (Binary Large Object)**: Used for binary data (e.g., images, videos, PDFs). Postgres uses `BYTEA` or the Large Object facility (`LO`).

**Efficiency**: Queries typically return a **locator** (a pointer to the object) rather than the entire object itself to avoid transferring large amounts of data unnecessarily.

---

## 6. Create Table Extensions

### 4.5.6 Create Table As Select (CTAS)

Often we need to create a table that has the same structure as an existing one.

**Syntax (CTAS)**: This copies both the structure AND the data.

```sql
CREATE TABLE new_students AS
SELECT ID, NAME, GPA
FROM students;
```

**Trick: Copy Structure Only**: By providing a `WHERE` clause that is always false, no rows are copied, only the column structure.

```sql
CREATE TABLE empty_student_table AS
SELECT * FROM students
WHERE 1=0; -- This is always false
```

---

## 7. Authorization

### 4.6 Role-Based Access Control (RBAC)

RBAC is a method for managing access control for large systems with many users. Instead of assigning permissions to users individually, we manage permissions through **Roles**.

**Privileges**: These are the permissions you can grant or revoke.
-   `SELECT`, `INSERT`, `UPDATE`, `DELETE` (For data access)
-   `EXECUTE` (For running functions/procedures)
-   `REFERENCES` (For creating foreign keys)

### 4.6.1 Granting and Revoking

**Grant Syntax**:

```sql
-- Give a role permission to select and insert into the students table
GRANT SELECT, INSERT
ON students
TO faculty_role;
```

**Revoke Syntax**:

```sql
-- Remove the insert permission from the role
REVOKE INSERT
ON students
FROM faculty_role;
```

### 4.6.2 Roles and Hierarchy

Roles can be assigned to other roles, creating a hierarchy.

**Example**: A `dean` role can inherit all permissions from a `teacher` role.

```sql
CREATE ROLE teacher;
CREATE ROLE dean;

-- Give teacher permissions to the dean
GRANT teacher TO dean;
```

**Transfer of Privileges**:
-   By default, a user cannot pass their privileges to others.
-   `WITH GRANT OPTION`: Allows the recipient of a privilege to further grant it to other roles.
    ```sql
    -- Allow the faculty_role to grant select permissions to others
    GRANT SELECT ON students TO faculty_role WITH GRANT OPTION;
    ```

### RBAC Example Diagram

![RBAC Example](https://i.imgur.com/r62Kq4k.png)
*Figure: Role-based Access Control in a Result Processing System (RPS)*

---

## Summary

-   **Joins**: Master `INNER`, `LEFT`, `RIGHT`, and `FULL` joins to link tables. Avoid `NATURAL JOIN` pitfalls by using the `ON` or `USING` clause.
-   **Views**: Use for abstraction and security. Understand update limitations and use Materialized Views for performance on expensive aggregation queries.
-   **Transactions**: Rely on ACID properties (especially Atomicity) to ensure data safety using `COMMIT` and `ROLLBACK`.
-   **Constraints**: Essential for backend data integrity. Use `CHECK`, `FOREIGN KEY`, and cascading actions to maintain consistency.
-   **Authorization**: Use Roles (`RBAC`) for scalable and manageable security.
