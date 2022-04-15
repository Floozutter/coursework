#include <cassert>

// You will be given a quantificational logic formula of the form QxQyQz F(x,y,z), where each Q can
// be either a "for all" or "there exists", and F is some 3-variable predicate. You will also be
// given the definition of F: the exact values of x, y, and z that cause the predicate to evaluate
// to true of false, via a 3D array. Your task is to write a function that correctly determines
// whether the given formula should evaluate to true or false.
//
// In case you've never seen 3D arrays before, you can access the element in row x, column y, and
// depth z of the array `data` via `data[x][y][z]`. You should not need to know anything more about
// multi-dimensional arrays to complete this assignment.
//
// To this end, you will be implementing the following function:
// bool quantificationalSolver(bool data[4][4][4], bool quants[3]);
//
// quants[0] will be 1 if Qx is "for all" x, and will be 0 if Qx is "there exists" x.
// quants[1] will be 1 if Qy is "for all" y, and will be 0 if Qy is "there exists" y.
// quants[2] will be 1 if Qz is "for all" z, and will be 0 if Qz is "there exists" z.
//
// The universe for each variable (x, y, and z) has 4 possible values (0, 1, 2, and 3).
// F is defined via the data parameter. If F(2, 1, 3) = true, then data[2][1][3] = true.
//
// It is possible to write this function in about 20 lines of code. If you are writing
// significantly more (50+), that is a sign you are approaching the problem incorrectly.

bool quantificationalSolver(bool data[4][4][4], bool quants[3]) {
    bool cata[4][4];
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            int trues = 0;
            for (int z = 0; z < 4; ++z) {
                if (data[x][y][z]) {
                    ++trues;
                }
            }
            cata[x][y] = quants[2] ? trues >= 4 : trues > 0;
        }
    }
    bool bata[4];
    for (int x = 0; x < 4; ++x) {
        int trues = 0;
        for (int y = 0; y < 4; ++y) {
            if (cata[x][y]) {
                ++trues;
            }
        }
        bata[x] = quants[1] ? trues >= 4 : trues > 0;
    }
    int trues = 0;
    for (int x = 0; x < 4; ++x) {
        if (bata[x]) {
            ++trues;
        }
    }
    return quants[0] ? trues >= 4 : trues > 0;
}

int main() {
    // Following evals to false since for all x, for all y, for all z is not satisfied.
    // (False when x=2, y=0, z=3.)
    bool data_a[4][4][4] = {
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 0,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
    };
    bool quants_a[3] = {1, 1, 1};
    assert(!quantificationalSolver(data_a, quants_a));
    // Following evals to true since for all x, there exists a y, there exists a z is satisfied.
    // (True when (x=0, y=0, z=1), (x=1, y=3, z=2), (x=2, y=1, z=3), (x=3, y=3, z=1).)
    bool data_b[4][4][4] = {
        0, 1, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 1, 0,
        0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 1, 0, 0,
    };
    bool quants_b[3] = {1, 0, 0};
    assert(quantificationalSolver(data_b, quants_b));
}
