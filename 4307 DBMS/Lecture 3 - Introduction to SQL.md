
*Date: December 19, 2025*
*Course: CSE 4307: Database Management Systems*
*Lecturer: Md. Tariquzzaman*

---

## 3.1 Overview of the SQL Query Language

SQL (Structured Query Language) is the standard language for relational database management systems. It's composed of several sub-languages.

-   **Data Manipulation Language (DML)**: The "hands" that work with the data.
    -   `SELECT`: To query (search or read) data.
    -   `INSERT`: To add new data.
    -   `UPDATE`: To change existing data.
    -   `DELETE`: To remove data.
-   **Data Definition Language (DDL)**: The "architect's blueprint" for the database structure.
    -   `CREATE`: To build new tables, views, and other database objects.
    -   `ALTER`: To modify the structure of existing objects.
    -   `DROP`: To delete objects.
-   **Transaction Control Language (TCL)**: Manages transactions to ensure data integrity.
    -   `BEGIN`: To start a transaction.
    -   `COMMIT`: To save the changes of a transaction.
    -   `ROLLBACK`: To undo the changes of a transaction.
-   **Data Control Language (DCL)**: Defines "who can do what" through authorization and permissions.
    -   `GRANT`: To give user permissions.
    -   `REVOKE`: To take user permissions away.

---

## 3.2 SQL Data Definition (DDL)

DDL is used to define, create, and manage the structure of database objects, primarily tables.

### 3.2.1 Domain Types (Data Types)

These are SQL's building blocks, defining the kind of data each column can hold.

| Data Type                                      | Description                                                                                                  | Example                                  |     |
| ---------------------------------------------- | ------------------------------------------------------------------------------------------------------------ | ---------------------------------------- | --- |
| `char(n)`                                      | **Fixed-length** character string. Always uses `n` bytes of storage. Shorter strings are padded with spaces. | `char(10)` storing "Avi" becomes "Avi "  |     |
| `varchar(n)`                                   | **Variable-length** character string up to `n` characters. Stores only the actual text length.               | `varchar(10)` storing "Avi" uses 3 chars |     |
| `int` or `integer`                             | Integer values. The range depends on the database system.                                                    | `12345`                                  |     |
| `smallint`                                     | A smaller integer, uses less storage. Efficient for smaller numeric values.                                  | `123`                                    |     |
| `numeric(p, d)<br>` or,<br>`decimal(p,d) <br>` | Fixed-point number with `p` total digits and `d` digits after the decimal point. Exact value.                | `numeric(5, 2)` can hold `123.45`        |     |
| `real`, `double precision`                     | Floating-point numbers. These are approximations and can have rounding errors.                               | `123.45678`                              |     |
| `float(n)`                                     | Floating-point number with at least `n` digits of precision.                                                 | `float(8)`                               |     |

> **Pro Tip**: Use `varchar` instead of `char` in most cases to save space and avoid issues with trailing spaces during string comparison. For multilingual data (like names in different languages), use `nvarchar` if your database supports it.

### 3.2.2 Basic Schema Definition (`CREATE TABLE`)

The `CREATE TABLE` command defines a new relation (table).

**General Form**:

```sql
CREATE TABLE table_name (
    attribute_1 data_type_1 <constraint_1>,
    attribute_2 data_type_2 <constraint_2>,
    ...
    <table_constraint_1>,
    <table_constraint_2>
);
```

**Integrity Constraints**:

-   **`PRIMARY KEY`**: Ensures each record is unique and not null. A table can have only one primary key.
-   **`FOREIGN KEY`**: Links one table to another, ensuring referential integrity. The values in the foreign key column must exist in the primary key column of the referenced table.
-   **`NOT NULL`**: Prevents a column from having missing (`NULL`) values.

**Example**: Creating `instructor` and `department` tables.

```sql
CREATE TABLE department (
    dept_name VARCHAR(20),
    building VARCHAR(15),
    budget NUMERIC(12, 2),
    PRIMARY KEY (dept_name)
);

CREATE TABLE instructor (
    ID CHAR(5),
    name VARCHAR(20) NOT NULL,
    dept_name VARCHAR(20),
    salary NUMERIC(8, 2),
    PRIMARY KEY (ID),
    FOREIGN KEY (dept_name) REFERENCES department(dept_name)
);


ALTER TABLE instructor 
ADD COLUMN bonus NUMERIC(4,2) DEFAULT 0;

ALTER TABLE instructor
ALTER COLUMN salary TYPE NUMERIC(9,1);

ALTER TABLE instructor
RENAME COLUMN dept_name TO department;

ALTER TABLE instructor
RENAME TO instructor;

ALTER TABLE instructor
DROP COLUMN bonus;

DROP TABLE instructor;
```

### 3.2.3 Modifying and Deleting Tables

-   **`INSERT`**: Add a new row.
    ```sql
    INSERT INTO instructor VALUES ('10211', 'Smith', 'Biology', 66000);
    ```
-   **`DELETE FROM`**: Remove rows from a table. **Warning**: Without a `WHERE` clause, it deletes **all** rows.
    ```sql
    DELETE FROM student WHERE name = 'Smith';
    ```
-   **`DROP TABLE`**: Removes the entire table structure (schema) and all its data. This action is irreversible.
    ```sql
    DROP TABLE student;
    ```
-   **`ALTER TABLE`**: Modifies a table's structure.
    ```sql
    -- Adds a new column (existing rows will have NULL for this column)
    ALTER TABLE instructor ADD phone_number VARCHAR(15);

    -- Removes a column
    ALTER TABLE instructor DROP COLUMN phone_number;
    ```

---

## 3.3 Basic Structure of SQL Queries

A typical SQL query has the form `SELECT... FROM... WHERE...`.

-   **`SELECT`**: Lists the attributes (columns) to be returned. (Relational Algebra: Projection π)
-   **`FROM`**: Lists the relations (tables) involved in the query. (Relational Algebra: Cartesian Product ×)
-   **`WHERE`**: Specifies conditions to filter the results. (Relational Algebra: Selection σ)

**Logical Order of Operations**: `FROM` -> `WHERE` -> `SELECT`.

### The `SELECT` Clause

-   Use `*` to denote "all attributes".
    ```sql
    SELECT * FROM instructor;
    ```
-   Use `DISTINCT` to eliminate duplicate rows from the result. `ALL` is the default.
    ```sql
    -- Find the department names of all instructors, and remove duplicates
    SELECT DISTINCT dept_name FROM instructor;
    ```
-   Can contain arithmetic expressions (`+`, `-`, `*`, `/`) or literals.
-   Use the `AS` clause to rename attributes for clarity, especially for expressions.
    ```sql
    SELECT ID, name, salary/12 AS monthly_salary FROM instructor;
    ```

### The `WHERE` Clause

-   Filters rows based on a specified condition (predicate).
-   Allows logical connectives `AND`, `OR`, `NOT`.
-   Supports comparison operators: `<`, `<=`, `>`, `>=`, `=`, `<>`.

```sql
-- Find all instructors in the Computer Science department with a salary > 70000
SELECT name
FROM instructor
WHERE dept_name = 'Comp. Sci.' AND salary > 70000;
```

### The `FROM` Clause and Joins

-   When multiple tables are listed, a **Cartesian Product** is formed.
-   A `WHERE` clause is then used to specify the join condition, filtering out meaningless combinations.

```sql
-- Old syntax for a join (less readable)
SELECT name, course_id
FROM instructor, teaches
WHERE instructor.ID = teaches.ID;
```

> **Best Practice**: Always use the explicit `JOIN` syntax (`INNER JOIN`, `LEFT JOIN`, etc.) instead of the old comma-separated `FROM` clause. It is more readable and less prone to errors. This is covered in Lecture 4.

---

## 3.4 Additional Basic Operations

### 3.4.1 The Rename Operation (`AS`)

The `AS` clause is used to rename relations (table aliases) and attributes (column aliases).

-   **Why Rename?**
    1.  **Clarity**: Give meaningful names to computed columns (`salary/12 AS monthly_salary`).
    2.  **Brevity**: Create short aliases for long table names (`instructor AS i`).
    3.  **Self-Joins**: Disambiguate when a table is joined with itself.

-   **Relation Alias Example**:
    ```sql
    -- 'T' and 'S' are aliases for the instructor and teaches tables
    SELECT T.name, S.course_id
    FROM instructor AS T, teaches AS S
    WHERE T.ID = S.ID;
    ```
    *The `AS` keyword is optional for table aliases.*

### 3.4.2 String Operations

-   Strings are enclosed in single quotes: `'Computer'`.
-   To include a single quote within a string, double it: `'It''s right'`.
-   **Pattern Matching with `LIKE`**:
    -   `%`: Matches any substring (zero or more characters).
    -   `_`: Matches any single character.
    -   `ESCAPE`: Used to search for the literal `%` or `_` characters.
        `LIKE 'ab%cd%' ESCAPE '\'` matches the literal string `ab%cd`.

-   **`LIKE` Examples**:
    -   `'Intro%'`: Matches `'Intro to CS'`.
    -   `'%Comp%'`: Matches `'Intro to Computer'` and `'Computational Bio'`.
    -   `'___'`: Matches any 3-character string.
    -   `'CS-1__ '`: Matches 100-level CS courses like `'CS-101'`.

-   **Other String Functions**: `||` (concatenation), `UPPER()`, `LOWER()`, `TRIM()`. *Note: Functions can vary by database system.*

### 3.4.3 Ordering the Display of Tuples (`ORDER BY`)

-   Sorts the result set based on one or more columns.
-   `ASC`: Ascending order (default).
-   `DESC`: Descending order.
-   The `ORDER BY` clause is executed **last** in a query.

```sql
-- Primary sort by salary (descending), secondary sort by name (ascending)
SELECT name, dept_name, salary
FROM instructor
ORDER BY salary DESC, name ASC;
```

### 3.4.4 `BETWEEN` Operator

-   A shorthand for a range check, inclusive of the endpoints.

```sql
-- Using BETWEEN
SELECT name FROM instructor WHERE salary BETWEEN 90000 AND 100000;

-- Equivalent to:
SELECT name FROM instructor WHERE salary >= 90000 AND salary <= 100000;
```

---

## 3.5 Set Operations

Set operations combine the results of two compatible queries into a single result set.

-   `UNION`: Combines results and **removes duplicates**.
-   `UNION ALL`: Combines results and **keeps all duplicates**.
-   `INTERSECT`: Returns only rows that appear in **both** query results, removing duplicates.
-   `INTERSECT ALL`: Returns common rows, keeping the minimum number of duplicate occurrences from both sides.
-   `EXCEPT`: Returns rows from the first query that are **not** in the second query, removing duplicates.
-   `EXCEPT ALL`: Performs set difference while tracking duplicates.

**Example**: Find courses taught in Fall 2017 or Spring 2018.
```sql
(SELECT course_id FROM section WHERE semester = 'Fall' AND year = 2017)
UNION
(SELECT course_id FROM section WHERE semester = 'Spring' AND year = 2018);
```
> `UNION ALL` is faster than `UNION` because it doesn't need to check for and remove duplicates. Use it if you know there are no duplicates or if duplicates are acceptable.

---

## 3.6 Null Values

-   **What is `NULL`?**: It represents **unknown** or **missing** data. It is not zero (`0`) or an empty string (`''`).
-   **Arithmetic**: Any arithmetic operation with `NULL` produces `NULL` (e.g., `5 + NULL` is `NULL`).
-   **Comparisons**: Comparisons with `NULL` yield a third logical value: `UNKNOWN`.
    -   The `WHERE` clause only includes rows that evaluate to `TRUE`. `FALSE` and `UNKNOWN` are excluded.
-   **Testing for `NULL`**: You cannot use `= NULL`. You must use `IS NULL` or `IS NOT NULL`.
    -   **Wrong**: `WHERE salary = NULL` (This will never be true).
    -   **Correct**: `WHERE salary IS NULL`.

-   **Three-Valued Logic**:
    -   `TRUE AND UNKNOWN` -> `UNKNOWN`
    -   `FALSE AND UNKNOWN` -> `FALSE`
    -   `TRUE OR UNKNOWN` -> `TRUE`
    -   `FALSE OR UNKNOWN` -> `UNKNOWN`
    -   `NOT UNKNOWN` -> `UNKNOWN`

---

## 3.7 Aggregate Functions

Aggregate functions take a collection of values as input and return a single value as output.

-   **`AVG()`**: Average value.
-   **`MIN()`**: Minimum value.
-   **`MAX()`**: Maximum value.
-   **`SUM()`**: Total sum.
-   **`COUNT()`**: Number of values.

**NULL Handling**: All aggregate functions except `COUNT(*)` ignore `NULL` values.
-   `COUNT(salary)`: Counts only the rows where `salary` is not `NULL`.
-   `COUNT(*)`: Counts all rows in the group, regardless of `NULL`s.
-   `AVG(salary)`: `SUM(salary) / COUNT(salary)`. Since both ignore `NULL`s, the average is calculated correctly over the known values.

### `GROUP BY` Clause

-   Divides the table into groups based on specified attributes.
-   Computes an aggregate function for each group separately.
-   Returns one result row per group.

**Core Rule**: When using `GROUP BY`, every attribute in the `SELECT` clause must be either:
1.  Listed in the `GROUP BY` clause, **OR**
2.  Wrapped inside an aggregate function.

**Wrong Query**:
```sql
/* Error: ID is not grouped or aggregated */
SELECT dept_name, ID FROM instructor GROUP BY dept_name;
```
*Why is this wrong? After grouping by `dept_name`, a single department group (e.g., 'Comp. Sci.') contains multiple instructors with different `ID`s. SQL doesn't know which `ID` to show for the group.*

**Correct Query**:
```sql
-- Find the average salary for each department
SELECT dept_name, AVG(salary)
FROM instructor
GROUP BY dept_name;
```

### `HAVING` Clause

-   Filters **groups** after they have been formed by `GROUP BY`.
-   `WHERE` filters individual **rows** *before* grouping.

| Clause  | Filters...      | When it's applied    | Can use aggregates? |
| ------- | --------------- | -------------------- | ------------------- |
| `WHERE` | Individual Rows | Before `GROUP BY`    | No                  |
| `HAVING`| Groups          | After `GROUP BY`     | Yes                 |

**Example**: Find departments with an average salary greater than $42,000.
```sql
SELECT dept_name, AVG(salary) AS avg_salary
FROM instructor
GROUP BY dept_name
HAVING AVG(salary) > 42000;
```

### SQL Query Processing Order (Logical)
1.  **`FROM`**: Assembles the initial set of data (including joins).
2.  **`WHERE`**: Filters individual rows.
3.  **`GROUP BY`**: Arranges the filtered rows into groups.
4.  **`HAVING`**: Filters entire groups.
5.  **`SELECT`**: Computes expressions and determines the final columns.
6.  **`ORDER BY`**: Sorts the final result set.
7.  **`LIMIT` / `OFFSET`**: Paginates the sorted result set.

---

## 3.8 Nested Subqueries

A **subquery** is a `SELECT` statement nested inside another query.

-   **Uncorrelated**: The inner query runs once and produces a result that the outer query uses.
-   **Correlated**: The inner query runs once for each row of the outer query, using values from the outer query's current row.

### Subqueries in the `WHERE` Clause

-   **`IN` / `NOT IN` (Set Membership)**: Checks if a value is in the set produced by a subquery.
    ```sql
    -- Find courses taught in Fall 2017 but NOT in Spring 2018
    SELECT DISTINCT course_id
    FROM section
    WHERE semester = 'Fall' AND year = 2017 AND course_id NOT IN (
        SELECT course_id FROM section WHERE semester = 'Spring' AND year = 2018
    );
    ```
-   **`SOME` / `ALL` (Set Comparison)**:
    -   `> SOME`: Greater than at least one value in the set (i.e., greater than the minimum).
    -   `> ALL`: Greater than every value in the set (i.e., greater than the maximum).
    -   *Note: `= SOME` is identical to `IN`.*
-   **`EXISTS` (Test for Empty Relations)**: Returns `TRUE` if the subquery returns one or more rows. Often used with correlated subqueries.
    ```sql
    -- Find courses taught in BOTH Fall 2017 and Spring 2018 (correlated subquery)
    SELECT course_id
    FROM section S
    WHERE S.semester = 'Fall' AND S.year = 2017 AND EXISTS (
        SELECT * FROM section T
        WHERE T.semester = 'Spring' AND T.year = 2018 AND S.course_id = T.course_id
    );
    ```
-   **`UNIQUE` (Test for Duplicates)**: Returns `TRUE` if the subquery has no duplicate tuples. An empty set is considered unique.

### Subqueries in the `FROM` Clause

-   The subquery creates a temporary table (a **derived table**) that the outer query can select from.
-   Most database systems require you to give this temporary table an alias.

```sql
-- Find departments with an average salary > 42000 (alternative to HAVING)
SELECT dept_name, avg_salary
FROM (
    SELECT dept_name, AVG(salary) AS avg_salary
    FROM instructor
    GROUP BY dept_name
) AS dept_averages -- Alias is required
WHERE avg_salary > 42000;
```

### The `WITH` Clause (Common Table Expressions - CTEs)

-   Creates one or more named temporary tables that exist only for the duration of the query.
-   Breaks complex logic into small, readable steps. Much easier to read than deeply nested subqueries.

```sql
WITH
  -- Step 1: Create a temp table of departmental salary sums
  dept_total(dept_name, total_salary) AS (
    SELECT dept_name, SUM(salary)
    FROM instructor
    GROUP BY dept_name
  ),
  -- Step 2: Create a temp table with the overall average of those sums
  avg_total(avg_value) AS (
    SELECT AVG(total_salary)
    FROM dept_total
  )
-- Final Query: Compare the sum of each dept to the overall average
SELECT dept_name
FROM dept_total, avg_total
WHERE dept_total.total_salary > avg_total.avg_value;
```

### Scalar Subqueries

-   A subquery that returns exactly **one value** (one row, one column).
-   Can be used almost anywhere a single value is expected (in `SELECT`, `WHERE`, `HAVING`).
-   Causes a runtime error if it returns more than one row.

```sql
-- List departments with their instructor count (scalar subquery in SELECT)
SELECT
    dept_name,
    (SELECT COUNT(*) FROM instructor WHERE department.dept_name = instructor.dept_name) AS num_instructors
FROM department;
```

---

## 3.9 Modification of the Database

### `DELETE`

-   Deletes whole tuples (rows).
-   The subquery is evaluated **once** before any deletions occur.
    ```sql
    -- Delete instructors with a salary below the average
    DELETE FROM instructor
    WHERE salary < (SELECT AVG(salary) FROM instructor);
    ```

### `INSERT`

-   **Positional**: `INSERT INTO course VALUES ('CS-437', 'DB Systems', ...)` (Dangerous if schema changes).
-   **Named Attributes**: `INSERT INTO course(course_id, title, ...) VALUES ('CS-437', ...)` (Safer).
-   **From a Query**: Insert the result of a `SELECT` statement. The `SELECT` is fully evaluated before insertion begins.
    ```sql
    INSERT INTO instructor
    SELECT ID, name, dept_name, 18000
    FROM student
    WHERE dept_name = 'Music' AND tot_cred > 144;
    ```

### `UPDATE`

-   Modifies attributes of existing tuples.
-   Use a `CASE` statement for conditional updates to avoid the "order problem" where one update affects rows that a subsequent update also targets.

**`CASE` statement for safe updates**:
```sql
-- Give a 3% raise to salaries > 100k and a 5% raise to others
UPDATE instructor
SET salary = CASE
    WHEN salary <= 100000 THEN salary * 1.05
    ELSE salary * 1.03
END;
```

**Handling `NULL`s from Aggregates**: If a subquery aggregate (like `SUM`) can return `NULL` (e.g., for a student who has taken no courses), it can cause an update to fail or set a value to `NULL`. Use `COALESCE` or `CASE` to handle this.

```sql
-- Coalesce returns the first non-null value in its argument list
UPDATE student S
SET tot_cred = (
    SELECT COALESCE(SUM(credits), 0)
    FROM takes
    WHERE takes.ID = S.ID
);
```