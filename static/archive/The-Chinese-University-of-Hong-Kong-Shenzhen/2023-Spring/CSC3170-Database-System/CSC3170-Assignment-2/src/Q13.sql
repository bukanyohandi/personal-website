SELECT EMPLOYEE_ID, SALARY
FROM employees E
WHERE
	(SELECT COUNT(DISTINCT SALARY)
	FROM employees
	WHERE SALARY <= E.SALARY) = 4;