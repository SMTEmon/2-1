PostgreSQL has a fantastic toolkit for manipulating strings. Since you've already seen `LEFT`, `TRIM`, and `REPLACE`, here are some of the other most widely used string functions, categorized by what they do:

### 1. Extracting Parts of a String

- **`RIGHT(string, n)`**: The exact opposite of `LEFT`. It grabs the specified number of characters from the end of a string.
    
    SQL
    
    ```
    SELECT RIGHT('John Doe', 3); 
    -- Result: 'Doe'
    ```
    
- **`SUBSTRING(string, start_position, length)`**: Extracts a specific chunk of text from the middle of a string. _(Note: SQL indexes start at 1, not 0)._
    
    SQL
    
    ```
    SELECT SUBSTRING('PostgreSQL', 1, 4); 
    -- Result: 'Post'
    ```
    
- **`SPLIT_PART(string, delimiter, part_number)`**: Splits a string based on a character you choose (like a comma, space, or `@`) and returns a specific chunk. This is incredibly useful for parsing data.
    
    SQL
    
    ```
    SELECT SPLIT_PART('john.doe@company.com', '@', 2); 
    -- Result: 'company.com'
    ```
    

### 2. Changing Case and Formatting

- **`INITCAP(string)`**: Capitalizes the first letter of _every_ word in the string and makes the rest lowercase. Perfect for cleaning up messy user inputs like names.
    
    SQL
    
    ```
    SELECT INITCAP('mARy jAnE sMITH'); 
    -- Result: 'Mary Jane Smith'
    ```
    
- **`UPPER(string)`**: Converts the entire string to uppercase. (You already saw its sibling, `LOWER`, in your previous task!).
    
    SQL
    
    ```
    SELECT UPPER('urgent action'); 
    -- Result: 'URGENT ACTION'
    ```
    
- **`LPAD(string, target_length, fill_character)`**: "Left Pad". It adds characters to the left of a string until it reaches a specific length. This is commonly used to standardize employee IDs or invoice numbers with leading zeros.
    
    SQL
    
    ```
    SELECT LPAD('42', 5, '0'); 
    -- Result: '00042'
    ```
    

### 3. Inspecting Strings

- **`LENGTH(string)`**: Returns the total number of characters in the string, including spaces and punctuation.
    
    SQL
    
    ```
    SELECT LENGTH('Data Base'); 
    -- Result: 9
    ```
    
- **`POSITION(substring IN string)`**: Finds the starting location (index number) of a specific character or word within a string. If it doesn't exist, it returns `0`.
    
    SQL
    
    ```
    SELECT POSITION('@' IN 'jdoe@test.com'); 
    -- Result: 5
    ```
    

### 4. Combining Strings

- **`CONCAT(string1, string2, ...)`**: While you can use the double pipe `||` to join strings (like we did in your username script), `CONCAT()` is often safer when dealing with missing data. If you use `||` with a `NULL` value, the entire result becomes `NULL`. `CONCAT()` simply ignores the `NULL` and joins the rest.
    
    SQL
    
    ```
    SELECT CONCAT('Hello', ' ', NULL, 'World'); 
    -- Result: 'Hello World'
    ```
    

---

Would you like to try a practice task where we use a combination of `SPLIT_PART` and `INITCAP` to extract and properly format first and last names from a messy email address column?