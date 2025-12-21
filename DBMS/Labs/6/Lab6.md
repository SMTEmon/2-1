# Lab 6: Views, Roles, String, Sets & Dates

**Course:** CSE 4308: DATABASE MANAGEMENT SYSTEMS LAB  
**Academic Year:** 2024-2025  
**Prepared by:** Md. Tariquzzaman

---

## 1. Introduction
This lab module demonstrates advanced data manipulation techniques in PostgreSQL, covering:
- Character string processing for data cleaning.
- Temporal operations for date logic.
- Set-theoretic operators for combining datasets.
- Data Control Language (DCL) for security management.

## 2. Lab Environment Setup

### 2.1 DDL and Data Insertion
```sql
-- 1. AcademicStaff Table
CREATE TABLE AcademicStaff (
    id SERIAL PRIMARY KEY,
    full_name VARCHAR(100),
    email_addr VARCHAR(100),
    joining_date DATE
);

INSERT INTO AcademicStaff (id, full_name, email_addr, joining_date) VALUES
(101, 'ALICE munn', 'alice.m@university.edu', '2018-01-15'),
(102, 'bob roberts', 'bob.roberts@gmail.com', '2019-11-20'),
(103, 'Dr. chaRLie', 'charlie.c@yahoo.com', '2020-03-10'),
(104, 'DAVID smith', 'david.s@university.edu', '2021-07-01'),
(105, 'eve O''Connor', 'eve.oconnor@outlook.com', '2022-02-14'),
(106, 'frank LIN', 'frank.lin@protonmail.com', '2023-08-30'),
(107, 'Grace HOPPER', 'g.hopper@cs.edu', '2024-01-05'),
(108, 'helen keller', 'helen.k@org.net', '2024-09-12');

-- 2. SystemLogs Table
CREATE TABLE SystemLogs (
    log_id INT PRIMARY KEY,
    raw_entry TEXT
);

INSERT INTO SystemLogs (log_id, raw_entry) VALUES
(1, ' System_Start '),
(2, '##CRITICAL_ERROR##'),
(3, 'User_Login_Success'),
(4, ' WARN: Low_Memory '),
(5, '__Connection_Timeout__');

-- 3. Course Enrollment Tables
CREATE TABLE Course_Alpha (student_id INT);
CREATE TABLE Course_Beta (student_id INT);

INSERT INTO Course_Alpha (student_id) VALUES
(1001), (1002), (1003), (1004), (1005);
INSERT INTO Course_Beta (student_id) VALUES
(1004), (1005), (1006), (1007), (1008);
```

---

## 3. Scalar Functions: String Processing

### 3.1 Case Conversion
- `UPPER(str)` / `LOWER(str)`: Converts entire string case.
- `INITCAP(str)`: Capitalizes the first letter of each word (Title Case).

```sql
SELECT
    full_name AS original,
    UPPER(full_name) AS upper_case,
    INITCAP(full_name) AS normalized_case
FROM AcademicStaff
WHERE id <= 104;
```

### 3.2 String Sanitization (TRIM)
- `TRIM([BOTH|LEADING|TRAILING] 'char' FROM str)`: Removes unwanted characters or whitespace.

```sql
SELECT
    raw_entry,
    TRIM(raw_entry) AS standard_trim,
    TRIM(BOTH '#' FROM raw_entry) AS hash_removal
FROM SystemLogs
WHERE log_id IN (1, 2, 4);
```

### 3.3 Substring Extraction & Pattern Matching
- `SUBSTR(str, start, length)`: Extracts segment starting at index `start`.
- `LEFT(str, n)` / `RIGHT(str, n)`: Takes `n` characters from ends.
- `POSITION(substring IN string)`: Returns the index of a character.

```sql
-- Dynamic Domain Extraction
SELECT
    email_addr,
    POSITION('@' IN email_addr) as at_symbol_index,
    SUBSTR(email_addr, POSITION('@' IN email_addr) + 1) AS domain_only
FROM AcademicStaff
WHERE id BETWEEN 101 AND 103;
```

### 3.4 Pattern Replacement
- `REPLACE(raw_entry, '_', ' ')`: Replaces occurrences of a pattern with another.

```sql
SELECT
    raw_entry,
    REPLACE(raw_entry, '_', ' ') AS clean_text
FROM SystemLogs
WHERE log_id = 3;
```

---

## 4. Temporal Data Management

### 4.1 Intervals and Aging
- `AGE(timestamp1, timestamp2)`: Calculates the symbolic difference between two dates.

```sql
SELECT
    INITCAP(full_name) AS name,
    AGE('2025-01-01', joining_date) AS tenure
FROM AcademicStaff
WHERE id >= 106;
```

### 4.2 Field Extraction (EXTRACT)
- `EXTRACT(field FROM source)`: Retrieves sub-fields (Year, Month, Day, Quarter, etc.).

```sql
SELECT
    joining_date,
    EXTRACT(YEAR FROM joining_date) AS join_year,
    EXTRACT(QUARTER FROM joining_date) AS fiscal_qtr
FROM AcademicStaff
WHERE id <= 104;
```

---

## 5. Relational Set Operators
Rules: Union Compatibility (same columns) and Type Compatibility.

### 5.1 UNION vs UNION ALL
- `UNION`: Combines sets and **removes duplicates** (Logical OR).
- `UNION ALL`: Combines sets and **keeps duplicates** (Faster).

```sql
SELECT student_id FROM Course_Alpha
UNION
SELECT student_id FROM Course_Beta;
```

### 5.2 INTERSECT
- Returns only rows that appear in **BOTH** result sets (Logical AND).

```sql
SELECT student_id FROM Course_Alpha
INTERSECT
SELECT student_id FROM Course_Beta;
```

### 5.3 EXCEPT (Difference)
- Returns rows from the first query that are **NOT** present in the second (MINUS in Oracle).

```sql
SELECT student_id FROM Course_Alpha
EXCEPT
SELECT student_id FROM Course_Beta;
```

---

## 6. Database Views

### 6.1 Standard Views
A "virtual table" defined by a query.
```sql
CREATE VIEW View_PublicDirectory AS
SELECT
    INITCAP(full_name) AS display_name,
    email_addr
FROM AcademicStaff;
```

### 6.2 Updatable Views WITH CHECK OPTION

**The Concept:** `WITH CHECK OPTION` acts as a guard. It ensures that any data you `INSERT` or `UPDATE` through a view **must satisfy the view's `WHERE` clause**.

If you try to insert data that doesn't match the filter (e.g., a non-.edu email), the row would effectively "vanish" from the view immediately after insertion. The database blocks this to prevent confusion and data integrity issues.

#### Visual Breakdown & Code

**Step 1: The Rule Definition**
```sql
CREATE OR REPLACE VIEW View_Edu_Staff AS
SELECT id, full_name, email_addr
FROM AcademicStaff
WHERE email_addr LIKE '%edu'    -- <--- The Filter
WITH CHECK OPTION;              -- <--- The Guard
```

**Step 2: Action vs Result**

| Scenario | Query Input | Check: `%edu`? | Outcome |
| :--- | :--- | :--- | :--- |
| **Valid** | `'john@university.edu'` | **True** ✅ | **Allowed.** Row is added to base table. |
| **Invalid** | `'jane@gmail.com'` | **False** ❌ | **Blocked.** Error: `violates check option`. |

**Step 3: Implementation**
```sql
-- 1. Valid Insert (Succeeds)
-- Matches the '%edu' rule, so it passes through.
INSERT INTO View_Edu_Staff (full_name, email_addr)
VALUES ('John Doe', 'john.d@university.edu');

-- 2. Invalid Insert (Fails)
-- Does NOT match '%edu'. The view rejects it because it would "vanish".
INSERT INTO View_Edu_Staff (full_name, email_addr)
VALUES ('Jane Doe', 'jane.d@gmail.com');
```

### 6.3 Materialized Views
Physically saves the result to disk; requires manual refreshing.
```sql
CREATE MATERIALIZED VIEW MatView_StaffAnalysis AS
SELECT
    EXTRACT(YEAR FROM joining_date) as year,
    COUNT(*) as total_recruits
FROM AcademicStaff
GROUP BY EXTRACT(YEAR FROM joining_date);

-- Refreshing the view
REFRESH MATERIALIZED VIEW MatView_StaffAnalysis;
```

---

## 7. Data Control Language (DCL)

### 7.1 Role Management
```sql
CREATE ROLE alice_operator LOGIN PASSWORD 'securePass123';
CREATE ROLE faculty_group NOLOGIN;
```

### 7.2 Role Inheritance (RBAC)
```sql
GRANT SELECT, INSERT ON Course_Alpha TO faculty_group;
GRANT faculty_group TO alice_operator;
```

### 7.3 Column-Level Security
```sql
CREATE ROLE auditor NOLOGIN;
GRANT SELECT (log_id) ON SystemLogs TO auditor; -- Hides raw_entry
```

---

## 8. Lab Tasks

1.  **Extract Domain Name:** Extract the domain name from the email addresses. Use `POSITION` to find the '@' symbol and `SUBSTR` to get the text after it.
2.  **Enrolled in 2023:** Find the names of students who enrolled in the year 2023. Use `EXTRACT(YEAR ...)` in your `WHERE` clause.
3.  **Set Difference:** Find the Student IDs of those who are taking 'CS102' but are NOT taking 'CS101'.
4.  **Complex Filter:** Display the `full_name` of students and the `domain` of their email, but only for students who have visited the 'Server Room'.
5.  **Materialized View:** Create a Materialized View named `MatView_Enrollment_Stats` that counts how many students are in each course.
