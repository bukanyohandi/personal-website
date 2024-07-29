day = 1
cnt = 0
for year in range(1901, 2001):
    for days in [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]:
        day += days
        if (year % 4 == 0 and year % 400 != 0) and days == 28:
            day += 1
        day %= 7
        if day == 0:
            cnt += 1
print(cnt - 1)