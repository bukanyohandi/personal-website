def sqrt(n):
    nextGuess = 1
    lastGuess = -1
    while abs(nextGuess - lastGuess) >= 0.0001:
        lastGuess = nextGuess
        nextGuess = (lastGuess + n / lastGuess) / 2    
    return nextGuess

def isPalindrome(s):
    return s == s[::-1]

def isPrime(n):
    if n > 2 and n % 2 == 0:
        return False
    for i in range(3, int(sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return n > 1

def isEmirp(n):
    return not(isPalindrome(str(n))) and isPrime(n) and isPrime(int(str(n)[::-1]))

emirps = []
number = 1
while len(emirps) < 100:
    if isEmirp(number):
        emirps.append(number)
    number += 1

for i in range(10):
    for j in range(10):
        for k in range(4 - len(str(emirps[i * 10 + j]))):
            print(end = " ")
        print(emirps[i * 10 + j], end = "\t")
    print("")