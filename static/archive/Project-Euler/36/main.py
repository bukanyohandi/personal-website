def is_palindrome(s):
    return s == s[::-1]
sm = 0
for i in range(1, 1000000):
    if is_palindrome(str(i)) and is_palindrome(str(bin(i))[2:]):
        sm += i
print(sm)