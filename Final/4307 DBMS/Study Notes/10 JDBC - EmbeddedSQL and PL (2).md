### 1. Declare the Cursor

- Tell the database what query the cursor will execute
```
DECLARE emp_cursor CURSOR FOR
	SELECT id, name FROM employee WHERE dept = 'HR';
```

### 2. Open the Cursor
```
OPEN emp_cursor;
```
- Actually runs the query on the DB
- Positions the cursor before the first row.
- Same as `ResultSet rs = stmt.executeQuery(...)`

### 3. Fetch Rows
```
FETCH emp_cursor INTO :id, :name;
```
- Moves the cursor one row fwd
- Stores col values into host var
- Returns a status (success/ no more rows)
- In JDBC: `rs.next()` + `getXXX()`

### 4. Loop Until Done
```
WHILE SQLCODE = 0 DO
	FETCH emp_cursor INTO :id, :name;
END WHILE;
```
same as:
```
while (rs.next()) {
    int id = rs.getInt("id");
    String name = rs.getString("name");
}
```

### 5. Close the Cursor
```
CLOSE emp_cursor;
```

Cursor Cycle: Declare --> Open --> Fetch --> Process --> Close

