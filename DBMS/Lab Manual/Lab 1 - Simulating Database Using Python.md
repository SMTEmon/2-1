---
course: CSE 4308 - DBMS Lab
source: Lab Manual PDF
---

# Lab I: Simulating Database Using Python

## 1. Objective
Understand internal implementation of CRUD (Create, Read, Update, Delete) operations using a simple text file (`students.txt`) and Python.

## 2. Implementation Concepts
*   **Data Store:** Text file with pipe-separated values (`ID|Name|Age...`).
*   **Create:** `open(file, 'a')` to append.
*   **Read:** `open(file, 'r')`, iterate lines, `split('|')`.
*   **Update:** Read all lines into memory, modify specific index in list, rewrite entire file.
*   **Delete:** Read all lines, filter out the target ID, rewrite remaining lines.
