# Quiz Practice: Advanced SQL & Database Connectivity
**Topic:** Lecture 6 (JDBC, Python DB-API, Embedded SQL, SQLJ, PL/pgSQL, Triggers)

---

### Part 1: JDBC & Database Connectivity

**1. JDBC Connection & Resource Management**
Write a Java code snippet using the modern **`try-with-resources`** approach (Java 7+).
*   **Task:** Connect to a PostgreSQL database at `jdbc:postgresql://localhost:5432/univdb` with user "admin" and password "1234".
*   **Action:** Create a `Statement` object inside the resource block. You do not need to execute a query, just set up the structure so the connection closes automatically.

**2. Prevention of SQL Injection (Prepared Statements)**
Refactor the following **vulnerable** code to use a `PreparedStatement`.
*   *Bad Code:*
    ```java
    String inputName = getUserInput(); // Assume input is:  X'; DROP TABLE students; --
    String query = "SELECT salary FROM instructor WHERE name = '" + inputName + "'";
    Statement stmt = conn.createStatement();
    ResultSet rs = stmt.executeQuery(query);
    ```
*   **Task:** Rewrite this using `conn.prepareStatement()` and bind the parameter securely.

**3. JDBC Transactions**
Write a Java snippet that performs a bank transfer (Atomic Transaction).
*   **Scenario:** Move $500 from Account A to Account B.
*   **Requirements:**
    1.  Turn off auto-commit.
    2.  Execute two `UPDATE` statements.
    3.  If both succeed, `commit()`.
    4.  If an exception occurs, `rollback()`.

**4. CallableStatements (Stored Procedures)**
Assume there is a stored procedure in the DB: `get_student_gpa(IN student_id, OUT gpa)`.
*   **Task:** Write the Java JDBC code to call this procedure.
    *   Set the input parameter to "12345".
    *   Register the output parameter (type `java.sql.Types.FLOAT`).
    *   Execute and print the retrieved GPA.

**5. Python DB-API (The Tuple Trap)**
Write a Python snippet using `sqlite3`.
*   **Task:** Select a department name where the building is "Taylor".
*   **Constraint:** You **must** use parameter substitution (`?`).
*   **Hint:** Pay attention to how you pass the single parameter "Taylor" to `cursor.execute`. (Recall the trailing comma rule).

---

### Part 2: Embedded SQL & SQLJ

**6. Embedded SQL (Cursors)**
Write a pseudocode/C-style snippet using Embedded SQL (`EXEC SQL`).
*   **Task:**
    1.  Declare a cursor `c` for `SELECT ID, salary FROM instructor`.
    2.  Loop through the cursor.
    3.  If the salary is less than 50,000, increase it by 10% using the `WHERE CURRENT OF` syntax.
    4.  Close the cursor.

**7. SQLJ (Concept Check)**
*   **Question:** In standard JDBC, if you write `SELECT * FROM instrucotr` (typo), when do you find out about the error?
*   **Question:** In SQLJ, when would you find out about that same error, and why?

---

### Part 3: PL/pgSQL & Triggers

**8. PL/pgSQL Function**
Write a PostgreSQL function named `count_credits(s_id varchar)` that returns an `INTEGER`.
*   **Logic:** It should calculate the sum of credits for a specific student from the `takes` and `course` tables (joined).
*   **Return:** Return the total sum into a variable.

**9. Row-Level Trigger (Audit Log)**
Write the SQL to create a **Row-Level Trigger**.
*   **Scenario:** We want to track changes to the `grade` table.
*   **Step 1:** Write the function `log_grade_change()` that inserts a string into an `audit` table saying: "Student [ID] grade changed from [OLD GRADE] to [NEW GRADE]".
*   **Step 2:** Write the `CREATE TRIGGER` statement to fire this function **AFTER UPDATE** on the `grade` table **FOR EACH ROW**.

**10. Statement-Level vs. Row-Level**
*   **Scenario:** You issue a single SQL command: `UPDATE instructor SET salary = salary * 1.10;` which affects 1,000 rows.
*   **Task:**
    *   If you have a **Row-Level** trigger, how many times does the function execute?
    *   If you have a **Statement-Level** trigger, how many times does the function execute?

---
---

### Answer Key / Self-Check

**1. JDBC Resource Block**
```java
String url = "jdbc:postgresql://localhost:5432/univdb";
try (Connection conn = DriverManager.getConnection(url, "admin", "1234");
     Statement stmt = conn.createStatement()) {
    // Connection and Statement auto-close here
} catch (SQLException e) {
    e.printStackTrace();
}
```

**2. Prepared Statement**
```java
String query = "SELECT salary FROM instructor WHERE name = ?";
try (PreparedStatement pstmt = conn.prepareStatement(query)) {
    pstmt.setString(1, inputName); // Secure binding
    ResultSet rs = pstmt.executeQuery();
}
```

**3. Transaction**
```java
try {
    conn.setAutoCommit(false); // 1. Start Transaction
    stmt.executeUpdate("UPDATE account SET bal = bal - 500 WHERE id = 'A'");
    stmt.executeUpdate("UPDATE account SET bal = bal + 500 WHERE id = 'B'");
    conn.commit(); // 2. Commit
} catch (SQLException e) {
    conn.rollback(); // 3. Rollback on error
}
```

**4. CallableStatement**
```java
String sql = "{call get_student_gpa(?, ?)}";
try (CallableStatement cs = conn.prepareCall(sql)) {
    cs.setString(1, "12345");
    cs.registerOutParameter(2, java.sql.Types.FLOAT);
    cs.execute();
    float gpa = cs.getFloat(2);
    System.out.println("GPA: " + gpa);
}
```

**5. Python Tuple**
```python
# The trailing comma (item,) is crucial for single-item tuples
cursor.execute("SELECT dept_name FROM department WHERE building = ?", ("Taylor",))
```

**6. Embedded SQL Update**
```sql
EXEC SQL DECLARE c CURSOR FOR SELECT ID, salary FROM instructor;
EXEC SQL OPEN c;
while(1) {
    EXEC SQL FETCH c INTO :id, :sal;
    if (SQLSTATE == '02000') break;
    if (sal < 50000) {
        EXEC SQL UPDATE instructor SET salary = salary * 1.10 
                 WHERE CURRENT OF c; 
    }
}
EXEC SQL CLOSE c;
```

**7. SQLJ**
*   **JDBC:** Runtime (Crash).
*   **SQLJ:** Compile-time (Build failure). The Precompiler checks syntax against the DB schema.

**8. PL/pgSQL Function**
```sql
CREATE FUNCTION count_credits(s_id varchar) RETURNS INTEGER AS $$
DECLARE
    total INTEGER;
BEGIN
    SELECT SUM(credits) INTO total 
    FROM takes NATURAL JOIN course 
    WHERE id = s_id;
    
    RETURN total;
END; $$ LANGUAGE plpgsql;
```

**9. Trigger**
```sql
-- Step 1: Function
CREATE FUNCTION log_grade_change() RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit (msg) 
    VALUES ('Student ' || NEW.id || ' grade changed from ' || OLD.grade || ' to ' || NEW.grade);
    RETURN NEW;
END; $$ LANGUAGE plpgsql;

-- Step 2: Trigger
CREATE TRIGGER trg_grade_update
AFTER UPDATE ON grade
FOR EACH ROW EXECUTE FUNCTION log_grade_change();
```

**10. Trigger Frequency**
*   **Row-Level:** 1,000 times.
*   **Statement-Level:** 1 time.
