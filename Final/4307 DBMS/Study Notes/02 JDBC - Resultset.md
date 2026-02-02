Understand that when you run the following in `psql` 
```
SELECT * FROM employee;
```

The server sends them row by row. That is the intuition JDBC builds on.

A **ResultSet** is a cursor positioned ***before*** the first row. We must move it to read the data. Rows are processed **one at a time**.

```
while (rs.next()) {

}
```

- `next()` moves cursor forward by **one row**
- Returns `true` if a row exists.

How are columns retrieved?

For each row, we can fetch columns by:
- column index (1-based) or,
- column name (much safer)

```
rs.getInt("id");
rs.getString("name");
rs.getDouble("salary");
rs.getDate("date");
rs.getTimestamp("time");
```

What about NULL Values?

Suppose:
```
salary = NULL
```
java:
```
double sal = rs.getDouble("salary");
```
if salary is NULL, Java gives 0.0 with no exception. 
(for other datatypes, equivalents are returned. as in for `int`, we get 0, for `bool`, we get false)

Correct way to handle this:
```
double sal = rs.getDouble("salary");
if(rs.wasNull()) {
	//salary was actually NULL
}
```
