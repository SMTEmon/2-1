---
course: "CSE 4307: Database Management Systems"
instructor: Md. Tariquzzaman
---
---

## 1. Structure of Relational Databases

A relational database consists of a collection of **tables** (relations), each assigned a unique name.

### Core Concepts

*   **Relation Instance ($r(R)$):** The "filled form" with real data. It changes over time as rows are added/removed.
    *   *Analogy:* An actual building or the actual ingredients used today.
*   **Relation Schema ($R$):** The logical design or structure. It usually remains static.
    *   *Notation:* `instructor = (ID, name, dept_name, salary)`
    *   *Analogy:* The blueprint or a recipe card.
*   **Tuple:** A row in the table. Represents a specific record.
*   **Attribute:** A column in the table.
*   **Domain:** The set of allowed values for an attribute (e.g., `salary` must be a number).

### Properties
1.  **Atomic Values:** Attribute values must be indivisible (e.g., a phone number is a single string, not a set of numbers).
2.  **Unordered:** The order of rows (tuples) does not matter.
3.  **Null Values:** Represents "unknown" or "not applicable". Note: Nulls cause complications in operations.

> [!INFO] Analogy Table
> | Concept | Analogy |
> | :--- | :--- |
> | **Schema** | Recipe card (design) |
> | **Instance** | Actual ingredients cooked today |
> | **Attribute** | Ingredient slot (e.g., sugar) |
> | **Tuple** | One complete recipe execution |

---

## 2. Keys

Keys are attributes used to identify or relate records.

### Types of Keys
1.  **Super Key:** Any set of attributes that uniquely identifies a tuple. Can contain *extra/unnecessary* attributes.
    *   *Example:* `{ID, name}`
2.  **Candidate Key:** A **minimal** super key. Contains no extra attributes.
    *   *Example:* `{ID}`
3.  **Primary Key:** The specific candidate key chosen by the designer to be the main identifier.
    *   **Constraint:** Cannot be NULL.
4.  **Alternate Key:** Candidate keys that were *not* chosen as the Primary Key.
5.  **Composite Key:** A key consisting of two or more attributes.
6.  **Foreign Key:** An attribute in one table that refers to the **Primary Key** of another table.
    *   *Purpose:* Enforces **Referential Integrity** (Parent-Child relationship).
    *   *Rule:* A value in the referencing table *must* exist in the referenced table.

> [!NOTE] Foreign Key Analogy
> A teacher's record book (referencing) lists a student's roll number. That roll number must actually exist in the main school register (referenced).

---

## 3. Schema Diagrams

A visual representation of the database structure.
*   **Boxes:** Relations (Tables).
*   **Arrows/Lines:** Connections via Foreign Keys.
*   **Underlined Text:** Primary Keys.
*   *Analogy:* A **City Map** where buildings are tables and roads are the connections.

---

## 4. Relational Query Languages

Languages used to request data from the database.

*   **Procedural:** User specifies *what* data is needed and *how* to get it.
*   **Non-Procedural (Declarative):** User specifies *what* is needed, without specifying how (e.g., SQL).

### Pure Languages
1.  **Relational Algebra** (Procedural)
2.  Tuple Relational Calculus (Non-procedural)
3.  Domain Relational Calculus (Non-procedural)

> [!TIP] Chef Analogy
> *   **Procedural:** Chef follows a recipe step-by-step.
> *   **Declarative:** Chef is told "Make Lasagna" and decides the steps themselves.
> *   **Relational Algebra:** The tools (knife, pan, blender) used to build the result.

---

## 5. Relational Algebra

A procedural language consisting of a set of operations.
*   **Input:** One or two relations.
*   **Output:** A new relation.
*   **Concept:** Like **LEGO** pieces; outputs can be chained as inputs to the next operation.

### Basic Operators

#### 1. Select ($\sigma$)
*   **Function:** Filters **rows** (tuples) based on a predicate (condition).
*   **Syntax:** $\sigma_{predicate}(relation)$
*   **Analogy:** Using a "Filter" in Excel.
*   **Example:** Find Physics instructors.
    *   $\sigma_{dept\_name = "Physics"}(instructor)$

#### 2. Project ($\Pi$)
*   **Function:** Selects specific **columns** (attributes) and discards the rest. Removes duplicates.
*   **Syntax:** $\Pi_{A1, A2}(relation)$
*   **Analogy:** Hiding columns in Excel.
*   **Example:** Show only names and salaries.
    *   $\Pi_{name, salary}(instructor)$

#### 3. Cartesian Product ($\times$)
*   **Function:** Combines every tuple of one relation with every tuple of another (all possible pairs).
*   **Syntax:** $r \times s$
*   **Analogy:** Pairing every shirt you own with every pair of pants.
*   **Note:** If attributes have the same name, prefix with relation name (e.g., `instructor.ID`).

#### 4. Join ($\bowtie$)
*   **Function:** Combines related tuples from two relations based on a match condition.
*   **Logic:** Cartesian Product + Select.
*   **Syntax:** $r \bowtie_{\theta} s = \sigma_{\theta}(r \times s)$
*   **Analogy:** The "matchmaker" combining only related pairs.

#### 5. Set Operations
For these to work, relations must be **compatible** (same number of attributes and compatible domains).
*   **Union ($\cup$):** Tuples in $r$ **OR** $s$ (or both).
*   **Intersection ($\cap$):** Tuples in **BOTH** $r$ and $s$.
*   **Set Difference ($-$):** Tuples in $r$ but **NOT** in $s$.

#### 6. Assignment ($\leftarrow$)
*   **Function:** Stores a query result in a temporary variable for complex queries.
*   **Syntax:** $Temp \leftarrow \sigma_{salary > 90000}(instructor)$

#### 7. Rename ($\rho$)
*   **Function:** Gives a name to the results of an expression or renames attributes.
*   **Syntax:** $\rho_{x}(E)$ (names result $x$) or $\rho_{x(A1, A2)}(E)$ (names result $x$ and attributes $A1, A2$).

### Composition & Equivalence
*   **Composition:** Chaining operations together.
    *   $\Pi_{name}(\sigma_{dept\_name="Physics"}(instructor))$
*   **Equivalent Queries:** Different algebra expressions can yield the same result.
    *   "Many paths, one destination."