#include <cassert>
#include <string>

// A palindrome is a string that reads the same front-to-back as back-to-front. So, the first
// character must be the same as the last character, and the second character must be the same as
// the second-to-last character, etc. Your function should return true if the input string is a
// palindrome, and false otherwise. You will probably want to add one or two function parameters
// (through use of a helper function). You may not use for, while, do while, or goto.
bool palindrome(std::string s) {
    return s.empty() ? true : s.front() == s.back() ? palindrome(s.substr(1, s.size()-2)) : false;
}

// Do NOT change the main function.
int main() {
    assert(palindrome(""));
    assert(palindrome("a"));
    assert(!palindrome("ab"));
    assert(palindrome("aa"));
    assert(palindrome("ablewasiereisawelba"));
    assert(!palindrome("ablewasiereisawelma"));
    return 0;
}
