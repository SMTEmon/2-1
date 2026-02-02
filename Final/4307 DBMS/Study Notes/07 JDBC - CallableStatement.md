In JDBC: used to call stored procedures or functions in the database
Syntax looks like SQL, but wrapped in `CallableStatement`
Similar to `PreparedStatement`, but handles IN, OUT, INOUT parameters.

Suppose, we have the following Postgres function:
```
CREATE FUNCTION get_salary(emp_id INT) RETURNS NUMERIC AS $$
BEGIN
    RETURN (SELECT salary FROM employee WHERE id = emp_id);
END;
$$ LANGUAGE plpgsql;
```

In JDBC, you call it using `CallableStatement`:
```
CallableStatement cs = con.prepareCall("{ ? = call get_salary(?) }");
cs.registerOutParameter(1, Types.NUMERIC);  // OUT parameter
cs.setInt(2, 101);                          // IN parameter
cs.execute();
BigDecimal salary = cs.getBigDecimal(1);
```

Here, `?` placeholders are the same as PreparedStatement
`registerOutParameter` is needed for OUT/ INOUT parameters
`setXXX` Set IN values
`getXXX` Retrieve OUT values after `execute()`


