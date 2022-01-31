"""
a recursive function to find the depth of the deepest node of a certain value in a binary tree,
for Ryan
"""

from typing import NamedTuple, Optional

class TreeNode(NamedTuple):  # integer binary tree node
    value: int
    left: Optional["TreeNode"]
    right: Optional["TreeNode"]

def opt_increment(z: Optional[int]) -> Optional[int]:
    if z is None: return None
    else:         return z+1

def opt_max(*args: Optional[int]) -> Optional[int]:
    return max((z for z in args if z is not None), default=None)

def deepest_depth(tn: Optional[TreeNode], value: int) -> Optional[int]:
    """returns the depth of the deepest node of a certain value"""
    if tn is None:
        return None
    elif tn.value != value:
        return opt_max(
            opt_increment(deepest_depth(tn.left, value)),
            opt_increment(deepest_depth(tn.right, value))
        )
    else:
        return opt_max(
            0,
            opt_increment(deepest_depth(tn.left, value)),
            opt_increment(deepest_depth(tn.right, value))
        )

if __name__ == "__main__":
    tree = TreeNode(0,
        TreeNode(2,
            TreeNode(1,
                None,
                None
            ),
            None
        ),
        TreeNode(1,
            None,
            TreeNode(1,
                None,
                TreeNode(2,
                    None,
                    None
                )
            )
        )
    )
    assert deepest_depth(tree, 0) == 0
    assert deepest_depth(tree, 1) == 2
    assert deepest_depth(tree, 2) == 3
    assert deepest_depth(tree, 3) == None
    print("passed all tests!")
