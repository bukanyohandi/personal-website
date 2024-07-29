with open("0022_names.txt", "r") as file:
    content = file.read()
names = content.replace('"', '').split(',')
rank = 1
sm = 0
for name in sorted(names):
    sm += sum([ord(alphabet) - ord('A') + 1 for alphabet in name]) * rank
    rank += 1
print(sm)