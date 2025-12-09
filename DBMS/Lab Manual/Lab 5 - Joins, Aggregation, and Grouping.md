---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF on Google Classroom
---
---

## 1. Sample Database Schema

To demonstrate Joins and Aggregation, the lab uses three tables: **Department**, **Employee**, and **Project**.

### Tables
| Table | Columns | Notes |
| :--- | :--- | :--- |
| **Department** | `dept_id` (PK), `dept_name`, `location` | Stores department details. |
| **Employee** | `emp_id` (PK), `name`, `salary`, `dept_id` (FK) | References Department. |
| **Project** | `proj_id` (PK), `proj_name`, `dept_id` (FK) | References Department. |

### Database Setup Code
Run this SQL block to initialize the environment for Lab V.

```sql
-- 1. Clean up existing tables
DROP TABLE IF EXISTS Project CASCADE;
DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Department CASCADE;

-- 2. Create Department Table
CREATE TABLE Department (
    dept_id VARCHAR(5),
    dept_name VARCHAR(20),
    location VARCHAR(50),
    CONSTRAINT pk_department PRIMARY KEY (dept_id)
);

-- 3. Create Employee Table
CREATE TABLE Employee (
    emp_id VARCHAR(5),
    name VARCHAR(30),
    salary NUMERIC(10, 2),
    dept_id VARCHAR(5),
    CONSTRAINT pk_employee PRIMARY KEY (emp_id),
    CONSTRAINT fk_emp_dept FOREIGN KEY (dept_id) 
        REFERENCES Department(dept_id) 
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- 4. Create Project Table
CREATE TABLE Project (
    proj_id VARCHAR(5),
    proj_name VARCHAR(50),
    dept_id VARCHAR(5),
    CONSTRAINT pk_project PRIMARY KEY (proj_id),
    CONSTRAINT fk_proj_dept FOREIGN KEY (dept_id) 
        REFERENCES Department(dept_id) 
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- 5. Insert Data
INSERT INTO Department VALUES 
('D01', 'CSE', 'Building A'), 
('D02', 'EEE', 'Building B'), 
('D03', 'BBA', 'Building C');

INSERT INTO Employee VALUES 
('E101', 'Alice', 50000, 'D01'),
('E102', 'Bob', 60000, 'D01'),
('E103', 'Charlie', 55000, 'D02'),
('E104', 'David', 45000, 'D03'),
('E105', 'Eve', 70000, 'D01');

INSERT INTO Project VALUES 
('P01', 'AI Research', 'D01'),
('P02', 'Circuit Design', 'D02'),
('P03', 'Web Dev', 'D01');
```

---

## 2. SQL Joins

Joins combine rows from two or more tables based on a related column.

### 2.1 INNER JOIN
Returns records that have matching values in **both** tables.

```sql
SELECT E.name, D.dept_name, D.location
FROM Employee E
INNER JOIN Department D ON E.dept_id = D.dept_id;
```

### 2.2 LEFT JOIN (Left Outer Join)
Returns **all** records from the left table, and the matched records from the right table.
> [!NOTE] 
> If there is no match, the right side will contain `NULL`.

**Query:** Show all Departments and their associated Projects (if any).
```sql
SELECT D.dept_id, D.dept_name, P.proj_name
FROM Department D
LEFT JOIN Project P ON D.dept_id = P.dept_id;
```
*Result:* Department `D03` (BBA) has no project, so `proj_name` returns `NULL`.

### 2.3 RIGHT JOIN (Right Outer Join)
Returns **all** records from the right table, and the matched records from the left table.

```sql
SELECT P.proj_name, D.dept_name
FROM Project P
RIGHT JOIN Department D ON P.dept_id = D.dept_id;
```

### 2.4 FULL OUTER JOIN
Returns all records when there is a match in **either** left or right table.

**Query:** Match Employees to Projects based on Department ID.
```sql
SELECT E.name, P.proj_name
FROM Employee E
FULL OUTER JOIN Project P ON E.dept_id = P.dept_id;
```
*Result:* Returns rows where employees exist, projects exist, or where one exists without the other (showing `NULL`).

### 2.5 CROSS JOIN
Produces a **Cartesian product**. Every row of Table 1 is combined with every row of Table 2.
*Calculation:* 3 Depts × 3 Projects = 9 Rows.

```sql
SELECT D.dept_name, P.proj_name
FROM Department D
CROSS JOIN Project P;
```

### 2.6 NATURAL JOIN
Creates an **implicit** join based on all columns in the two tables that have the **same name and data type** (e.g., `dept_id`).
> [!TIP]
> Explicit `ON` clauses are not required here.

```sql
SELECT name, dept_name, location
FROM Employee
NATURAL JOIN Department;
```

---

## 3. Aggregate Functions

Used to perform calculations on a set of values to return a single scalar value.

| Function | Description |
| :--- | :--- |
| `COUNT(*)` | Count total rows |
| `SUM()` | Summation of values |
| `AVG()` | Average of values |
| `MIN()` | Minimum value |
| `MAX()` | Maximum value |

**Example Query:**
```sql
SELECT 
    COUNT(*) AS total_staff,
    SUM(salary) AS total_cost,
    AVG(salary) AS avg_pay,
    MIN(salary) AS min_pay,
    MAX(salary) AS max_pay
FROM Employee;
```

---

## 4. Grouping Data (GROUP BY)

Groups rows that have the same values into summary rows.

### 4.1 GROUP BY with Aggregate
**Query:** Count the number of employees in each department.
```sql
SELECT dept_id, COUNT(*) AS emp_count
FROM Employee
GROUP BY dept_id;
```

### 4.2 GROUP BY with JOIN
**Query:** Find the total salary expense per Department Name.
```sql
SELECT D.dept_name, SUM(E.salary) AS total_salary
FROM Department D
JOIN Employee E ON D.dept_id = E.dept_id
GROUP BY D.dept_name;
```

---

## 5. Filtering Groups (HAVING)

The `HAVING` clause filters groups **after** the aggregation has occurred.

> [!important] Difference between WHERE and HAVING
> * `WHERE`: Filters rows **before** grouping.
> * `HAVING`: Filters groups **after** grouping.

**Query:** Find departments where the **average salary** is greater than 50,000.
```sql
SELECT dept_id, AVG(salary) AS avg_sal
FROM Employee
GROUP BY dept_id
HAVING AVG(salary) > 50000;
```
*Result:* Department `D03` is excluded because its average (45,000) is not > 50,000.