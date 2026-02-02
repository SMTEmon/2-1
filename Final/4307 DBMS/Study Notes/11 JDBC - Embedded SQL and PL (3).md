1. Updating Data with Emb
   - You can use hots variables to pass values from your program to SQL
```
EXEC SQL UPDATE employee
SET salary = :newSalary
WHERE id = :empId
```

```
int count;
EXEC SQL GET DIAGNOSTICS :count = ROW_COUNT;
```

2. Combining with Cursor & Loop

```
EXEC SQL DECLARE emp_cursor CURSOR FOR
    SELECT id, salary FROM employee WHERE dept = 'HR';
EXEC SQL OPEN emp_cursor;

WHILE SQLCODE = 0 DO
    EXEC SQL FETCH emp_cursor INTO :id, :salary;
    :salary = :salary * 1.1;  -- increase by 10%
    EXEC SQL UPDATE employee
        SET salary = :salary
        WHERE id = :id;
END WHILE;

EXEC SQL CLOSE emp_cursor;
```

3. Connection to PL/ pgSQL
```
CREATE PROCEDURE increase_salary(dept TEXT)
LANGUAGE plpgsql
AS $$
DECLARE
    r RECORD;
BEGIN
    FOR r IN SELECT id, salary FROM employee WHERE department = dept LOOP
        UPDATE employee
        SET salary = r.salary * 1.1
        WHERE id = r.id;
    END LOOP;
END;
$$;
```
- `FOR r IN SELECT ... LOOP` → same as cursor + fetch
- Host variables replaced by **loop variables**
- Transaction handled automatically (or explicitly with COMMIT/ROLLBACK)
