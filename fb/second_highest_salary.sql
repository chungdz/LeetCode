/*
176 Second Highest Salary

Table: Employee

+-------------+------+
| Column Name | Type |
+-------------+------+
| Id          | int  |
| Salary      | int  |
+-------------+------+
Id is the primary key column for this table.
Each row of this table contains information about the salary of an employee.
 

Write an SQL query to report the second highest salary from the Employee table. If there is no second highest salary, the query should report null.

The query result format is in the following example.

 

Example 1:

Input: 
Employee table:
+----+--------+
| Id | Salary |
+----+--------+
| 1  | 100    |
| 2  | 200    |
| 3  | 300    |
+----+--------+
Output: 
+---------------------+
| SecondHighestSalary |
+---------------------+
| 200                 |
+---------------------+
Example 2:

Input: 
Employee table:
+----+--------+
| Id | Salary |
+----+--------+
| 1  | 100    |
+----+--------+
Output: 
+---------------------+
| SecondHighestSalary |
+---------------------+
| Null                |
+---------------------+

MS SQL语法：
从第N + 1行开始选择M行
OFFSET N ROWS
FETCH FIRST M ROWS ONLY

如果是NULL返回VALUE
ISNULL(Variable, VALUE)
*/

SELECT ISNULL((
    SELECT DISTINCT Salary
    FROM Employee
    ORDER BY Salary DESC 
    OFFSET 1 ROWS
    FETCH FIRST 1 ROWS ONLY), 
    NULL) as SecondHighestSalary;