from itertools import combinations
from collections import defaultdict

min_support = 100

# Read browsing.txt file
baskets = []
with open('browsing.txt', 'r') as file:
    baskets = [set(line.strip().split()) for line in file]

items_freq = defaultdict(int)
for basket in baskets:
    for item in basket:
        items_freq[item] += 1
items_support = [item for item, freq in items_freq.items() if freq >= min_support]
items_set = set(items_support)
assert(len(items_support) == len(items_set))

# (c) Identify pairs of items (X, Y) such that the support of {X, Y} is at least 100.
pairs_freq = defaultdict(int)
for basket in baskets:
    for pair in combinations(basket, 2):
        if all(item in items_set for item in pair):
            pairs_freq[tuple(sorted(pair))] += 1
pairs_support = [pair for pair, freq in pairs_freq.items() if freq >= min_support]
pairs_set = set(pairs_support)
assert(len(pairs_support) == len(pairs_set))

pairs = []
for X, Y in pairs_set:
    pairs.append((X, Y, pairs_freq[(X, Y)] / items_freq[X]))
    pairs.append((Y, X, pairs_freq[(X, Y)] / items_freq[Y]))
pairs.sort(key = lambda x: (-x[2], x[0]))
print("Top 5 rules for pairs X => Y are listed below.")
for X, Y, conf in pairs[:5]:
    print(X + " => " + Y)

# (d) Identify item triples (X, Y, Z) such that the support of {X, Y, Z} is at least 100.
triples_freq = defaultdict(int)
for basket in baskets:
    for triple in combinations(basket, 3):
        if all(item in items_set for item in triple) and all(tuple(sorted(pair)) in pairs_set for pair in combinations(triple, 2)):
            triples_freq[tuple(sorted(triple))] += 1
triples_support = [triple for triple, freq in triples_freq.items() if freq >= min_support]
triples_set = set(triples_support)
assert(len(triples_support) == len(triples_set))

triples = []
for X, Y, Z in triples_set:
    triples.append(((X, Y), Z, triples_freq[(X, Y, Z)] / pairs_freq[(X, Y)]))
    triples.append(((X, Z), Y, triples_freq[(X, Y, Z)] / pairs_freq[(X, Z)]))
    triples.append(((Y, Z), X, triples_freq[(X, Y, Z)] / pairs_freq[(Y, Z)]))
triples.sort(key = lambda x: (-x[2], x[0], x[0][0], x[0][1]))
print("Top 5 rules for triples (X, Y) => Z are listed below.")
for (X, Y), Z, conf in triples[:5]:
    print("(" + X + ", " + Y + ") => " + Z)
