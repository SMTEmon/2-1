---
tags: [database, dbms, cse4307, lecture1, data_management]
aliases: [DBMS Introduction, Database Management Systems, Data Abstraction]
---
## 1. The Problem with File Systems (Motivation)

The "Kingdom of Kod" analogy highlights the inefficiencies of traditional, flat-file data management:

* **Data Duplication & Waste:** Each department (Merchandise, Overseas Business, Export) independently enters, stores, and prints the same data, leading to wasted effort and storage.
* **Data Inconsistency/Conflict:** If data changes (e.g., product price), separate updates are required for every department. Failures to update or incorrect updates cause conflicting information across the system.
* **Difficulty in Updating/Adding New Projects:** Starting a new department requires creating new, separate files, increasing complexity and duplication.

***

> [!summary] **The Solution**
> A **[[Database]]** provides **uniform data management** from a single source, which **prevents data conflicts**, **eliminates duplicated data**, and allows for **easy integration** of new departments.

## 2. Database Management System (DBMS)

### 2.1 Definition & Function

* **Definition:** A specialized software system designed to **store, organize, and manage large amounts of data efficiently**.
* **Function:** Acts as an interface for users and applications to perform **C**reate, **R**etrieve, **U**pdate, and **D**elete (**CRUD**) operations.
* **Goal:** Ensure data is **consistent, secure, and easily accessible**, even with simultaneous user access.
* **Examples:** MySQL, PostgreSQL, Oracle Database, MongoDB.

### 2.2 DBMS Solves File System Problems

| Problem in File Systems | Solution Offered by DBMS |
| :--- | :--- |
| **Data Redundancy & Inconsistency** | Centralized storage eliminates duplication. |
| **Difficulty in Accessing Data** | Query languages (SQL) simplify data retrieval. |
| **Data Isolation** | Provides a single, unified view of the data. |
| **Integrity Problems** | Constraints (e.g., `balance > 0`) are defined explicitly in the schema. |
| **Atomicity of Updates** | Transactions ensure updates either complete entirely or not at all (e.g., a funds transfer). |
| **Concurrent Access by Multiple Users** | Concurrency-control manager prevents inconsistencies during simultaneous updates. |
| **Security Problems** | Provides fine-grained access control (authorization management). |

***

## 3. Key Concepts

### 3.1 Data Model, Schema, and Instance

* **Data:** Raw facts that can be recorded and have meaning.
* **Database:** A logically coherent collection of data designed for a specific purpose.
* **Data Model:** A conceptual framework describing data, relationships, and constraints.
    * *Examples:* [[Relational Model]] (tables), [[Entity-Relationship Model]] (conceptual design).
* **Schema (Blueprint):** The overall design or structure of a database.
    * *Logical Schema:* The overall structure (what data is stored).
    * *Physical Schema:* The overall physical storage structure.
* **Instance (Content):** The actual content of the database at a particular point in time (the data values).

### 3.2 Data Abstraction (View of Data)

A DBMS hides storage complexity by presenting three levels of abstraction:

| Level | Focus | Description | Users |
| :--- | :--- | :--- | :--- |
| **3. View Level** | Highest | Presents only the relevant portion of the database to specific users for simplicity and security. | Naïve Users, Sophisticated Users |
| **2. Logical Level** | Intermediate | Describes **what** data is stored and its relationships using simple structures (tables, records). | DBA, Application Programmers |
| **1. Physical Level** | Lowest | Describes **how** the data is actually stored (byte-level details, indexes, files). | Internal DBMS components |

* **Key Concept:** **Physical Data Independence** - The ability to modify the physical storage structure (*Physical Schema*) without changing the overall logical structure (*Logical Schema*).

## 4. Database Languages

| Language | Acronym | Purpose | Example |
| :--- | :--- | :--- | :--- |
| **Data Definition Language** | **DDL** | Defines the database structure (schema) and constraints. | `CREATE TABLE`, `ALTER TABLE` |
| **Data Manipulation Language** | **DML** | Used to access and modify the data in the database. | `SELECT`, `INSERT`, `UPDATE`, `DELETE` |

> [!info] **SQL (Structured Query Language)**
> * SQL combines DDL and DML capabilities.
> * It is a **declarative (nonprocedural)** query language, meaning the user specifies *what* data is needed, not *how* to get it.

## 5. Database Engine Components

The core components that manage the database's operation:

1.  **Storage Manager:**
    * Interface between low-level data and application programs.
    * Responsible for efficient storage, retrieval, and updates.
    * Manages **Data files**, the **Data dictionary** (metadata), and **Indices** (for fast access).
2.  **Query Processor:**
    * **DML Compiler:** Translates SQL into an execution plan, performing **Query Optimization** to find the most efficient plan.
    * **Query Evaluation Engine:** Executes the low-level instructions generated by the compiler.
3.  **Transaction Manager:**
    * Ensures the database remains **consistent** despite system failures (e.g., crashes) and concurrent access.
    * Includes the **Concurrency-Control Manager**.

***

## 6. Database Users and Administrator

### Database Users
1.  **Naïve Users:** Use predefined interfaces (e.g., web forms).
2.  **Application Programmers:** Write programs and application logic that interact with the database.
3.  **Sophisticated Users:** Interact directly using query languages (SQL) or analysis tools (e.g., data analysts).

### Database Administrator (DBA)
The DBA has central control over data and access programs.
**Key Responsibilities:**
1.  **Schema Definition** (Logical and Physical).
2.  **Authorization Management** (Security control).
3.  **Schema and Physical Organization Modification.**
4.  **Routine Maintenance** (Backup, recovery, performance tuning).