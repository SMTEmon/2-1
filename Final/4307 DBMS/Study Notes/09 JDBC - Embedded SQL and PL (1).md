Embedded SQL: What it is
- Embedded SQL = putting SQL inside a host language (like C, Java)
- Host language handles variables, loops, control flow
- SQL handles data operations

Connection and Host Variable
- Host variables = program variables that SQL reads from or writes to
- You declare them in your host language, then prefix with : in SQL

```
int empId = 101;
char name[50];

EXEC SQL SELECT name INTO :name FROM employee WHERE id = :empId;
```

conceptually quite similar to JDBC PreparedStatement + ResultSet

Cursor & Impedance Mismatch Problem
- Cursor = pointer to a set of rows returned by a query
- Impedance mismatch = difference between relational sets and host language data structures.
- Embedded SQL solves this with cursors.
```
EXEC SQL DECLARE emp_cursor CURSOR FOR
    SELECT id, name FROM employee;
EXEC SQL OPEN emp_cursor;

while (more_rows) {
    EXEC SQL FETCH emp_cursor INTO :id, :name;
}
EXEC SQL CLOSE emp_cursor;
```

Updates with Embedded SQL
- Works like SELECT, but writes data
- Uses host variables to pass values
```
EXEC SQL UPDATE employee
SET salary = :newSalary
WHERE id = :empId;
```

Connection to PL/ pgSQL
- Embedded SQL concepts --> maps directly to functions and procedures in Postgres
- Cursors, loops, conditional logic --> PL/ pgSQL blocks
