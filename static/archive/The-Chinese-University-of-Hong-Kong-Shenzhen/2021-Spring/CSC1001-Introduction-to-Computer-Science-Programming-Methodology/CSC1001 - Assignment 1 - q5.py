def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        for cast in [int]:
            try:
                ret = cast(inp)
                if ret > 1:
                    return ret
                else:
                    print("The integer should be larger than 1")
            except ValueError:
                print("The input should be an integer number")
                pass

N = inputPrompt("N = ")
isPrime = [True for i in range(N)]
primes = []
isPrime[1] = False
for i in range(2, N):
    if isPrime[i]:
        primes.append(i)
        for j in range(2 * i, N, i):
            isPrime[j] = False
print("The prime numbers smaller than", N, "include:", end = '')
for i in range(len(primes)):
    if i % 8 == 0:
        print("")
    else:
        print(" ", end = '')
    print(primes[i], end = '')