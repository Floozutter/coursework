"""
a recursive implementation of mergesort, for Ryan (not Rayan)
"""

from typing import Any, TypeVar
from typing_extensions import Protocol
from abc import abstractmethod

# https://github.com/python/typing/issues/59#issuecomment-353878355
C = TypeVar("C", bound="Comparable")
class Comparable(Protocol):
    @abstractmethod
    def __lt__(self: C, other: C) -> bool: ...

def merge(a: list[C], b: list[C]) -> list[C]:
    """merges two lists that are sorted in ascending order"""
    if   not a:       return b
    elif not b:       return a
    elif a[0] < b[0]: return a[0:1] + merge(a[1:], b)
    else:             return b[0:1] + merge(a, b[1:])

def mergesort(lst: list[C]) -> list[C]:
    """returns the list sorted using mergesort"""
    n = len(lst)
    if n < 2: return lst
    else:     return merge(mergesort(lst[:n//2]), mergesort(lst[n//2:]))

if __name__ == "__main__":
    from random import random
    for n in (0, 1, 2, 17, 100):
        lst = [random() for _ in range(n)]
        assert sorted(lst) == mergesort(lst)
    print("passed all tests!")
