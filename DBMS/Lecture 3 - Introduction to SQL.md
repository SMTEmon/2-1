---
course: "CSE 4307: Database Management Systems"
instructor: Md. Tariquzzaman
tags:
  - sql
  - database
  - dbms
  - CS
---
---

## 3.1 Overview of SQL Language
SQL is split into specific functionalities:

*   **DML (Data Manipulation Language):** The "hands" of the DB. Used to `INSERT`, `DELETE`, `UPDATE`, and `QUERY` data.
*   **DDL (Data Definition Language):** The "architect's blueprint". Defines schema, constraints, and views.
*   **Integrity Constraints:** Rules to keep data accurate (e.g., no negative ages).
*   **View Definition:** Custom windows into data (virtual tables).
*   **Transaction Control:** Manages atomicity (`BEGIN`, `COMMIT`, `ROLLBACK`).
*   **Embedded/Dynamic SQL:** Mixing SQL with languages like C, Java, Python.
*   **Authorization:** Permissions and access control.

---

## 3.2 SQL Data Definition (DDL)

DDL defines the **Schema** (structure), **Types**, **Constraints**, **Indices**, and **Storage**.

### Domain Types (Data Types)
| Type | Description | Example | Note |
| :--- | :--- | :--- | :--- |
| `char(n)` | Fixed length | `char(10)` | Pads with spaces if shorter. |
| `varchar(n)` | Variable length | `varchar(10)` | Stores only actual length. **Preferred.** |
| `int` | Integer | | Machine dependent. |
| `smallint` | Small Integer | | Efficient for small numbers. |
| `numeric(p,d)` | Fixed-point | `numeric(3,1)` | Total `p` digits, `d` after decimal. (e.g., 44.5) |
| `float(n)` | Floating point | | Precision of at least `n` digits. |

### Creating Tables
```sql
create table instructor (
    ID char(5),
    name varchar(20) not null,
    dept_name varchar(20),
    salary numeric(8,2),
    primary key (ID),
    foreign key (dept_name) references department(dept_name)
);
```

### Integrity Constraints
1.  **Primary Key:** Unique and Not Null. Identifies a row.
2.  **Foreign Key:** Ensures referential integrity (links to another table).
3.  **Not Null:** Prevents missing values.

> [!WARNING] Constraint Violations
> SQL automatically blocks updates or insertions that violate constraints (e.g., duplicate primary keys or invalid foreign keys).

### Modifying Relations
*   **Insert:** `insert into table values (...);`
*   **Delete:** `delete from table;` (Deletes rows, keeps structure).
*   **Drop:** `drop table r;` (Removes rows AND structure).
*   **Alter:**
    *   `alter table r add A D;` (Add column).
    *   `alter table r drop A;` (Remove column).

---

## 3.3 Basic Structure of SQL Queries

Standard Structure:
```sql
SELECT A1, A2 ...      -- Projection (Columns)
FROM r1, r2 ...        -- Cartesian Product (Relations)
WHERE P;               -- Selection (Predicate/Filter)
```

### Key Concepts
*   **Duplicates:** SQL allows duplicates (Multiset/Bag semantics).
    *   Use `DISTINCT` to remove duplicates: `select distinct dept_name ...`
    *   Use `ALL` to explicitly keep them (default).
*   **Literals:** Can select literals: `select '437' as FOO`.
*   **Arithmetic:** Allowed in select clause: `select salary/12 ...`
*   **Where Clause:** Supports logical connectives (`AND`, `OR`, `NOT`) and comparison (`<`, `<=`, `>`, `>=`, `=`, `<>`).

### Multi-Table Queries (Joins)
Queries dealing with multiple tables in the `FROM` clause generate a **Cartesian Product**.
```sql
-- Join with condition
select name, course_id
from instructor, teaches
where instructor.ID = teaches.ID;
```

**Self Join:** Using aliases to compare rows within the same table.
```sql
-- Find supervisors
select E1.person as employee, E2.supervisor as boss
from emp_super as E1, emp_super as E2
where E1.supervisor = E2.person;
```

---

## 3.4 Additional Basic Operations

### Rename (`AS`)
Used for attributes or relations (aliases).
```sql
select T.name 
from instructor as T, instructor as S
where T.salary > S.salary;
```

### String Operations (`LIKE`)
*   **%**: Matches any substring.
*   **_**: Matches any single character.
*   **Escape characters:** Used to match literal `%` or `_`. e.g., `like 'ab\%cd%' escape '\'`.
*   **Functions:** `upper()`, `lower()`, `trim()`, `||` (concatenation).

### Ordering
*   `ORDER BY attribute [ASC | DESC]`
*   Can sort by multiple attributes: `order by salary desc, name asc`.

### Between & Tuple Comparison
*   `WHERE salary BETWEEN 90000 AND 100000`
*   **Row Constructor:** `WHERE (instructor.ID, dept_name) = (teaches.ID, 'Biology')`

---

## 3.5 Set Operations

SQL treats results as **Multisets** (bags), but set operations act differently depending on the keyword `ALL`.

| Operation | Description | Analogy | Handling Duplicates |
| :--- | :--- | :--- | :--- |
| **UNION** | Items in A OR B | Combined guest list | Removes duplicates |
| **UNION ALL** | Items in A OR B | Combined list | Keeps duplicates (Sum of counts) |
| **INTERSECT** | Items in A AND B | Guests at both parties | Removes duplicates |
| **INTERSECT ALL**| Items in A AND B | | Keeps duplicates (Min of counts) |
| **EXCEPT** | In A but NOT B | Exclusive guests | Removes duplicates |
| **EXCEPT ALL** | In A but NOT B | | Keeps duplicates (Count A - Count B) |

---

## 3.6 Null Values

> [!INFO] Definition
> NULL represents **unknown** or **missing** data. It is *not* zero and *not* an empty string.

### Logic with NULL
*   **Arithmetic:** `5 + NULL = NULL`
*   **Comparison:** `5 > NULL` yields **UNKNOWN**.
*   **Three-Valued Logic:** TRUE, FALSE, UNKNOWN.
    *   `OR`: (Unknown OR True) = True. (Unknown OR False) = Unknown.
    *   `AND`: (True AND Unknown) = Unknown. (False AND Unknown) = False.
    *   `NOT`: (NOT Unknown) = Unknown.

### Testing for NULL
*   **Wrong:** `where salary = NULL`
*   **Correct:** `where salary IS NULL`

---

## 3.7 Aggregate Functions

Functions that take a collection of values and return a single value.

1.  `AVG()`: Average (Input must be numeric).
2.  `SUM()`: Total (Input must be numeric).
3.  `MIN()`: Minimum.
4.  `MAX()`: Maximum.
5.  `COUNT()`: Number of values.

### Important Rules
*   **NULL Handling:** All aggregates **ignore** NULLs, except `COUNT(*)`.
*   **Empty Sets:** `COUNT` returns 0; others return NULL.
*   **Distinct:** `COUNT(DISTINCT ID)` counts unique values.

### Grouping (`GROUP BY` & `HAVING`)
*   **GROUP BY:** Aggregates data per group.
    *   *Rule:* Attributes in `SELECT` must be either grouped or aggregated.
*   **HAVING:** Filters **groups** (applied *after* aggregation).
    *   *Rule:* Attributes in `HAVING` must be grouped or aggregated.

> [!TIP] Query Processing Order
> 1. `FROM` (Get tables)
> 2. `WHERE` (Filter rows)
> 3. `GROUP BY` (Make groups)
> 4. `HAVING` (Filter groups)
> 5. `SELECT` (Return columns/aggregates)

---

## 3.8 Nested Subqueries

Subqueries can be nested in `WHERE`, `FROM`, `SELECT`, and `HAVING`.

### 1. Set Membership (`IN`, `NOT IN`)
Checks if a value exists in a set generated by a subquery.
```sql
-- Courses in Fall 2017 AND Spring 2018
select course_id from section where ...
AND course_id IN (select course_id from section where ...);
```

### 2. Set Comparison (`SOME`, `ALL`)
*   **> SOME:** Greater than at least one value (Equivalent to `> MIN`).
*   **> ALL:** Greater than all values (Equivalent to `> MAX`).
*   **<> ALL:** Equivalent to `NOT IN`.

### 3. Existence (`EXISTS`, `NOT EXISTS`)
Checks if the subquery returns *any* rows.
*   Often used with **Correlated Subqueries** (inner query references outer query variables).
*   `NOT EXISTS` (A except B) can be used to check for set containment (subset/superset).

### 4. Uniqueness (`UNIQUE`)
Checks if the subquery contains duplicate tuples (returns TRUE if no duplicates).

### 5. Subqueries in FROM Clause
Creates a temporary, derived table.
```sql
select ... from (select avg(salary) ... ) as dept_avg ...
```
*   *Note:* In MySQL/PostgreSQL, derived tables **must** be named (aliased).

### 6. The `WITH` Clause
Defines a temporary relation (Common Table Expression - CTE) valid only for the query. Improves readability.
```sql
WITH max_budget(value) AS (
    SELECT MAX(budget) FROM department
)
SELECT ... FROM department, max_budget ...
```

### 7. Scalar Subqueries
Subqueries that return exactly **one row and one column**. Can be used wherever a value is valid (e.g., in `SELECT` list, arithmetic expressions).

---

## 3.9 Modification of the Database

### Deletion
*   `delete from table where P;`
*   > [!DANGER] Omitting WHERE
    > `delete from table;` deletes **all** rows in the table.

### Insertion
*   **Simple:** `insert into table values (v1, v2...);`
*   **Safe:** `insert into table (col1, col2) values (v1, v2);` (Order independent).
*   **From Query:** `insert into table select ...`
    *   *Infinite Loop Risk:* Inserting into a table while selecting from it. SQL ensures select completes before insert starts.

### Updates
*   `update table set col = new_value where P;`
*   **CASE Statement:** Useful for conditional updates to avoid order-of-execution errors.
    ```sql
    update instructor
    set salary = case
        when salary <= 100000 then salary * 1.05
        else salary * 1.03
    end;
    ```
*   **Handling Nulls in Updates:** Use `COALESCE(value, 0)` to convert NULLs to a usable value (like 0) during calculation.