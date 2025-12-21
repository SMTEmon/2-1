--Task 1
select email_addr, substr(email_addr, position('@' in email_addr) + 1) as domail_name from students;

--Task 2
select full_name from Students where extract(year from enrollment_date) = 2023;

--Task 3
select student_id from enrollments where course_code = 'CS102' except select student_id from enrollments where course_code = 'CS101';

--Task 4
select DISTINCT s.full_name, substr(s.email_addr, position('@' in s.email_addr) + 1) as domain from students s inner join gate_logs g on s.student_id = g.person_id where g.location = 'Server Room';

--Task 5
create materialized view MatView_Enrollment_Stats as select course_code, count(student_id) from enrollments group by course_code;