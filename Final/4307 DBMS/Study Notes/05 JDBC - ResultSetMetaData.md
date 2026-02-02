It lets Java inspect the structure of query results at runtime. This is handy for dynamic apps or generic reporting. 

Step1: Getting Metadata
We start with a `ResultSet`
```
ResultSet rs = stmt.executeQuery("SELECT * FROM employee");
ResultSetMetaData rsmd = rs.gerMetaData();
```
- `rsmd` now knows everything about the columns in the result set. 

Useful Methods:

| Method                       | What it tells you                 |
| ---------------------------- | --------------------------------- |
| `getColumnCount()`           | How many columns                  |
| `getColumnName(int col)`     | Name of column `col` (1-based)    |
| `getColumnTypeName(int col)` | SQL type (e.g., `INT`, `VARCHAR`) |
| `isNullable(int col)`        | Can this column be `NULL`?        |
| `isAutoIncrement(int col)`   | Auto-increment column?            |
Example:
```
int colCount = rsmd.getColumnCount();
for (int i = 1; i <= colCount; i++) {
	System.out.println(
		rsmd.getColumnName(i) + " - " + rsmd.getColumnTypeName(i)
	);

}
```

Primary Keys (via DatabaseMetaData)
```
DatabaseMetaData dbmd = con.getMetaData();
ResultSet pk = dbmd.getPrimaryKeys(null, null, "employee");
while (pk.next()) {
	System.out.println(pk.getString("COLUMN_NAME");
}
```

- `DatabaseMetaData`= info about the entire database
- `ResultSetMetaData` = info about one result set
