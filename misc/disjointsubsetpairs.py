"""
a program to count the possible pairs of disjoint subsets, for Christian

"Let n be a positive integer and define [n] to be the set of the first n
positive integers. That is, [n] = {1, 2, 3, ... , n}. We want to select two
disjoint, possibly empty subsets A, B of [n]. In how many ways can we do
this?"
"""

from itertools import chain, combinations, product
from collections.abc import Iterator

# "define [n] to be the set of the first n positive integers"
def brackets(n: int) -> frozenset[int]:
    return frozenset(range(1, n+1))

def powerset(s: frozenset[int]) -> frozenset[frozenset[int]]:
    return frozenset(map(frozenset, chain.from_iterable(
        combinations(s, r) for r in range(len(s)+1)
    )))

def disjoint_subset_pairs(s: frozenset[int]) -> Iterator[tuple[frozenset[int], frozenset[int]]]:
    ps = powerset(s)
    return ((a, b) for a, b in product(ps, ps) if a.isdisjoint(b))

if __name__ == "__main__":
    for i in range(10): 
        print(f"|[{i}]| = {len(tuple(disjoint_subset_pairs(brackets(i))))}")
