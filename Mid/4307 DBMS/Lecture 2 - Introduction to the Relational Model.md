---
course: "CSE 4307: Database Management Systems"
instructor: Md. Tariquzzaman
---
## 1. What a Relational Database Really Is

A **relational database** is just a collection of **tables**.

Each table:

- Has **columns** → called **attributes**
- Has **rows** → called **tuples**
- Has a **name**

Example table:

**Instructor**

|ID|name|dept_name|salary|
|---|---|---|---|
|101|Alice|Physics|90000|
|102|Bob|CS|95000|

### Two Important Ideas

- **Schema** → structure/design of the table  
    `Instructor(ID, name, dept_name, salary)`
    
- **Instance** → actual data inside the table (the rows)
    

Schema = blueprint  
Instance = real data

---

## 2. Keys (VERY IMPORTANT)

Keys are about **uniquely identifying rows** and **connecting tables**.

### Super Key

Any set of attributes that can uniquely identify a row.

Example:

- `{ID}`
- `{ID, name}`
- `{ID, dept_name}`
    

⚠️ Super keys may have **extra unnecessary attributes**

---

### Candidate Key

A **minimal** super key  
→ remove anything extra and it still uniquely identifies a row

Example:

- `{ID}` ✅
- `{ID, name}` ❌ (name is extra)
    

A table can have **multiple candidate keys**.

---

### Primary Key

The **one candidate key chosen** to identify rows.

Rules:

- Must be **unique**
- **Cannot be NULL**
    

Example:

- Primary Key = `ID`
    

---

### Alternate Key

Candidate keys that were **not chosen** as the primary key.

If:

- Candidate keys = `{ID}`, `{email}`
- Primary key = `{ID}`
    

Then:

- `{email}` is an **alternate key**
    

---

### Composite Key

A key made from **multiple attributes**.

Example:  
**Enrollment**

|student_id|course_id|grade|
|---|---|---|

Primary Key = `{student_id, course_id}`  
(neither alone is enough)

---

### Foreign Key (CONNECTS TABLES)

A **foreign key** in one table refers to a **primary key** in another table.

Example:

**Student**

|student_id|name|
|---|---|
|1|John|

**Enrollment**

|student_id|course_id|
|---|---|
|1|CS101|

Here:

- `Enrollment.student_id` is a **foreign key**
- It references `Student.student_id`
    

Rule:

> A foreign key value **must exist** in the referenced table

This enforces **referential integrity**.

---

## 3. Relational Algebra (The Core Query Logic)

Relational algebra is:

- **Procedural**
- Operates on tables
- Takes tables as input
- Produces tables as output
    

Think:

> Tables in → operation → table out

---

## 4. The Most Important Relational Algebra Operations

### 1. SELECT (σ) — Filters ROWS

Used when you want **specific rows**.

Syntax:

```
σ_condition(Table)
```

Example:

> Get instructors from Physics

```
σ_dept_name = "Physics"(Instructor)
```

This keeps all columns, but removes rows that don’t match.

---

### 2. PROJECT (Π) — Chooses COLUMNS

Used when you want **specific attributes**.

Syntax:

```
Π_column1, column2(Table)
```

Example:

> Show only names and salaries

```
Π_name, salary(Instructor)
```

Important:

- **Duplicates are removed**
    
- Order doesn’t matter
    

---

### SELECT vs PROJECT (Common Confusion)

|Operation|Filters|
|---|---|
|SELECT (σ)|rows|
|PROJECT (Π)|columns|

---

### 3. CARTESIAN PRODUCT (×) — All Possible Pairs

Combines **every row of one table** with **every row of another table**.

If:

- Table A has 3 rows
    
- Table B has 4 rows
    

Result has:

> 3 × 4 = 12 rows

Example:

```
Instructor × Department
```

⚠️ Rarely used directly because it creates **huge useless tables**

---

### 4. JOIN (⨝) — The Useful Version of ×

A **join** connects related rows.

Definition:

```
R ⨝_condition S = σ_condition(R × S)
```

Example:

> Match instructors with their departments

```
Instructor ⨝ Instructor.dept_name = Department.dept_name Department
```

This:

1. Creates pairs
2. Keeps only matching ones
    

---

### 5. SET OPERATIONS (Like Math Sets)

Requirements:

- Same number of columns
- Same domains
    

#### UNION (∪)

Rows in **either** table

```
CS_Students ∪ Math_Students
```

---

#### INTERSECTION (∩)

Rows in **both** tables

---

#### DIFFERENCE (−)

Rows in first table but **not** in second

```
CS_Students − Graduated_Students
```

---

### 6. RENAME (ρ)

Used to:

- Rename a table
    
- Rename attributes
    
- Avoid ambiguity
    

Example:

```
ρ_S1(Student)
```

Or:

```
ρ_S1(sid, sname)(Student)
```

---

### 7. ASSIGNMENT (←)

Used for **breaking complex queries into steps**.

Example:

```
HighPaid ← σ_salary > 90000(Instructor)
Result ← Π_name(HighPaid)
```

---

## 5. Putting It All Together (Composition)

Example:

> Names of Physics instructors

```
Π_name(σ_dept_name = "Physics"(Instructor))
```

Read inside → out:

1. Filter Physics instructors
2. Show only their names
    

---

## Final Mental Model

- **Tables** are everything
- **Keys** = identity + relationships
- **σ (select)** → rows
- **Π (project)** → columns
- **×** → all combinations (avoid)
- **⨝** → meaningful combinations
- Everything returns a **table**, so you can chain operations
    