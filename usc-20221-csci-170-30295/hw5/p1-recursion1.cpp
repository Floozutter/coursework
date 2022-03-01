#include <cassert>

// Change this function so that it calculates the sum of the digits of n recursively, rather than
// iteratively. You may not use while, for, do while, or goto.
/*
int sumofdigits(unsigned int n) {
    int ans = 0;
    while (n > 0) {
        ans += n % 10;
        n /= 10;
    }
    return ans;
}
*/

int sumofdigits(unsigned int n) {
    return n ? n % 10 + sumofdigits(n / 10) : 0;
}

// Do NOT change the main function.
int main() {
    assert(sumofdigits(0) == 0);
    assert(sumofdigits(5) == 5);
    assert(sumofdigits(76) == 13);
    assert(sumofdigits(123) == 6);
    assert(sumofdigits(999999999) == 81);
    return 0;
}
