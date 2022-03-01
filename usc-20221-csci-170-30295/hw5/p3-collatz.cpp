#include <cassert>

// The Collatz Conjecture states that if you start with a positive integer n, you will eventually
// reach 1 by following this algorithm: if n is odd, multiply it by 3 and add 1. If n is even,
// divide it by 2. Write a recursive function that calculates the number of steps required to
// reduce n down to 1. If n = 1, it should take 0 steps.
int collatz(unsigned int n) {
    return n <= 1 ? 0 : 1 + collatz(n % 2 ? 3*n + 1 : n /2);
}

// Do NOT change the main function.
int main() {
    assert(collatz(1) == 0);
    assert(collatz(2) == 1);
    assert(collatz(3) == 7);
    assert(collatz(7) == 16);
    assert(collatz(1000000) == 152);
    return 0;
}
