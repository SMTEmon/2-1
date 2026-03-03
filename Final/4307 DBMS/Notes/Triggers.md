Based on the example provided in the GeeksforGeeks article, here is a step-by-step explanation of how the PostgreSQL trigger works. https://www.geeksforgeeks.org/postgresql/postgresql-trigger/

The goal of this example is to automatically keep an audit log. Every time a new employee is added to the company database, the database should automatically record the employee's ID and the exact time they were added into a separate audit table.

Here is the breakdown of how the example achieves this in 4 steps:

### Step 1: Create the Necessary Tables

First, the example sets up two tables:

1. **`COMPANY` Table**: This is the main table that holds employee records (ID, Name, Age, Address, and Salary).
    
2. **`AUDIT` Table**: This is the tracking table. It only has two columns: `EMP_ID` (to record _who_ was added) and `ENTRY_DATE` (to record _when_ they were added).
    

### Step 2: Define the Trigger Function

Before creating a trigger, PostgreSQL requires you to create a special function that tells the database exactly _what_ to do when the trigger fires.

SQL

```
CREATE OR REPLACE FUNCTION auditlog() RETURNS TRIGGER AS $$  
BEGIN  
  INSERT INTO AUDIT(EMP_ID, ENTRY_DATE) VALUES (NEW.ID, current_timestamp);  
  RETURN NEW;  
END;  
$$ LANGUAGE plpgsql;  
```

- **`RETURNS TRIGGER`**: This specifies that this function is specifically built to be used by a trigger.
    
- **`NEW.ID`**: The keyword `NEW` holds the data of the new row being inserted. `NEW.ID` grabs the ID of the new employee being added to the `COMPANY` table.
    
- **`current_timestamp`**: A built-in function that grabs the exact current date and time.
    
- **The Action**: It inserts the new employee's ID and the current time into the `AUDIT` table.
    
- **`RETURN NEW;`**: Row-level triggers must return the row data (`NEW`) so the database can proceed with the original insert operation.
    

### Step 3: Create and Bind the Trigger

Now that the function exists, the example binds it to the `COMPANY` table using a trigger.

SQL

```
CREATE TRIGGER example_trigger  
AFTER INSERT ON COMPANY  
FOR EACH ROW  
EXECUTE FUNCTION auditlog();  
```

- **`AFTER INSERT ON COMPANY`**: This tells PostgreSQL to wait until a new row is successfully inserted into the `COMPANY` table before firing.
    
- **`FOR EACH ROW`**: This makes it a "Row-Level Trigger." If a single SQL query inserts 5 employees at once, this trigger will run 5 separate times (once for every individual employee added).
    
- **`EXECUTE FUNCTION auditlog()`**: This tells the trigger to run the function created in Step 2.
    

### Step 4: Insert Sample Data and Verify

Finally, the example tests the trigger by inserting data:

SQL

```
INSERT INTO COMPANY (ID, NAME, AGE, ADDRESS, SALARY)  
VALUES (1, 'Raju', 25, 'New-Delhi', 33000.00 );  
```

**What happens under the hood when this runs?**

1. PostgreSQL inserts Raju (ID: 1) into the `COMPANY` table.
    
2. Because an `INSERT` just happened on the `COMPANY` table, the `example_trigger` wakes up.
    
3. The trigger executes the `auditlog()` function.
    
4. The function takes Raju's ID (`1`) and the current time, and automatically inserts them into the `AUDIT` table.
    

As a result, without you having to write a second `INSERT` statement, the `AUDIT` table automatically logs the event!