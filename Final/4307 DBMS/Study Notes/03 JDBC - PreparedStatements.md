Why do you think this is bad?
```
String sql = "SELECT * FROM employee WHERE name = " + name ;
```

If `name` contains ', we are open to `SQL Injection`. 

How does prepared statement solve this? 
```
SELECT * FROM employee WHERE name = ?
```
- `?` = placeholder
- Data is bound, not injected into SQL text
- PostgresSQL never treats it as SQL code

JDBC Flow:
```
PreparedStatement ps = con.preparedStatement(
	"SELECT * FROM employee WHERE name = ?"
);

ps.setString(1, name);
ResultSet rs = ps.executeQuery();
```
