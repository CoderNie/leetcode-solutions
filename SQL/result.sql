/* 175. Combine Two Tables */
SELECT
	Person.FirstName AS FirstName,
	Person.LastName AS LastName,
	Address.City AS City,
	Address.State As State
FROM
	Person
LEFT JOIN
	Address
ON
	Person.PersonId = Address.PersonId

/* 176. Second Highest Salary */
SELECT
  IFNULL(
    (
      SELECT DISTINCT
        Salary
      FROM
        Employee
      ORDER BY Salary DESC
      LIMIT 1 OFFSET 1
    ),
  NULL) AS SecondHighestSalary

SELECT
  (
    SELECT DISTINCT
      Salary
    FROM
      Employee
    ORDER BY Salary DESC
    LIMIT 1 OFFSET 1
  ) AS SecondHighestSalary


/* 177. Nth Highest Salary */
DELIMITER //
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N - 1;
  RETURN (
    IFNULL(
    (
      SELECT DISTINCT
        Salary
      FROM
        Employee
      ORDER BY Salary DESC
      LIMIT 1 OFFSET N
    ),
    NULL)
  );
END //

/* 178. Rank Scores */
SELECT 
  Score, 
  @i := @i + (@pre <> ( @pre := Score)) AS Rank 
FROM 
  Scores, 
  (SELECT @i := 0,@pre := -1) INIT
ORDER BY Score DESC
