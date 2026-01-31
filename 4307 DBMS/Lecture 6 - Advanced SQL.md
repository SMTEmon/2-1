***

# Advanced SQL (Lecture 6, Chapter 5)

## 1. Accessing SQL from Programming Languages

### Why Interface with Programs?
SQL is declarative and data-focused. It is not general-purpose. Real-world applications (Web Servers, GUIs) need general-purpose languages (Java, Python, C++) to handle logic, user interfaces, and complex calculations, while SQL handles the data manipulation.

### Main Approaches
1.  **Dynamic SQL:** Queries are constructed as strings at runtime.
    *   **JDBC (Java Database Connectivity):** Standard API for Java.
    *   **ODBC (Open Database Connectivity):** Standard for C/C++, C#, etc.
    *   **Python DB-API:** Standard for Python.
2.  **Embedded SQL:** SQL statements are identified at compile time by a pre-processor (e.g., `EXEC SQL`).

---

## 2. JDBC (Java Database Connectivity)

**Definition:** A Java API for communicating with database systems supporting SQL.
**Key Capabilities:** Querying/updating data, retrieving results, and **Metadata retrieval**.

### The Communication Model
1.  Open a connection.
2.  Create a "Statement" object.
3.  Execute queries (send to DB / fetch results).
4.  Handle errors via Exceptions (`SQLException`).

### Establishing Connections

> [!NOTE] Try-with-resources
> Modern Java (Java 7+) uses `try-with-resources` to automatically close connections and statements, preventing memory leaks.

**Modern Approach (Recommended):**
```java
public static void JDBCexample(String dbid, String userid, String passwd) {
    // Automatically closes resources
    try (Connection conn = DriverManager.getConnection(
            "jdbc:oracle:thin:@db.yale.edu:2000:univdb", userid, passwd);
         Statement stmt = conn.createStatement();
    ) {
        // ... Do Actual Work ...
    } catch (SQLException sqle) {
        System.out.println("SQLException : " + sqle);
    }
}
```

**Legacy Approach (Older Java):**
*   Requires `Class.forName("driver")`.
*   Requires manual `conn.close()` and `stmt.close()`.

### Executing Commands

**1. Updates (INSERT, UPDATE, DELETE)**
Use `stmt.executeUpdate()`. Returns an integer (row count).
```java
try {
    stmt.executeUpdate(
        "insert into instructor values('77987', 'Kim', 'Physics', 98000)");
} catch (SQLException sqle) { ... }
```

**2. Queries (SELECT)**
Use `stmt.executeQuery()`. Returns a `ResultSet`.
```java
ResultSet rset = stmt.executeQuery(
    "select dept_name, avg(salary) from instructor group by dept_name");

while (rset.next()) {
    // Access by column name or index (1-based)
    System.out.println(rset.getString("dept_name") + " " + rset.getFloat(2));
}
```

### Handling Null Values
Primitive types in Java (`int`, `float`) cannot be `null`.
*   **Method:** Use `rs.wasNull()` immediately after reading a column to check validity.
```java
int a = rs.getInt("a");
if (rs.wasNull()) {
    System.out.println("Got null value");
}
```

---

## 3. SQL Injection & Security

> [!WARNING] CRUCIAL SECURITY WARNING
> **NEVER** create a query by concatenating user input strings. This leads to SQL Injection.

### The Attack
**Vulnerable Code:**
```java
"select * from instructor where name = '" + name + "'"
```
**Exploit:** User enters `X' or 'Y' = 'Y`.
**Resulting Query:**
```sql
select * from instructor where name = 'X' or 'Y' = 'Y'
```
Since `'Y'='Y'` is always true, the attacker gains access to **all** data.

### The Solution: Prepared Statements
Queries are compiled once with placeholders (`?`). Input is treated as **literal data**, not executable code.

**Syntax:**
```java
PreparedStatement pStmt = conn.prepareStatement(
    "insert into instructor values(?,?,?,?)");

// Set values safely
pStmt.setString(1, "88877");
pStmt.setString(2, "Perry");
pStmt.setString(3, "Finance");
pStmt.setInt(4, 125000);

pStmt.executeUpdate();
```

**Benefits:**
1.  **Security:** Completely prevents SQL Injection.
2.  **Performance:** DB reuses the execution plan (parsing overhead reduced).

---

## 4. Metadata Features

Metadata allows programs to discover the schema (tables, columns, types) dynamically.

1.  **ResultSetMetaData:** Information about the *result* of a query.
    ```java
    ResultSetMetaData rsmd = rs.getMetaData();
    // Loop through columns
    for(int i = 1; i <= rsmd.getColumnCount(); i++) {
        System.out.println(rsmd.getColumnName(i));
        System.out.println(rsmd.getColumnTypeName(i));
    }
    ```
2.  **DatabaseMetaData:** Information about the *database* itself.
    *   **Get Columns:** `dbmd.getColumns(null, "univdb", "department", "%")`
    *   **Get Tables:** `dbmd.getTables(...)`
    *   **Get Primary Keys:** `dbmd.getPrimaryKeys(...)`

---

## 5. Transactions & Other JDBC Features

### Transaction Control
*   **Default:** Auto-commit is **ON**.
*   **Manual Control:** Needed for atomicity (grouping multiple updates).
    ```java
    conn.setAutoCommit(false); // Start transaction
    // ... perform operations ...
    conn.commit();   // Save changes
    conn.rollback(); // Discard changes on error
    ```

### Other Features
*   **CallableStatements:** For executing stored procedures/functions.
    ```java
    CallableStatement cStmt = conn.prepareCall("{? = call some_func(?)}");
    ```
*   **LOBs (Large Objects):** `getBlob()` / `getClob()` for large binary/text data.

---

## 6. Embedded SQL & SQLJ

**Problem with JDBC:** Errors are caught at *runtime*.
**Solution (SQLJ):** Static checking at *compile time*.

**Concept:** Embed SQL directly in host language (Java, C) using a preprocessor.
*   **Prefix:** `EXEC SQL` (C style) or `#sql` (Java style).
*   **Host Variables:** Preceded by a colon (`:`). Must be declared in a `DECLARE SECTION`.

### Cursors (Solving Impedance Mismatch)
SQL works on **Sets**; Host languages work on **Records**. A **Cursor** acts as a pointer/iterator to bridge this gap.

**Workflow:**
1.  **Declare:** Define the query.
2.  **Open:** Execute query, store results in temp relation.
3.  **Fetch:** Get one row into host variables.
4.  **Close:** Clean up.

**Updating with Cursors:**
Must declare `FOR UPDATE`.
```sql
UPDATE instructor SET salary = salary + 1000 
WHERE CURRENT OF c;
```

---

## 7. Python Database Access (DB-API)

Standard API used by drivers like `psycopg2` (Postgres), `sqlite3`, `mysql-connector`.

**Key Concepts:**
*   **Connection:** Session with DB.
*   **Cursor:** Equivalent to JDBC Statement; executes queries.

**Example (Safe Parameterization):**
```python
import sqlite3
conn = sqlite3.connect('univ.db')
cursor = conn.cursor()

dept = 'Music'
# Use ? or %s for placeholders depending on driver
cursor.execute("SELECT name FROM instructor WHERE dept_name = ?", (dept,))

for row in cursor.fetchall():
    print(row[0])

conn.close()
```

---

## 8. Functions and Procedures (PL/pgSQL)

**PL/pgSQL:** Procedural Language/PostgreSQL. Adds variables, loops, and flow control to SQL.

### Anatomy of a Block
```sql
DO $$ 
DECLARE
    -- 1. Variables
    counter integer := 0;
BEGIN
    -- 2. Logic
    counter := counter + 1;
    -- 3. Output
    RAISE NOTICE 'Count: %', counter;
END $$;
```
*   `$$`: Dollar quotes (avoids escaping single quotes).
*   `SELECT ... INTO var`: Moves data from table to variable.

### Control Structures
*   **IF/ELSE:**
    ```sql
    IF len < 60 THEN ... ELSIF ... ELSE ... END IF;
    ```
*   **Loops (FOR):**
    ```sql
    FOR cnt IN 1..3 LOOP ... END LOOP;
    ```
*   **Looping Query Results:**
    ```sql
    FOR r IN SELECT * FROM department LOOP
        total := total + r.budget;
    END LOOP;
    ```

### Functions vs. Procedures
| Feature | Function | Procedure (Postgres 11+) |
| :--- | :--- | :--- |
| **Invocation** | `SELECT func()` | `CALL proc()` |
| **Return** | Must return value/void | No return (uses `INOUT`) |
| **Transactions** | Cannot `COMMIT`/`ROLLBACK` | **Can** manage transactions |

**Table Functions:** Can return a set of rows (`RETURNS TABLE`) and be used in the `FROM` clause.

---

## 9. Triggers

**Definition:** Procedural code automatically executed ("fired") in response to a database change.
**ECA Model:** **E**vent (Insert/Update) → **C**ondition (Predicate) → **A**ction (SQL execution).

### Variables
*   `NEW`: The new row being inserted/updated.
*   `OLD`: The old row being deleted/updated.

### Row-Level vs. Statement-Level

| Feature | Row-Level | Statement-Level |
| :--- | :--- | :--- |
| **Syntax** | `FOR EACH ROW` | `FOR EACH STATEMENT` |
| **Frequency** | Fires $N$ times ($N$=rows affected) | Fires 1 time per SQL command |
| **Access** | Can see `NEW` and `OLD` data | No direct row access (uses Transition Tables) |
| **Use Case** | Data validation, Calculations | Auditing, Logging "batch" events |

**Implementation Steps (Postgres):**
1.  Create a **Function** returning `TRIGGER`.
2.  Create a **Trigger** binding that function to an event (`AFTER UPDATE ON table`).

> [!DANGER] Risks of Triggers
> 1.  **Cascading:** Trigger A updates Table B, which triggers Trigger B updating Table A... (Infinite Loop).
> 2.  **Hidden Failures:** An error in an audit trigger can rollback critical transactions.
> 3.  **Bulk Performance:** Loading 1 million rows fires the trigger 1 million times. (Disable triggers for bulk loads).

---

## 10. Recursive Queries

Essential for hierarchical data (e.g., Organization Charts, Prerequisite Chains).
Uses **Common Table Expressions (CTEs)** via `WITH RECURSIVE`.

### Structure
1.  **Base Case:** Non-recursive query (Starting point/Depth 0).
2.  **Recursive Step:** Joins the CTE with the original table to find the next level.
3.  **Termination:** Stops when the recursive step returns 0 rows.

**Example: Transitive Closure (Prerequisites)**
```sql
WITH RECURSIVE rec_prereq(course_id, prereq_id) AS (
    -- Base Case
    SELECT course_id, prereq_id FROM prereq
    UNION
    -- Recursive Step
    SELECT rec_prereq.course_id, prereq.prereq_id
    FROM rec_prereq, prereq
    WHERE rec_prereq.prereq_id = prereq.course_id
)
SELECT * FROM rec_prereq;
```

---

## 11. Advanced Aggregation (OLAP)

### Ranking Functions
*   `rank()`: Leaves gaps for ties (1, 1, 3).
*   `dense_rank()`: No gaps for ties (1, 1, 2).
*   `row_number()`: Unique integer, non-deterministic on ties.
*   `ntile(n)`: Divides data into $n$ buckets (e.g., quartiles).

**Partitioning:** `OVER (PARTITION BY dept_name ORDER BY GPA)` allows ranking *within* groups without collapsing them like `GROUP BY`.

### Window Functions
Calculates a value for each row based on a "window" of related rows. **Does not collapse rows.**

**Window Frames:**
*   `ROWS UNBOUNDED PRECEDING`: From start to current (Running Total).
*   `ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING`: Moving Average.

### OLAP (Online Analytical Processing)
Visualizing multidimensional data (Data Cubes).
*   **Dimensions:** Filters (Color, Size, Date).
*   **Measures:** Values (Quantity, Sales).

**Operations:**
*   **Slicing:** Fixing one dimension (e.g., Only "Red" shirts).
*   **Dicing:** Filtering a sub-cube (e.g., "Red" or "Blue" shirts).
*   **Roll-up:** Zoom out (Daily → Monthly).
*   **Drill-down:** Zoom in (Yearly → Quarterly).

**Extended Aggregation in SQL:**
1.  `ROLLUP(Item, Color)`: Generates hierarchy totals (Subtotals for Item, Grand Total). *Misses totals for Color alone.*
2.  `CUBE(Item, Color)`: Generates **all** possible combinations ($2^N$), including cross-sections missing in Rollup.