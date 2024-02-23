def inputPrompt(description):
    ret = None
    while True:
        inp = input(description)
        if inp.isalpha():
            return inp
        print("The string may only consists of alphabet characters")

def isAnagram(s1, s2):
    if sorted(list(s1)) == sorted(list(s2)):
        return "is an anagram"
    else:
        return "is not an anagram"

s1 = inputPrompt("Enter the first string: ")
s2 = inputPrompt("Enter the second string: ")
print(isAnagram(s1, s2))