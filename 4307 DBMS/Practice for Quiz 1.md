# Hard PostgreSQL Practice Questions (Quiz Prep)

**Tags:** #sql #postgres #database #quiz-prep #hard
**Date:** [[2025-12-10]]

---

## 📖 Covered Lectures
This quiz covers the following material:
- [[Lecture 1 - Introduction to Database Management Systems]]
- [[Lecture 2 - Introduction to the Relational Model]]
- [[Lecture 3 - Introduction to SQL]]

---

## 📚 Schema Reference
*Use this schema to solve the problems.*

- **instructor** (`ID`, name, dept_name, salary)
- **teaches** (`ID`, course_id, sec_id, semester, year)
- **student** (`ID`, name, dept_name, tot_cred)
- **takes** (`ID`, course_id, sec_id, semester, year, grade)
- **course** (`course_id`, title, dept_name, credits)
- **section** (`course_id`, `sec_id`, `semester`, `year`, building, room_number, time_slot_id)

---

## 🧠 Questions

### Q1: Correlated Subquery
**Question:** Find the names of all instructors who have a higher salary than the average salary of **their specific** department.

> [!tip] Hint
> You cannot calculate one global average. You need to calculate the average row-by-row based on the current instructor's department.

> [!success]- Solution
> ```sql
> SELECT name 
> FROM instructor I 
> WHERE salary > (
>     SELECT AVG(salary) 
>     FROM instructor 
>     WHERE dept_name = I.dept_name
> );
> ```

---

### Q2: Complex Aggregation (ALL)
**Question:** Find the department(s) that have the **highest average** instructor salary among all departments.

> [!tip] Hint
> You cannot nest aggregates like `MAX(AVG(...))`. Compare the specific group's average against `ALL` other groups' averages.

> [!success]- Solution
> ```sql
> SELECT dept_name 
> FROM instructor 
> GROUP BY dept_name 
> HAVING AVG(salary) >= ALL (
>     SELECT AVG(salary) 
>     FROM instructor 
>     GROUP BY dept_name
> );
> ```

---

### Q3: Relational Division (The "Every" Problem)
**Question:** Find the ID and name of students who have taken **EVERY** course offered by the 'Biology' department.

> [!tip] Hint
> Think about "Double Negation". Find students where there is **no** Biology course that they have **not** taken.

> [!success]- Solution
> ```sql
> SELECT S.ID, S.name 
> FROM student S 
> WHERE NOT EXISTS (
>     (SELECT course_id FROM course WHERE dept_name = 'Biology') 
>     EXCEPT 
>     (SELECT T.course_id FROM takes T WHERE T.ID = S.ID)
> );
> ```

---

### Q4: Conditional Updates (CASE)
**Question:** Update the salary of all instructors in a single command: Increase salary by **5%** if it is **≤ 100,000**, and by **3%** if it is **> 100,000**.

> [!tip] Hint
> If you run two separate queries, the order matters and might corrupt data. Use a `CASE` expression to do it atomically.

> [!success]- Solution
> ```sql
> UPDATE instructor 
> SET salary = CASE 
>     WHEN salary <= 100000 THEN salary * 1.05 
>     ELSE salary * 1.03 
> END;
> ```

---

### Q5: NULL Handling & Coalesce
**Question:** List all departments and the total credits taken by students in that department. If a department has students but no credits recorded (NULL) or no students, display **0** instead of NULL.

> [!tip] Hint
> `SUM` returns `NULL` on empty sets. Wrap the result in a function that checks for nulls.

> [!success]- Solution
> ```sql
> SELECT dept_name, COALESCE(SUM(tot_cred), 0) 
> FROM student 
> GROUP BY dept_name;
> ```

---

### Q6: Precise Pattern Matching
**Question:** Find the names of instructors whose name starts with 'M', ends with 't', and has **exactly 4 characters** in between.

> [!tip] Hint
> `%` matches any string. `_` matches exactly one character.

> [!success]- Solution
> ```sql
> SELECT name 
> FROM instructor 
> WHERE name LIKE 'M____t';
> ```
> *(Note: That is 4 underscores)*

---

### Q7: Set Operations with Duplicates
**Question:** Find the total number of times `CS-101` was taught across Fall 2017 and Spring 2018. If it was taught twice in Fall and twice in Spring, the result should be **4** (not 1).

> [!tip] Hint
> Standard `UNION` removes duplicates. You need the variant that keeps them.

> [!success]- Solution
> ```sql
> SELECT COUNT(*) 
> FROM (
>     SELECT course_id FROM section WHERE semester = 'Fall' AND year = 2017 AND course_id = 'CS-101'
>     UNION ALL
>     SELECT course_id FROM section WHERE semester = 'Spring' AND year = 2018 AND course_id = 'CS-101'
> ) AS combined_sections;
> ```

---

### Q8: The WITH Clause (CTEs)
**Question:** Find the names of departments where the **total** salary of the department is greater than the **average of the total** salaries of all departments.

> [!tip] Hint
> Step 1: Calculate Total per dept. Step 2: Calculate Average of those totals. Step 3: Compare.

> [!success]- Solution
> ```sql
> WITH dept_total (dept_name, value) AS (
>     SELECT dept_name, SUM(salary) FROM instructor GROUP BY dept_name
> ), 
> dept_total_avg (value) AS (
>     SELECT AVG(value) FROM dept_total
> )
> SELECT dept_name 
> FROM dept_total, dept_total_avg 
> WHERE dept_total.value > dept_total_avg.value;
> ```

---

### Q9: Subquery Deletion
**Question:** Delete all instructors who teach in the 'Taylor' building, but ensure you don't delete anyone if the 'Taylor' building doesn't exist (using table relations).

> [!tip] Hint
> Instructor table doesn't have `building`. You need to look up `dept_name` in the `department` table first.

> [!success]- Solution
> ```sql
> DELETE FROM instructor 
> WHERE dept_name IN (
>     SELECT dept_name 
>     FROM department 
>     WHERE building = 'Taylor'
> );
> ```

---

### Q10: Set Difference
**Question:** Find distinct `course_id`s that were offered in Fall 2017 but were **NOT** offered in Spring 2018.

> [!tip] Hint
> You can use `NOT IN` or `NOT EXISTS`, but the set operator for difference is usually cleanest.

> [!success]- Solution
> ```sql
> SELECT course_id FROM section WHERE semester = 'Fall' AND year = 2017
> EXCEPT
> SELECT course_id FROM section WHERE semester = 'Spring' AND year = 2018;
> ```

---

## ⚡ Quick Cheat Sheet

- [ ] **Grouping:** If you SELECT a column + an Aggregate (SUM/COUNT), you **must** `GROUP BY` that column.
- [ ] **Filtering:** `WHERE` is for rows (before grouping). `HAVING` is for groups (after grouping).
- [ ] **Counting:** `COUNT(*)` includes NULLs. `COUNT(attribute)` ignores NULLs.
- [ ] **Logic:** `1 + NULL = NULL`.
- [ ] **Order of Ops:** `FROM` -> `WHERE` -> `GROUP BY` -> `HAVING` -> `SELECT` -> `ORDER BY`.