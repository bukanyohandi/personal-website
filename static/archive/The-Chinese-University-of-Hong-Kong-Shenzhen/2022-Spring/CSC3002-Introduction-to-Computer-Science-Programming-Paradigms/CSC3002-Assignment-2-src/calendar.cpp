/*
 * File: calendar.cpp
 * ------------------
 * This file implements the calendar.h interface
 */

#include "calendar.h"

std::string monthToString(Month month){
    /*
     * Note: There is no way to access the value of the enumerator
     *       key except using X macro. So I decided to use this
     *       naive way.
     */

    switch(month){
        case 1: return "JANUARY";
        case 2: return "FEBRUARY";
        case 3: return "MARCH";
        case 4: return "APRIL";
        case 5: return "MAY";
        case 6: return "JUNE";
        case 7: return "JULY";
        case 8: return "AUGUST";
        case 9: return "SEPTEMBER";
        case 10: return "OCTOBER";
        case 11: return "NOVEMBER";
        case 12: return "DECEMBER";
        default: return "???";
    }
}

int daysInMonth(Month month, int year){
    /*
     * Note: Every month has its respective number of days, except
     *       for FEBRUARY. In a case where a year is a leap year,
     *       the FEBRUARY month has an extra day.
     */

    int days[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return days[month] + (bool)(month == 2 && isLeapYear(year));
}

bool isLeapYear(int year){
    /*
     * Note: A leap year is defined as a year that is divisible
     *       by 400 or divisible by 4 but not divisible by 100.
     */

    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

Month operator++(Month & month, int){
    month = Month(static_cast<std::underlying_type<Month>::type>(month) + 1);
    return month;
}

// Date Constructor
Date::Date(){
    this -> month = JANUARY;
    this -> day = 1;
    this -> year = 1900;
}
Date::Date(int day, Month month, int year){
    this -> month = month;
    this -> day = day;
    this -> year = year;
}
Date::Date(Month month, int day, int year){
    this -> month = month;
    this -> day = day;
    this -> year = year;
}

int Date::getDay(){
    return this -> day;
}
Month Date::getMonth(){
    return this -> month;
}
int Date::getYear(){
    return this -> year;
}

std::string Date::toString(){
    std::string day, month, year;

    day = std::to_string(this -> day);

    month = monthToString(this -> month).substr(0, 3);
    month[1] = tolower(month[1]);
    month[2] = tolower(month[2]);

    year = std::to_string(this -> year);
    while(year.length() < 4){
        year = "0" + year;
    }
    if(year.length() > 4){
        year = year.substr((int)year.length() - 4, 4);
    }

    return day + "-" + month + "-" + year;
}

// The insertion operator <<
std::ostream & operator<<(std::ostream & os, Date date){
    os << date.toString();
    return os;
}

// The relation operators ==, !=, <, <=, >, and >=
bool operator==(Date d1, Date d2){
    return (d1.getYear() == d2.getYear()) && (d1.getMonth() == d2.getMonth()) && (d1.getDay() == d2.getDay());
}
bool operator!=(Date d1, Date d2){
    return !operator==(d1, d2);
}
bool operator<(Date d1, Date d2){
    if(d1.getYear() != d2.getYear()) return d1.getYear() < d2.getYear();
    if(d1.getMonth() != d2.getMonth()) return d1.getMonth() < d2.getMonth();
    return d1.getDay() < d2.getDay();
}
bool operator<=(Date d1, Date d2){
    return !operator>(d1, d2);
}
bool operator>(Date d1, Date d2){
    if(d1.getYear() != d2.getYear()) return d1.getYear() > d2.getYear();
    if(d1.getMonth() != d2.getMonth()) return d1.getMonth() > d2.getMonth();
    return d1.getDay() > d2.getDay();
}
bool operator>=(Date d1, Date d2){
    return !operator<(d1, d2);
}

// The increment and decrement operators ++ and --
Date operator++(Date & date){
    int day = date.getDay();
    Month month = date.getMonth();
    int year = date.getYear();

    day += 1;
    if(day > daysInMonth(month, year)){
        day = 1;
        if(month == DECEMBER){
            month = JANUARY;
            year += 1;
        } else {
            month = Month(month + 1);
        }
    }

    date = Date(day, month, year);
    return date;
}
Date operator++(Date & date, int){
    Date old_date = date;
    ++date;
    return old_date;
}
Date operator--(Date & date){
    int day = date.getDay();
    Month month = date.getMonth();
    int year = date.getYear();

    day -= 1;
    if(day == 0){
        if(month == JANUARY){
            month = DECEMBER;
            year -= 1;
        } else {
            month = Month(month - 1);
        }

        day = daysInMonth(month, year);
    }

    return date;
}
Date operator--(Date & date, int){
    Date old_date = date;
    --date;
    return old_date;
}

// The expression operators + -
Date operator+(Date date, int delta){
    while(delta--)
        date++;
    return date;
}
Date operator-(Date date, int delta){
    while(delta--)
        date--;
    return date;
}
int operator-(Date d1, Date d2){
    if(d1 > d2){
        Date tmp = d1;
        d1 = d2;
        d2 = tmp;
    }
    int ans = 0;
    while(d1 < d2){
        d1++;
        ans += 1;
    }
    return ans;
}

// The shorthand assignment operators
Date & operator+=(Date & date, int delta){
    date = date + delta;
    return date;
}
Date & operator-=(Date & date, int delta){
    date = date - delta;
    return date;
}
