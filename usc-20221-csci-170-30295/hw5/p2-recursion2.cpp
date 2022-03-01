#include <cassert>

// Barry Bruin is learning about recursion, and attempted to write a program that recursively
// determines whether a provided integer's digits are in nondecreasing order (that is, they are in
// increasing order, but not necessarily strictly increasing order). As is, the program currently
// always outputs false, asserting that the digits are not in nondecreasing order. Your job is to
// fix the code so that it gives the correct output for all possible inputs. Only make changes
// where the code indicates that they should be made: you should not change the main function, nor
// the start of the helper function. You may not use for, while do while, or goto.
bool nondecreasing(unsigned int a) {
    if (a > 0) {
        // If the recursive call fails, don't bother to check further.
        if (!nondecreasing(a / 10)) {
            return false;
        }
        int last = a % 10;  // The least significant digit.
        int prev = (a / 10) % 10;  // The second least significant digit, 0, if a < 10.
        // Make your changes only below this line.
        if (prev <= last) {
            return true;
        } else {
            return false;
        }
    }
    //return false;  // <--- original
    return true;
}

// Do NOT change the main function.
int main() {
    assert(nondecreasing(5));
    assert(nondecreasing(11));
    assert(!nondecreasing(91));
    assert(nondecreasing(1223334444));
    assert(!nondecreasing(1223323444));
    return 0;
}
