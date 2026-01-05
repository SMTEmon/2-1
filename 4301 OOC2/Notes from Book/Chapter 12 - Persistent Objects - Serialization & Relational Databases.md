**Source Material:** Chapter 12 (Pages 225 - 246)
**Tags:** #Programming #Java #CSharp #Databases #Serialization #JDBC #XML #OOP

---

## 1. Persistent Objects Basics
### The Problem: Object Scope
In a traditional application, an object (e.g., `Employee`) lives only as long as the application is running. When the application terminates, the object and its state (attributes like `name`, `ss#`) are lost.

### The Solution: Persistence
**Persistence** is the concept of saving the state of an object so it can be restored and used later, independent of the single application instance that created it.

#### Object Life Cycle Comparison

**Traditional Life Cycle:**
```mermaid
graph LR
    A[Start App] --> B[Instantiate Object]
    B --> C[Use Object]
    C --> D[End App]
    D --> E((Object Destroyed))
    style E fill:#f9f,stroke:#333,stroke-width:2px
```

**Persistent Life Cycle:**
```mermaid
graph LR
    subgraph App 1
    A[Create Object] --> B[Write to Storage]
    end
    
    B --> DB[(Persistent Storage)]
    
    subgraph App 2
    DB --> C[Read/Load Object]
    C --> D[Instantiate Replica]
    end
```

### Storage Mechanisms
There are three main ways to save an object's state:
1.  **Flat File:** Simple file managed by the OS (Text/Binary).
2.  **Relational Database (RDBMS):** Tables and Rows (SQL Server, Oracle, Access).
3.  **Object Database:** Specialized DB designed to store objects directly.

---

## 2. Serialization: Saving to a Flat File

**Definition:** Serialization is the process of decomposing an object into a stream of bytes to store it in a file or memory.

### Challenges with Flat Files
1.  **Reconstitution:** An object isn't just a list of variables; it is a unit. Putting it back together requires knowing the exact order and types.
2.  **Composition:** Objects often contain *other* objects (e.g., a `Car` contains `Engine` and `Wheels`). Serialization must handle the entire object graph.

### Java Implementation (Binary Serialization)
Java uses a proprietary mechanism involving Streams.

*   **Interface:** Objects must implement `Serializable` (a marker interface with no methods).
*   **Classes Used:** `FileOutputStream`, `ObjectOutputStream`, `FileInputStream`, `ObjectInputStream`.

> [!INFO] What about Methods?
> Serialization saves **attributes** (data), not methods. The class definition (code) must exist on both the "saving" and "loading" ends of the application for the object to be restored.

#### Java Code Example: Writing
```java
// Step 1: Mark class as Serializable
public class Person implements Serializable {
    private String name;
    // ... constructor and getters
}

// Step 2: Write object to disk
Person p = new Person("Jack Jones");
try {
    FileOutputStream fos = new FileOutputStream("Name.txt");
    ObjectOutputStream oos = new ObjectOutputStream(fos);
    oos.writeObject(p); // The Magic Line
    oos.flush();       // Forces any buffered data to the file
    oos.close();       // Closes the stream and releases resources
} catch (Exception e) { e.printStackTrace(); }
```

> [!TIP] Why use `flush()`?
> Output streams often use a **buffer** (temporary memory) to store data before writing it to disk to improve performance. `flush()` ensures that all data currently in that buffer is immediately pushed out to the destination file. While `close()` usually calls `flush()` automatically, explicit flushing is a best practice to ensure data integrity.

#### Java Code Example: Reading
```java
// Step 3: Read object from disk
FileInputStream fis = new FileInputStream("Name.txt");
ObjectInputStream ois = new ObjectInputStream(fis);
// Must cast the object back to its class
Person p = (Person) ois.readObject(); 
```

### Handling Multiple Objects
When multiple objects are stored in a file, `readObject()` retrieves them one by one in the order they were written.

**Option A: Read until EOF (Loop)**
```java
try {
    while (true) {
        Person p = (Person) ois.readObject();
        // Process p
    }
} catch (EOFException e) {
    // End of file reached
}
```

**Option B: Store a Collection (Recommended)**
Write a single `List<Person>` object. Reading it back retrieves all data in one call.
```java
// Write: oos.writeObject(myListOfPeople);

// Read:
List<Person> people = (List<Person>) ois.readObject();
for (Person p : people) {
    // Process p
}
```

---

## 3. XML Serialization (Cross-Platform)

While binary serialization is efficient, it is proprietary. **XML** allows objects to be shared between different languages (e.g., Java writing a file that C# reads).

### Key Concepts
*   **Portability:** XML is text-based and standard.
*   **Encapsulation:** In C#/.NET, XML serialization works closely with Properties (Getters/Setters).
*   **Metadata:** Uses **Attributes** (decorators) to define how the XML should look.

### C# .NET Implementation
The framework uses the `System.Xml.Serialization` namespace.

**Attributes used:**
*   `[XmlRoot("person")]`: Defines the root element.
*   `[XmlAttribute("name")]`: Maps a property to an XML attribute.
*   `[XmlElement("age")]`: Maps a property to a nested XML element.

#### C# Code Structure
```csharp
[XmlRoot("person")]
public class Person {
    private String strName;

    // The XML Serializer uses this Property to get/set data
    [XmlAttribute("name")]
    public String Name {
        get { return this.strName; }
        set { this.strName = value; }
    }
}
```

#### Generated XML Output
```xml
<?xml version="1.0" encoding="utf-8"?>
<person name="John Q. Public">
    <age>32</age>
</person>
```

---

## 4. Relational Databases (RDBMS)

Relational databases are the industry standard (e.g., Microsoft Access, SQL Server, Oracle).

### The Challenge: Impedance Mismatch
*   **Databases** use Tables, Rows, and Columns (Relational Model).
*   **Applications** use Classes, Objects, and Inheritance (Object Model).
*   **Legacy Data:** Most companies have massive amounts of existing data in RDBMS. You cannot simply switch to Object Databases; you must write code to map objects to tables.

### Architecture: Client/Server
The application acts as the Client, communicating with the Database Server via a Driver.

```mermaid
flowchart LR
    User["User App"] <--> JDBC["Driver (JDBC/ODBC)"]
    JDBC <--> DB[("Database Server")]
```

### JDBC (Java Database Connectivity)
Java uses the `java.sql` package to interact with databases. It often bridges to **ODBC** (Open Database Connectivity), a Microsoft standard that abstracts specific vendor protocols.

#### The 4 Main JDBC Components
1.  **DriverManager:** Loads the specific driver for the DB (e.g., Access, Oracle).
2.  **Connection:** Establish the link to the DB.
3.  **Statement:** Container for SQL commands.
4.  **ResultSet:** Holds the data returned by a query.

#### The Connection Process
```mermaid
sequenceDiagram
    participant App as Java App
    participant DM as DriverManager
    participant DB as Database
    
    App->>DM: 1. Class.forName("DriverName")
    App->>DM: 2. getConnection(URL, User, Pass)
    DM->>DB: Connect
    DB-->>App: Connection Object
    App->>DB: 3. createStatement()
    App->>DB: 4. executeQuery(SQL)
    DB-->>App: ResultSet
    App->>App: 5. Iterate ResultSet (rs.next)
    App->>DB: 6. close()
```

---

## 5. SQL Implementation Details

### SQL Statements
*   **Queries:** Use `executeQuery()`. Used for `SELECT`. Returns a `ResultSet`.
*   **Updates:** Use `executeUpdate()`. Used for `INSERT`, `UPDATE`, `DELETE`. Returns generic success/fail info.

### Important SQL Syntax Note
> [!WARNING] Strings in SQL
> SQL uses **single quotes** (`'`) to delineate strings, unlike Java/C# which use double quotes (`"`).
> *   **Incorrect:** `WHERE Product = "Bolts"`
> *   **Correct:** `WHERE Product = 'Bolts'`

### Iterating Results
The `ResultSet` acts like a cursor.
```java
// Iterate through all rows
while (rs.next()) {
    // Retrieve column by name
    String id = rs.getString("SUPPLIERID");
    System.out.println(id);
}
```

---

## 6. Comprehensive Code Examples

### Java: JDBC Complete Example
```java
public void findVendor(String vendorId) throws SQLException {
    // 1. Load Driver
    Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
    
    // 2. Connect
    String url = "jdbc:odbc:myDriver";
    Connection conn = DriverManager.getConnection(url, "user", "password");
    
    // 3. Create Statement
    Statement stmt = conn.createStatement();
    
    // 4. Build Query (Note single quotes for SQL string)
    String sql = "SELECT PRODUCT FROM SUPPLIERTABLE WHERE PRODUCT = 'Bolts'";
    
    // 5. Execute
    ResultSet rs = stmt.executeQuery(sql);
    
    // 6. Process Results
    while (rs.next()) {
        System.out.println(rs.getString("SUPPLIERID"));
    }
    
    // 7. Clean up
    stmt.close();
    conn.close();
}
```

### C# .NET: XML Serialization Example
```csharp
using System;
using System.IO;
using System.Xml.Serialization;

[XmlRoot("person")]
public class Person {
    [XmlAttribute("name")]
    public string Name { get; set; }
    
    [XmlElement("age")]
    public int Age { get; set; }
    
    // Constructor required for serialization
    public Person() {} 
}

public class Program {
    public static void Serialize() {
        Person[] people = new Person[2];
        people[0] = new Person { Name = "John", Age = 32 };
        people[1] = new Person { Name = "Jane", Age = 35 };

        XmlSerializer serializer = new XmlSerializer(typeof(Person[]));
        TextWriter writer = new StreamWriter("person.xml");
        
        serializer.Serialize(writer, people);
        writer.Close();
    }

    public static void Deserialize() {
        XmlSerializer serializer = new XmlSerializer(typeof(Person[]));
        TextReader reader = new StreamReader("person.xml");
        
        Person[] loadedPeople = (Person[])serializer.Deserialize(reader);
        
        foreach(Person p in loadedPeople) {
            Console.WriteLine(p.Name + " is " + p.Age);
        }
    }
}
```