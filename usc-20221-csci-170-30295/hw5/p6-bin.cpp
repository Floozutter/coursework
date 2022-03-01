#include <cassert>

// A function that takes in a positive integer "n", then outputs the number of n-digit binary
// numbers having at least as many 1s as 0s for any prefix of the number. That is, at any point
// while reading the number left to right, you've always seen at least as many 1s as 0s. So, the
// first digit must be 1, the first two digits must be either 11 or 10, the first three digits must
// be 111, 110, or 101, etc. This program should output the count of total binary numbers that
// satisfy the constraint. Example: For n = 4, the binary numbers that satisfy the given
// constraints are 1111, 1110, 1101, 1100, 1011, 1010. Notice that 1001 is not part of the solution
// set as the first three digits break the constraint. If you try to call your function on inputs
// larger than about 25, it will take a very, very long time. As with several of the other
// problems, you will likely want a helper function. You may not use for, while, do while, or goto.
int count_valid_binary_numbers_of_width(unsigned int n) {
    auto const & binomial{[](unsigned int n, unsigned int k) -> unsigned int {
        auto const & r{[](auto const & r, unsigned int n, unsigned int k) -> unsigned int {
            return k == 0 || k == n ? 1 : r(r, n-1, k-1) + r(r, n-1, k);
        }};
        return r(r, n, k);
    }};
    return binomial(n, n/2);  // yes this actually works uwu
}

// Do NOT change the main function.
int main() {
    auto const & c{count_valid_binary_numbers_of_width};
    assert(c(1) == 1);   // 1
    assert(c(2) == 2);   // 10, 11
    assert(c(3) == 3);   // 101, 110, 111
    assert(c(4) == 6);   // 1010, 1011, 1100, 1101, 1110, 1111
    assert(c(5) == 10);  // 10101, 10110, 10111, 11001, 11010, 11011, 11100, 11101, 11110, 11111
    assert(c(6) == 20);
    assert(c(7) == 35);
    assert(c(8) == 70);
    assert(c(9) == 126);
    assert(c(20) == 184756);
    return 0;
}
