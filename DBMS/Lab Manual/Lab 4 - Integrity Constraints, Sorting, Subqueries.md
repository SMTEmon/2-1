--- 
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab IV: Integrity Constraints, Sorting, Subqueries

## 1. Integrity Constraints

### 1.1 Primary Key
Uniquely identifies each row. Cannot be NULL.
```sql
CONSTRAINT pk_dept PRIMARY KEY (dept_id)
```

### 1.2 Foreign Key
Enforces referential integrity.
```sql
CONSTRAINT fk_emp_dept FOREIGN KEY (dept_id) 
REFERENCES Department(dept_id)
ON DELETE CASCADE ON UPDATE CASCADE
```
*   `ON DELETE CASCADE`: If parent is deleted, child rows are also deleted.

---

## 2. Data Sorting (ORDER BY)
Sorts result set.
*   `ASC` (Default) / `DESC`
*   **Multiple Columns:** `ORDER BY col1 ASC, col2 DESC` (Sorts by col1, then ties broken by col2).

---

## 3. Intermediate SQL: Subqueries
Query within a query.

### 3.1 Single-Row Subqueries
Returns one value. Used with `=`, `>`, `<`, etc.
*   *Example:* Employees earning more than average.
    `WHERE salary > (SELECT AVG(salary) FROM ...)`

### 3.2 Multiple-Row Subqueries
Returns >1 row. Used with `IN`, `ANY`, `ALL`.
*   *Example:* Employees in departments located in 'Building A'.
    `WHERE dept_id IN (SELECT dept_id ...)`

### 3.3 Nested Subqueries
Subqueries inside subqueries.
*   *Logic:* Find project's dept $ightarrow$ Find dept in Employee.

### 3.4 Correlated Subqueries
Depends on the outer query. Executed once for **each row** of the outer query.
*   *Example:* Salary > Average of *their specific* department.
    ```sql
    WHERE e1.salary > (SELECT AVG(salary) FROM Employee e2 WHERE e2.dept_id = e1.dept_id)
    ```

---

## 4. Range and Limit

### 4.1 Range Operators
*   `BETWEEN x AND y`: Inclusive range.
*   `DISTINCT`: Returns unique values.

### 4.2 LIMIT
*   Restricts number of rows returned. Useful for pagination or "Top N" queries.
    `LIMIT 3`

```