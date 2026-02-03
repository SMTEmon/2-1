
| Feature            | Function                                                    | Procedure                                |
| ------------------ | ----------------------------------------------------------- | ---------------------------------------- |
| Return value       | Must return something (scalar, record, table)               | Optional / none                          |
| Called with        | `SELECT myfunc(...)` or `? = call myfunc(...)` (JDBC)       | `CALL myproc(...)`                       |
| Can be used in SQL | Yes — can appear in queries                                 | No — only CALL                           |
| Transactions       | Cannot manage (COMMIT/ROLLBACK inside function not allowed) | Can manage transactions inside procedure |
| OUT / INOUT params | Can have, optional                                          | Can have, optional                       |

- Function
```
CREATE FUNCTION get_salary(emp_id INT) RETURNS NUMERIC AS $$
DECLARE
    sal NUMERIC;
BEGIN
    SELECT salary INTO sal FROM employee WHERE id = emp_id;
    RETURN sal;
END;
$$ LANGUAGE plpgsql;

```
- Must return a value
- Can be used in SELECT or via JDBC CallableStatement

- Procedure
```
CREATE PROCEDURE update_salary(emp_id INT, increment NUMERIC)
LANGUAGE plpgsql
AS $$
BEGIN
    UPDATE employee SET salary = salary + increment WHERE id = emp_id;
END;
$$;

```
- Does not return a value
- Can be invoked via CALL update_salary(101, 500);
- Can include transaction control inside

- Transactions in Procedures
```
CREATE PROCEDURE transfer_money(from_acc INT, to_acc INT, amt NUMERIC)
LANGUAGE plpgsql
AS $$
BEGIN
    BEGIN
        UPDATE account SET balance = balance - amt WHERE id = from_acc;
        UPDATE account SET balance = balance + amt WHERE id = to_acc;
        COMMIT;
    EXCEPTION
        WHEN OTHERS THEN
            ROLLBACK;
    END;
END;
$$;

```
- Functions cannot do this
- Procedures give you full transactional control

- Using FOR ... IN loops inside Procedures/ Functions
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
