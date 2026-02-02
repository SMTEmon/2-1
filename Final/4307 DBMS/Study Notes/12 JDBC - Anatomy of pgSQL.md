Basic structure:

```
DO $$
DECLARE
    variable_name data_type := initial_value;  -- optional
BEGIN
    -- SQL statements
    -- Procedural logic
EXCEPTION
    WHEN some_exception THEN
        -- error handling
END;
$$ LANGUAGE plpgsql;

```

1. DECLARE: optional, for variables
2. BEGIN ... END: mandatory, holds the exec code
3. EXCEPTION: optional, handles errors
4. `$$` : delimiter for the block (like we discussed before)

### Variables
- Declare in DECLARE section
- TYPES = SQL types
- Can init immediately
```
DECLARE
	total_salary NUMERIC := 0;
	emp_name TEXT;
```

### Conditional Logic
```
IF total_salary > 5000 THEN
    RAISE NOTICE 'High salary';
ELSIF total_salary > 3000 THEN
    RAISE NOTICE 'Medium salary';
ELSE
    RAISE NOTICE 'Low salary';
END IF;
```

### Loops

a. Basic Loop
```
LOOP
    -- statements
    EXIT WHEN condition;  -- must exit
END LOOP;
```

b. While loop
```
WHILE i <= 10 LOOP
    RAISE NOTICE '%', i;
    i := i + 1;
END LOOP;
```

c. For ... in loop
```
FOR r IN SELECT id, salary FROM employee LOOP
    RAISE NOTICE 'ID: %, Salary: %', r.id, r.salary;
END LOOP;
```

