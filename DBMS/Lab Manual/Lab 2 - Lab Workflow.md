---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab II: Lab Workflow

## 1. Connection & Setup
1.  **Network:** Use Ethernet connection in the lab.
2.  **Login:** `sudo -i -u postgres psql`

## 2. Create Role and Database
**Important:** Drop existing if conflict avoids errors.
```sql
DROP DATABASE IF EXISTS db_name;
DROP ROLE IF EXISTS user_name;

CREATE ROLE alice LOGIN PASSWORD 'pass';
CREATE DATABASE db_name OWNER alice;
GRANT ALL PRIVILEGES ON DATABASE db_name TO alice;
```

## 3. Execution
1.  **Connect:** `psql -U alice -d db_name`
2.  **Load SQL File:** Run from terminal (outside psql):
    `psql -U alice -d db_name -f /path/to/file.sql`
3.  **Verify:** `\dt` (list tables), `SELECT * FROM ...`
