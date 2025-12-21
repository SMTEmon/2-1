-- ================================================================
-- Lab 6 Tasks Solutions
-- Context: University management system (Students, Enrollments, Gate_Logs, etc.)
-- ================================================================

-- Task 1: Extract the domain name from the email addresses.
-- Uses POSITION to find '@' and SUBSTR to extract the text after it.
SELECT 
    email_addr,
    SUBSTR(email_addr, POSITION('@' IN email_addr) + 1) AS domain_name
FROM Students;

-- Task 2: Find the names of students who enrolled in the year 2023.
-- Uses EXTRACT(YEAR ...) in the WHERE clause.
SELECT full_name 
FROM Students 
WHERE EXTRACT(YEAR FROM enrollment_date) = 2023;

-- Task 3: Find the Student IDs of those who are taking 'CS102' but are NOT taking 'CS101'.
-- Uses the EXCEPT set operator.
SELECT student_id 
FROM Enrollments 
WHERE course_code = 'CS102'
EXCEPT
SELECT student_id 
FROM Enrollments 
WHERE course_code = 'CS101';

-- Task 4: Display the full_name of students and the domain of their email, 
-- but only for students who have visited the 'Server Room'.
-- Joins Students with Gate_Logs and applies the domain extraction logic.
SELECT DISTINCT
    S.full_name,
    SUBSTR(S.email_addr, POSITION('@' IN S.email_addr) + 1) AS domain
FROM Students S
JOIN Gate_Logs G ON S.student_id = G.person_id
WHERE G.location = 'Server Room';

-- Task 5: Create a Materialized View named MatView_Enrollment_Stats 
-- that counts how many students are in each course.
CREATE MATERIALIZED VIEW MatView_Enrollment_Stats AS
SELECT 
    course_code, 
    COUNT(student_id) AS total_students
FROM Enrollments
GROUP BY course_code;
