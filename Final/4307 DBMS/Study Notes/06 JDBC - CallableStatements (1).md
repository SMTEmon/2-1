We have to understand 3 different things:

1. `registerOutParameter` 
   this tells JDBC that a particular parameter is OUT or INOUT (i.e. the database will return a value in that slot.)
   
   ```
    CREATE FUNCTION get_salary(emp_id INT) RETURNS NUMERIC AS $$
	BEGIN
	    RETURN (SELECT salary FROM employee WHERE id = emp_id);
	END;
	$$ LANGUAGE plpgsql;
   ```
   JDBC:
   ```
    CallableStatement cs = con.prepareCall("{ ? = call get_salary(?) }");
	cs.registerOutParameter(1, Types.NUMERIC); // OUT parameter
	cs.setInt(2, 101);                         // IN parameter
	cs.execute();
	BigDecimal salary = cs.getBigDecimal(1);   // retrieve OUT value
   ```

The ? represents the return value of the function in JDBC. And could be OUT parameter.

1. `$$` in Postgres
   
   ```
    CREATE FUNCTION test() RETURNS void AS $$
	BEGIN
	   RAISE NOTICE 'Hello World';
	END;
	$$ LANGUAGE plpgsql;
   ```

- Everything between `$$ ... $$` is treated as a string literal
- Advantage: you don't have to escape single quotes `'` inside the function
- Handy for **PL/pgSQL** blocks with lots of quotes

1. `plpgSQL`
   Procedural Language for PostgresSQL
   - Adds programming constructs to SQL:
	   - Variables
	   - IF/ ELSE
	   - Loops
	   - Exception Handling
   - Used inside functions/ procedures:
```
CREATE FUNCTION get_bonus(salary NUMERIC) RETURNS NUMERIC AS $$
DECLARE
    bonus NUMERIC;
BEGIN
    IF salary > 5000 THEN
        bonus := salary * 0.1;
    ELSE
        bonus := salary * 0.05;
    END IF;
    RETURN bonus;
END;
$$ LANGUAGE plpgsql;
```

- `$function$ ... $function$` is optional, can also use `$body$` etc.
- Makes Postgres more like a mini programming language inside the DB


