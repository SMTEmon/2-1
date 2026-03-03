The `TRUNCATE` command in PostgreSQL is used to quickly remove all rows from a table or a group of tables.

While it achieves the same end result as a `DELETE` statement without a `WHERE` clause, it operates very differently under the hood. It is generally classified as a Data Definition Language (DDL) operation because of how it interacts with storage, though in PostgreSQL, it retains transaction safety.

Here is a breakdown of how `TRUNCATE` works in PostgreSQL, its key features, and how it compares to `DELETE`.

---

### Core Syntax and Key Options

The basic syntax is straightforward:

SQL

```
TRUNCATE TABLE table_name;
```

However, PostgreSQL provides several powerful options to modify its behavior:

- **Multiple Tables:** You can truncate several tables at once in a single command.
    
    SQL
    
    ```
    TRUNCATE TABLE table1, table2, table3;
    ```
    
- **`RESTART IDENTITY` / `CONTINUE IDENTITY`:** If your table uses an auto-incrementing identity column (like `SERIAL` or `GENERATED ALWAYS AS IDENTITY`), `TRUNCATE` does not reset the sequence counter by default (`CONTINUE IDENTITY`). If you want the sequence to start over at 1, use `RESTART IDENTITY`.
    
    SQL
    
    ```
    TRUNCATE TABLE table_name RESTART IDENTITY;
    ```
    
- **`CASCADE` / `RESTRICT`:** If other tables have Foreign Key references pointing to the table you are truncating, `TRUNCATE` will fail by default (`RESTRICT`). To automatically truncate all referencing tables as well, use `CASCADE`. **Use this with extreme caution.**
    
    SQL
    
    ```
    TRUNCATE TABLE parent_table CASCADE;
    ```
    

---

### Key Characteristics of TRUNCATE

- **Performance:** `TRUNCATE` is significantly faster than `DELETE`. `DELETE` scans the table and logs the deletion of _every single row_ in the Write-Ahead Log (WAL). `TRUNCATE` simply drops the data files associated with the table and creates new, empty ones, requiring minimal system resources and WAL logging.
    
- **Storage Reclaim:** `TRUNCATE` immediately reclaims the disk space used by the table data and its indexes. `DELETE` merely marks rows as "dead" (invisible), requiring a `VACUUM` operation later to actually free up the space.
    
- **Transaction Safe (Postgres Specific):** Unlike in some other database systems (like Oracle), `TRUNCATE` is MVCC-safe in PostgreSQL. This means you can run `TRUNCATE` inside a transaction block (`BEGIN; ... COMMIT;`), and if you issue a `ROLLBACK`, the truncated data will be perfectly restored.
    
- **Locking:** `TRUNCATE` acquires an **`ACCESS EXCLUSIVE`** lock on the table. This means it completely blocks all concurrent operations on that table, including simple `SELECT` queries, until the transaction finishes.
    
- **Triggers:** `TRUNCATE` does **not** fire row-level `ON DELETE` triggers. It will only fire statement-level `BEFORE TRUNCATE` and `AFTER TRUNCATE` triggers if you have explicitly defined them.
    

---

### TRUNCATE vs. DELETE Comparison

|**Feature**|**TRUNCATE**|**DELETE (without WHERE)**|
|---|---|---|
|**Speed**|Extremely fast|Slow (scales with table size)|
|**Disk Space**|Reclaimed immediately|Requires `VACUUM` to reclaim|
|**Transaction Safe?**|Yes (in PostgreSQL)|Yes|
|**Row-Level Triggers?**|No|Yes|
|**Lock Level**|`ACCESS EXCLUSIVE` (blocks reads & writes)|`ROW EXCLUSIVE` (blocks writes, allows reads)|
|**Foreign Keys**|Blocked unless using `CASCADE`|Blocked if referenced rows exist|
|**Granularity**|Entire table only|Can target specific rows with `WHERE`|

---

Would you like to see examples of how to write statement-level `TRUNCATE` triggers, or do you need help optimizing a specific data-deletion process in your database?