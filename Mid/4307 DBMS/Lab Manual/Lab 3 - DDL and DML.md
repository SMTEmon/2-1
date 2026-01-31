---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab III: DDL and DML

## 1. Data Definition (DDL)

### 1.1 Creating a Table
```sql
CREATE TABLE Product (
    pid SERIAL PRIMARY KEY,           -- Auto-increment
    name VARCHAR(50) NOT NULL,
    price INT CHECK (price >= 0),     -- Constraint
    category VARCHAR(30)
);
```
**Common Types:** `INT`, `VARCHAR(n)`, `SERIAL`, `NUMERIC(p,s)`.

### 1.2 Dropping & Altering
*   `DROP TABLE table_name CASCADE;` (Removes table and dependents).
*   `ALTER TABLE`:
    *   `ADD COLUMN`
    *   `DROP COLUMN`
    *   `ALTER COLUMN ... TYPE ...`
    *   `RENAME COLUMN ... TO ...`

---

## 2. Data Manipulation (DML)

### 2.1 Inserting Records
```sql
INSERT INTO Product (pid, name, price) 
VALUES (DEFAULT, 'Mouse', 45);
```

### 2.2 Updating & Deleting
**Warning:** Always use a `WHERE` clause.
*   `UPDATE table SET col = val WHERE condition;`
*   `DELETE FROM table WHERE condition;`

---

## 3. Retrieval and Filtering
*   **Basic:** `SELECT * FROM table WHERE condition;`
*   **Logical Operators:** `AND`, `OR`.
