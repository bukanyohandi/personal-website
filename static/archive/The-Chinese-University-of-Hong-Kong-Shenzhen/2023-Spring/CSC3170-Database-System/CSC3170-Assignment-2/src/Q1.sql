SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

DROP SCHEMA IF EXISTS `as3` ;
CREATE SCHEMA IF NOT EXISTS `as3` DEFAULT CHARACTER SET utf8 ;
USE `as3` ;

-- -----------------------------------------------------
-- Create below: Table `as3`.`regions`
-- -----------------------------------------------------
DROP TABLE IF EXISTS regions;
CREATE TABLE regions(
	REGION_ID decimal(5, 0) NOT NULL,
    REGION_NAME varchar(25) NOT NULL,
    
    PRIMARY KEY (REGION_ID)
);

-- DESCRIBE regions; 

-- -----------------------------------------------------
-- Create below: Table `as3`.`countries`
-- -----------------------------------------------------
DROP TABLE IF EXISTS countries;
CREATE TABLE countries(
	COUNTRY_ID varchar(2) NOT NULL,
    COUNTRY_NAME varchar(255) NOT NULL,
	REGION_ID decimal(5, 0) NOT NULL,
    
    PRIMARY KEY (COUNTRY_ID)
);

-- DESCRIBE countries;

-- -----------------------------------------------------
-- Create below: Table `as3`.`locations`
-- -----------------------------------------------------
DROP TABLE IF EXISTS locations;
CREATE TABLE locations(
	LOCATION_ID decimal(4, 0) NOT NULL,
    STREET_ADDRESS varchar(40),
    POSTAL_CODE varchar(12),
    CITY varchar(30) NOT NULL,
    STATE_PROVINCE varchar(25),
    COUNTRY_ID varchar(2) NOT NULL,
    
    PRIMARY KEY (LOCATION_ID)
);

-- DESCRIBE locations;

-- -----------------------------------------------------
-- Create below: Table `as3`.`jobs`
-- -----------------------------------------------------
DROP TABLE IF EXISTS jobs;
CREATE TABLE jobs(
	JOB_ID varchar(10) NOT NULL,
    JOB_TITLE varchar(35) NOT NULL,
    MIN_SALARY decimal(6, 0),
    MAX_SALARY decimal(6, 0),
    
    PRIMARY KEY (JOB_ID)
);

-- DESCRIBE jobs;

-- -----------------------------------------------------
-- Create below: Table `as3`.`employees`
-- -----------------------------------------------------
DROP TABLE IF EXISTS employees;
CREATE TABLE employees(
	EMPLOYEE_ID decimal(6, 0) NOT NULL,
    FIRST_NAME varchar(20),
    LAST_NAME varchar(25) NOT NULL,
    EMAIL varchar(255) NOT NULL,
	PHONE_NUMBER varchar(20),
    HIRE_DATE date NOT NULL,
    JOB_ID varchar(10) NOT NULL,
    SALARY decimal(8, 2) NOT NULL,
    COMMISSION_PCT decimal(3, 2) NOT NULL,
    MANAGER_ID decimal(6, 0) NOT NULL,
    DEPARTMENT_ID int NOT NULL,
    
    PRIMARY KEY (EMPLOYEE_ID)
);

-- DESCRIBE employees;

-- -----------------------------------------------------
-- Create below: Table `as3`.`departments`
-- -----------------------------------------------------
DROP TABLE IF EXISTS departments;
CREATE TABLE departments(
	DEPARTMENT_ID int NOT NULL,
    DEPARTMENT_NAME varchar(255) NOT NULL,
    MANAGER_ID decimal(6, 0),
    LOCATION_ID decimal(4, 0) NOT NULL,
    
    PRIMARY KEY (DEPARTMENT_ID)
);

-- DESCRIBE departments;

-- -----------------------------------------------------
-- Create below: Table `as3`.`job_history`
-- -----------------------------------------------------
DROP TABLE IF EXISTS job_history;
CREATE TABLE job_history(
	EMPLOYEE_ID decimal(6, 0) NOT NULL,
    START_DATE date NOT NULL,
    END_DATE date NOT NULL,
	JOB_ID varchar(10) NOT NULL,
    DEPARTMENT_ID int NOT NULL
);

-- DESCRIBE job_history;

-----------------------------------------------------
-- End of coding
-- -----------------------------------------------------

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
