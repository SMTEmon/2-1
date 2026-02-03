---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab VII: Introduction to Database Design (ERD)

## 1. Introduction
The database design process is a structured approach used to transform real-world data requirements into a physical database implementation. It is crucial to ensure the final system is efficient, consistent, and capable of supporting user needs.

### 1.1 Design Phases
The design process is typically divided into three major phases:
1.  **Initial Phase (Requirement Analysis):** This phase involves characterizing the data needs of prospective database users. The designer interacts with domain experts to generate a specification of user requirements. For instance, in a university context, this might involve identifying that the system needs to store data about students, instructors, and the courses they take.
2.  **Conceptual-Design Phase:** Here, the designer translates the requirements into a conceptual schema. The **Entity-Relationship (ER) model** is the standard tool used for this purpose. The result is an ER Diagram (ERD), which is an abstract representation of the data, independent of the specific database software (like MySQL or Oracle) that will eventually be used.
3.  **Implementation Phase:** This phase moves from the abstract to the concrete:
    *   **Logical Design:** Maps the conceptual ER schema onto the implementation data model (usually the Relational Model, consisting of tables and constraints).
    *   **Physical Design:** Handles storage details, such as file organization and indexing, to optimize performance.

### 1.2 Common Design Pitfalls
A robust design must avoid two specific errors:
*   **Redundancy:** This occurs when the same piece of information is stored in multiple places. It is dangerous because updating the data in one location without updating it in others leads to *data inconsistency*.
*   **Incompleteness:** A design is incomplete if it fails to model necessary aspects of the enterprise or introduces bad business logic, making it impossible to store required information.

## 2. The Entity-Relationship (ER) Model
The ER model represents data as a collection of entities and relationships.

### 2.1 Entity Sets
An **entity** is a distinct object in the real world that is distinguishable from all other objects. Examples include a specific person ("Einstein"), a company, or a course.
An **entity set** is a collection of entities of the same type that share the same properties (e.g., the set of all students).

**Visual Representation:**
*   **Rectangles** represent entity sets.
*   The name of the entity set is placed at the top or center.
*   **Attributes** are listed inside the rectangle.
*   The **Primary Key** (the attribute that uniquely identifies an entity) is <u>underlined</u>.

> *Figure Example:* A Student entity set with attributes `ID` (underlined), `Name`, and `Tot_cred`.

### 2.2 Attributes
Attributes describe the properties of an entity. They are classified as follows:

#### 2.2.1 Simple vs. Composite Attributes
*   **Simple Attribute:** An attribute that cannot be divided further (e.g., `ID`, `Salary`).
*   **Composite Attribute:** An attribute that has meaningful sub-parts. For example, a `Name` attribute might be composed of `First Name`, `Middle Initial`, and `Last Name`.
*   **ERD Notation:** Composite attributes are connected to their parent attribute.

#### 2.2.2 Single-valued vs. Multi-valued Attributes
*   **Single-valued:** The attribute holds a single value for a specific entity.
*   **Multi-valued:** The attribute may hold multiple values (e.g., phone numbers). Multi-valued attribute allows for multiple entries for the same property.
*   **ERD Notation:** Enclosed in a **double ellipse**.

#### 2.2.3 Derived Attributes
*   The value is computed from other attributes (e.g., `Age` from `Date_of_Birth`).
*   **ERD Notation:** Enclosed in a **dashed ellipse**.

## 3. Relationships
A **relationship** is an association between entities. For example, an `advisor` relationship links a `Student` entity with an `Instructor` entity.

### 3.1 Visual Representation
*   **Diamonds** represent relationship sets.
*   **Solid lines** connect the diamond to the participating entity sets.

> *Figure Example:* `Instructor` --< `Advisor` >-- `Student`

### 3.2 Roles and Recursive Relationships

#### 3.2.1 Concept Definition
In most relationships, we connect two *different* entity sets (e.g., a `Student` takes a `Course`). However, sometimes an entity set needs to relate to **itself**. This is called a **recursive relationship**.

**Real-world Logic:** Imagine a single table containing a list of all University Courses.
*   *Course A* (Introduction to C) is a prerequisite for *Course B* (Data Structures).
*   Both A and B belong to the same entity set: **Course**.
*   We are linking a record in the `Course` entity to another record in the *same* `Course` entity.

#### 3.2.2 The Necessity of Roles
Since both participants in the relationship are the same entity set, the meaning of the relationship can become ambiguous. To solve this, we use **Roles**.
*   Roles are labels placed on the relationship lines to specify *how* the entity participates.
*   In the prerequisite example, one instance of the course plays the role of the **Main Course** (the one having a requirement), and the other plays the role of the **Prerequisite** (the requirement itself).

#### 3.2.3 Implementation Note
When mapping this to a database table (Implementation Phase), a recursive relationship typically results in a **Self-Join**. You would add a Foreign Key column (e.g., `prereq_id`) to the `Course` table that references the `course_id` of the same table.

### 3.3 Attributes on Relationships
Attributes can also be assigned to relationships. For instance, in an `Advisor` relationship, we might need to track the `date` the student was assigned to that instructor. This attribute is attached to the diamond.

## 4. Constraints and Cardinality
Mapping cardinality defines the number of entities to which another entity can be associated via a relationship set.

### 4.1 Visual Notation (Arrow Styles)
In standard ER diagrams, the style of the line tip indicates cardinality:
*   **Directed Line (→):** Represents "One".
*   **Undirected Line (—):** Represents "Many" (zero or more).

### 4.2 Types of Mapping Cardinalities

| Type | Description | Diagram Style |
| :--- | :--- | :--- |
| **One-to-One** | An entity in A is associated with at most one in B, and vice versa. | `→` on both sides |
| **One-to-Many** | An entity in A is associated with many in B. An entity in B is associated with at most one in A. | `→` on A, `—` on B |
| **Many-to-One** | An entity in A is associated with at most one in B. An entity in B is associated with many in A. | `—` on A, `→` on B |
| **Many-to-Many** | Entities in both sets can be associated with any number of entities in the other set. | `—` on both sides |

### 4.3 Participation Constraints
*   **Total Participation:** Every entity in the set *must* participate in the relationship. This is indicated by a **double line**.
*   **Partial Participation:** Some entities may not participate. This is indicated by a **single line**.

## 5. Advanced ER Features

### 5.1 Weak Entity Sets
A **weak entity** is an entity that cannot be uniquely identified by its own attributes alone. It typically represents a dependency.
*   It must be associated with a **strong entity** (owner entity).
*   It uses a **discriminator** (partial key) combined with the strong entity's primary key for unique identification.

**Diagram Notation:**
*   **Weak Entity Set:** Double Rectangle.
*   **Identifying Relationship:** Double Diamond.
*   **Discriminator Attribute:** Dashed Underline.

> *Example:* `Loan` depends on `Customer`. `Loan` is the weak entity.

## 6. Implementation: Solved Example (Complex ERD to Tables)
Instead of memorizing abstract rules, let us walk through a complete, solved example of converting a complex ER Diagram into a Relational Schema (SQL Tables).

### 6.1 The Scenario: University Academic System
Consider an ER Diagram representing a university system containing:
*   **Strong Entities:** `Student` and `Course`.
*   **Weak Entity:** `Exam` (Dependent on `Course`).
*   **Multi-valued Attribute:** `Phone` on `Student`.
*   **M:N Relationship:** `Enrolled` (Student takes Course) with a descriptive attribute `Grade`.

### 6.2 Step-by-Step Conversion

#### 6.2.1 Step 1: Strong Entities
Create tables for independent entities. All simple attributes become columns.

```sql
CREATE TABLE Student (
    S_ID INT PRIMARY KEY,
    Name VARCHAR(100)
);

CREATE TABLE Course (
    C_ID VARCHAR(10) PRIMARY KEY,
    Title VARCHAR(100)
);
```

#### 6.2.2 Step 2: Multi-valued Attributes
The `Phone` attribute on `Student` cannot be stored in the main `Student` table (violates 1NF). We create a separate table.
*   **Columns:** Owner's Primary Key + The Attribute itself.
*   **Composite Primary Key:** (`S_ID`, `Phone`).

```sql
CREATE TABLE Student_Phone (
    S_ID INT,
    Phone_Number VARCHAR(15),
    PRIMARY KEY (S_ID, Phone_Number),
    FOREIGN KEY (S_ID) REFERENCES Student(S_ID)
);
```

#### 6.2.3 Step 3: Weak Entities
The `Exam` entity relies on `Course`. It has no unique ID of its own, only `Exam_No` (e.g., Exam 1, Exam 2).
*   **Foreign Key:** Include `C_ID` from `Course`.
*   **Composite Primary Key:** (`C_ID`, `Exam_No`).

```sql
CREATE TABLE Exam (
    C_ID VARCHAR(10),       -- From Strong Entity
    Exam_No INT,            -- Partial Key
    Exam_Date DATE,
    PRIMARY KEY (C_ID, Exam_No),
    FOREIGN KEY (C_ID) REFERENCES Course(C_ID)
    ON DELETE CASCADE       -- If Course is deleted, Exams are deleted
);
```

#### 6.2.4 Step 4: Many-to-Many (M:N) Relationship
The `Enrolled` relationship links `Student` and `Course`. Since it is M:N, we cannot simply add a foreign key to either table. We need a **Junction Table**.
*   **Columns:** FK from Student + FK from Course + Descriptive Attributes (Grade).
*   **Composite Primary Key:** (`S_ID`, `C_ID`).

```sql
CREATE TABLE Enrolled (
    S_ID INT,
    C_ID VARCHAR(10),
    Grade CHAR(2),
    PRIMARY KEY (S_ID, C_ID),
    FOREIGN KEY (S_ID) REFERENCES Student(S_ID),
    FOREIGN KEY (C_ID) REFERENCES Course(C_ID)
);
```

## 7. Key Concepts Breakdown

> [!INFO] **Composite Primary Key**
> A **Composite Primary Key** is a combination of two or more columns that *together* act as the unique identifier for a row. This is common when a single column isn't enough to be unique.
> 
> *   **How it works:** In `PRIMARY KEY (S_ID, Phone_Number)`, `S_ID` can repeat, and `Phone_Number` can repeat, but the *pair* must be unique.
> 
> | S_ID | Phone_Number | Valid? | Explanation |
> | :--- | :--- | :--- | :--- |
> | 101 | 555-0001 | **YES** | First entry. |
> | 101 | 555-0002 | **YES** | Same Student (101), different phone. |
> | 102 | 555-0001 | **YES** | Different student, same phone. |
> | 101 | 555-0001 | **NO** | **ERROR.** (101, 555-0001) already exists. |
> 
> *   **Use Case:** Multi-valued attributes (one student has many phones) or Junction Tables (one student takes many courses).
> *   **Syntax:** Must be defined at the bottom of the table: `PRIMARY KEY (Col1, Col2)`.

> [!WARNING] **The Purpose of Foreign Keys**
> While Primary Keys handle uniqueness *inside* a table, **Foreign Keys** manage relationships *outside* the table.
> 
> *   **The Guard:** `FOREIGN KEY (S_ID) REFERENCES Student(S_ID)` prevents you from adding a phone number for a student ID that doesn't exist. It ensures referential integrity (no "fake" students).
> *   **The Cleaner:** It allows automatic cleanup operations like Cascade Delete.

> [!DANGER] **Cascade Delete (ON DELETE CASCADE)**
> By default, a database stops you from deleting a record (e.g., a Student) if other tables reference it (e.g., Student_Phone). This is to prevent orphaned data.
> 
> **How to configure:**
> ```sql
> FOREIGN KEY (S_ID) REFERENCES Student(S_ID) ON DELETE CASCADE
> ```
> *   **What it does:** If you delete a Student from the main table, the database *automatically* deletes all their associated records in the child table (e.g., all their phone numbers).
