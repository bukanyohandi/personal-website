SELECT EMPLOYEE_ID
FROM employees E, departments D
WHERE E.EMPLOYEE_ID = D.MANAGER_ID AND E.EMPLOYEE_ID NOT IN (
	SELECT MANAGER_ID FROM EMPLOYEES
);