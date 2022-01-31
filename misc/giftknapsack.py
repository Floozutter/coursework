"""
a recursive solution to a 0-1 knapsack problem about gifts, for Ryan
"""

from typing import NamedTuple
from collections.abc import Iterable

class Gift(NamedTuple):
    value: int
    weight: int

def max_total_value(gifts: Iterable[Gift], weightlimit: int) -> int :
    """returns the total value of a 0-1 knapsack solution for the gifts"""
    if not gifts:
        return 0
    head, *tail = gifts
    if head.weight > weightlimit:
        return max_total_value(tail, weightlimit)  # head must be excluded
    return max(
        max_total_value(tail, weightlimit-head.weight) + head.value,  # include head
        max_total_value(tail, weightlimit)                            # exclude head
    )

if __name__ == "__main__":
    gifts = (
        Gift(70, 10),
        Gift(80, 15),
        Gift(140, 20),
        Gift(150, 20),
        Gift(200, 30),
    )
    weightlimit = 50
    solution = 360
    assert max_total_value(gifts, weightlimit) == solution
    print("passed all tests!")
