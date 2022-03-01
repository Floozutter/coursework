#include <cassert>
#include <span>

// This function takes an array as input and tries to find the index where the treasure is hidden.
// The array will have valid locations from 0 to n-1 (n is an input parameter). Your treasure map
// tells you to always look at location (max+min)/2, where max = the largest index the treasure
// could be at, and min = the smallest index the treasure could be at (using integer division, so
// round down). The integer value at that location will give you a hint where the treasure must be
// stored:
// - If the value is -1, then the treasure cannot be stored at locations (max+min)/2 or bigger.
// - If the value is +1, then the treasure cannot be stored at locations (max+min)/2 or smaller.
// - If the value is 0, then you found the treasure! Return the current index you're looking at.
// - If you run out of array to search without finding the treasure, return -1.
// There is fake gold and fake hints buried in this array! If you search anywhere other than where
// the map tells you, you will get false information! You will probably want to make a helper
// function. You may not use for, while, do while, or goto.
int treasure(int const * arr, unsigned int n) {
    if (!n) {
        return -1;
    }
    auto const & mid{(n-1) / 2};
    auto const & x{arr[mid]};
    if (x < 0) {
        return treasure(arr, mid);
    } else if (x > 0) {
        auto const & offset{mid + 1};
        auto const & index{treasure(arr + offset, n - offset)};
        return index == -1 ? index : index + offset;
    } else {
        return mid;
    }
}

// Do NOT change the main function.
int main() {
    int const a[] = {0};
    int const b[] = {1};
    int const c[] = {0, 1};
    int const d[] = {-1, 0};
    int const e[] = {1, 0};
    int const f[] = {1, 1};
    assert(treasure(a, std::size(a)) == 0);
    assert(treasure(b, std::size(b)) == -1);
    assert(treasure(c, std::size(c)) == 0);
    assert(treasure(d, std::size(d)) == -1);
    assert(treasure(e, std::size(e)) == 1);
    assert(treasure(f, std::size(f)) == -1);
    return 0;
}
