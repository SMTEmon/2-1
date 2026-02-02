A usual workflow in psql:
```
connect --> run SQL --> see result -->commit/rollback -->disconnect
```

In JDBC, the *same* flow exists, but with Java objects.
```
Connection --> Statement/PreparedStatement --> Resultset --> commmit()/rollback()
```

1. **Connection**: Represents a live session with PostgreSQL
2. **Statement/ Prep:** Used to send SQL to DB (Prep = safe + pre=compiled)
3. **ResultSet**: Cursor over query results (row by row access)

In JDBC: 

`executeQuery()` --> SELECT
`executeUpdate()` --> INSERT/ UPDATE/ DELETE

Suppose you ruin this in PostreSQL: 
```
UPDATE employee SET salary = salary * 1.1;
```

What do you actually *see* printed?
```
UPDATE 12
```

Notice that `UPDATE/ INSERT/ DELETE` do NOT return rows. They return number of rows affected. 

In JDBC terms: `executeUpdate()` returns an int

```
int count = stmt.executeUpdate();
```

Contrast with SELECT:
```
SELECT * FROM employee;
```

This on the other hand, does return rows. Hence, in JDBC: `executeQuery() --> ResultSet`
