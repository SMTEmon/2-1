In `psql`, by default, every statement is auto-committed.
Similarly, in JDBC, `autoCommit = true` by default. 

Why is this dangerous in Java?
Imagine this logic:
- deduct money from acct. A
- add money to acct. B

If step 2 fails and autoCommit is ON:
- step 1 is already permanent
- database becomes inconsistent

```
con.setAutoCommit(false);

try {
   // multiple SQL statements
   con.commit();
} catch (Exception e) {
   con.rollback();
}

```

exaclty like:

```
BEGIN;
-- statements
COMMIT;
-- or ROLLBACK
```

trap: `commit()` does nothing if auto-commit = true.
`rollback()` only works when auto-commit = false
Always reset auto-commit in pooled connections.

