---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab VI: Views, Roles, String, Sets and Dates

## 1. String Processing
Essential for Data Normalization (cleaning data).

### 1.1 Case Conversion
*   `UPPER(str)` / `LOWER(str)`: Convert entire string case.
*   `INITCAP(str)`: Title Case (Capitalizes first letter of each word).

### 1.2 String Sanitization (TRIM)
Removes unwanted characters (default whitespace).
*   `TRIM([BOTH|LEADING|TRAILING] 'char' FROM str)`

### 1.3 Substring & Pattern Matching
*   `SUBSTR(str, start, length)`: Extract segment.
*   `POSITION(substring IN string)`: Returns index of character.
    *   *Example:* extracting domain from email.

### 1.4 Pattern Replacement
*   `REPLACE(str, 'old', 'new')`: Replaces all occurrences.

---

## 2. Temporal Data Management

### 2.1 Intervals and Aging
*   `AGE('target_date', date_col)`: Calculates symbolic difference (e.g., "1 year 4 mons").

### 2.2 Field Extraction
*   `EXTRACT(field FROM source)`: Retrieves sub-fields (`YEAR`, `MONTH`, `QUARTER`, `WEEK`).
    *   *Usage:* Aggregation (e.g., Sales per Quarter).

---

## 3. Relational Set Operators
Combine result sets of two or more queries.
*   **Rules:** Union Compatibility (Same number of columns, compatible data types).

1.  **UNION vs UNION ALL**
    *   `UNION`: Combines sets, **removes duplicates** (Logical OR).
    *   `UNION ALL`: Combines sets, **keeps duplicates** (Faster).
2.  **INTERSECT**
    *   Returns rows appearing in **BOTH** sets (Logical AND).
3.  **EXCEPT** (Minus)
    *   Returns rows in the first query **NOT** present in the second.

---

## 4. Database Views
A "virtual table" defined by a query.

### 4.1 Standard Views
*   `CREATE VIEW view_name AS SELECT ...`
*   Hides sensitive columns or simplifies complex joins.

### 4.2 Updatable Views & WITH CHECK OPTION
*   Simple views (1:1 mapping, no aggregates) are automatically updatable.
*   `WITH CHECK OPTION`: Prevents updates/inserts that would cause the row to disappear from the view (violating the `WHERE` clause).

### 4.3 Materialized Views
*   `CREATE MATERIALIZED VIEW ...`
*   Physically saves the query result to disk.
*   Improves read performance for heavy queries.
*   Requires `REFRESH MATERIALIZED VIEW view_name` to update data.

---

## 5. Data Control Language (DCL)
Handles permissions and access control.

### 5.1 Role Management
*   `CREATE ROLE name LOGIN PASSWORD '...'`: Concrete user.
*   `CREATE ROLE group_name NOLOGIN`: Abstract group.

### 5.2 Role Inheritance (RBAC)
*   Grant privileges to a **Group**: `GRANT SELECT ON table TO group;`
*   Add User to Group: `GRANT group TO user;` (User inherits privileges).

### 5.3 Column-Level Security
*   `GRANT SELECT (col1, col2) ON table TO user;`
*   Restricts access to specific columns (Least Privilege).

### 5.4 Revoking Access
*   `REVOKE privilege ON object FROM user;`
