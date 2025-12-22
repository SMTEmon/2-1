---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab VII: Introduction to Database Design (ERD)

## 1. Introduction
The database design process transforms real-world data requirements into a physical database implementation.

### 1.1 Design Phases
1.  **Initial Phase (Requirement Analysis):** Characterizing data needs of users. Output: Specification of user requirements.
2.  **Conceptual-Design Phase:** Translating requirements into a conceptual schema using the **Entity-Relationship (ER) model**. Output: ER Diagram (ERD).
3.  **Implementation Phase:**
    *   **Logical Design:** Mapping ER schema to a data model (e.g., Relational Model with tables).
    *   **Physical Design:** Handling storage details, file organization, and indexing.

### 1.2 Common Design Pitfalls
*   **Redundancy:** Storing the same information in multiple places (leads to inconsistency).
*   **Incompleteness:** Failing to model necessary aspects or introducing bad business logic.

---

## 2. The Entity-Relationship (ER) Model

### 2.1 Entity Sets
*   **Entity:** A distinct object (e.g., a person, a car).
*   **Entity Set:** A collection of entities of the same type.
*   **Visual:** Rectangles.
*   **Primary Key:** Underlined attribute.

### 2.2 Attributes
Properties of an entity.
1.  **Simple vs. Composite:**
    *   *Simple:* Cannot be divided (e.g., `ID`).
    *   *Composite:* Has sub-parts (e.g., `Name` -> `First Name`, `Last Name`).
2.  **Single-valued vs. Multi-valued:**
    *   *Single-valued:* One value per entity.
    *   *Multi-valued:* Multiple values (e.g., `Phone`). **Notation:** Double ellipse.
3.  **Derived Attributes:**
    *   Computed from other attributes (e.g., `Age` from `DOB`). **Notation:** Dashed ellipse.

---

## 3. Relationships
Association between entities (e.g., Student *Advisor* Instructor).
*   **Visual:** Diamonds connected by solid lines.

### 3.2 Roles and Recursive Relationships
*   **Recursive Relationship:** An entity set relates to itself (e.g., Course *Prereq* Course).
*   **Roles:** Labels on lines to specify participation (e.g., `Main Course` vs. `Prerequisite`).
*   *Implementation:* Requires a **Self-Join**.

### 3.3 Attributes on Relationships
Attributes can be attached to the relationship diamond (e.g., `Date` of advice).

---

## 4. Constraints and Cardinality

### 4.1 Visual Notation (Arrow Styles)
*   **Directed Line (\rightarrow):** Represents "One".
*   **Undirected Line (—):** Represents "Many".

### 4.2 Mapping Cardinalities
| Type |
Diagram Style |
Description |
| :--- |
: --- |
: --- |
| **One-to-One** |
$\rightarrow$ A, $\rightarrow$ B |
Entity in A associated with at most one in B, and vice versa. |
| **One-to-Many** |
$\rightarrow$ A, — B |
Entity in A associated with many in B. |
| **Many-to-One** |
— A, $\rightarrow$ B |
Entity in A associated with at most one in B. |
| **Many-to-Many** |
— A, — B |
Entities in both sets associated with any number of others. |

### 4.3 Participation Constraints
*   **Total Participation:** Every entity *must* participate. **Notation:** Double line.
*   **Partial Participation:** Some entities may not participate. **Notation:** Single line.

---

## 5. Advanced ER Features

### 5.1 Weak Entity Sets
*   Cannot be uniquely identified by its own attributes alone.
*   Must be associated with a **Strong Entity** (Owner).
*   Uses a **Discriminator** (Partial Key).
*   **Notation:** Double Rectangle (Entity), Double Diamond (Relationship), Dashed Underline (Discriminator).

---

## 6. Implementation: ERD to Tables (Solved Example)

**Scenario:** University Academic System
*   **Strong:** Student, Course
*   **Weak:** Exam (depends on Course)
*   **Multi-valued:** Phone (on Student)
*   **M:N Relationship:** Enrolled (Student-Course) with Grade.

### Conversion Steps
1.  **Strong Entities:** Create tables. Simple attributes become columns.
    *   `Student(S_ID, Name)`
    *   `Course(C_ID, Title)`
2.  **Multi-valued Attributes:** Create a separate table.
    *   Cols: Owner PK + Attribute.
    *   PK: Composite (Owner PK, Attribute).
    *   `Student_Phone(S_ID, Phone_Number)`
3.  **Weak Entities:**
    *   Cols: Partial Key + Strong Entity PK (FK).
    *   PK: Composite (Strong PK, Partial Key).
    *   `Exam(C_ID, Exam_No, Exam_Date)`
4.  **Many-to-Many (M:N) Relationships:** Create a **Junction Table**.
    *   Cols: PK of Entity A + PK of Entity B + Descriptive Attributes.
    *   PK: Composite (PK A, PK B).
    *   `Enrolled(S_ID, C_ID, Grade)`
