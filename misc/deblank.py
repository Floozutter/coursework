"""
a recursive function that removes spaces from a string, for Rayan
"""

def deblank(s: str) -> str:
    """returns the string argument without any spaces"""
    if not s:         return ""
    elif s[0] == " ": return deblank(s[1:])
    else:             return s[0] + deblank(s[1:])

if __name__ == "__main__":
    assert deblank("uwu") == "uwu"
    assert deblank(" u w u ") == "uwu"
    print("passed all tests!")
