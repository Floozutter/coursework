"""
a heart-shaped plot, for Shauen
(this wasn't a romantic gesture lol it was apparently a homework problem)

"Draw a heart using the equation y = x^(2/3) +- sqrt(1 - x^2). Set the color to red and increase
the number of points to make the curve smooth. Hide the axes and adjust the ratio to make the heart
look better."
"""

import matplotlib.pyplot as plt

def heart(x: float) -> tuple[float, float]:
    """computes the double-valued heart function"""
    a = (x**2)**(1/3)  # single-valued term
    b = (1 - x**2)**(1/2)  # double-valued term
    return (a + b, a - b)

def linspace(start: float, stop: float, n: int) -> tuple[float, ...]:
    """returns a tuple of linearly spaced numbers"""
    if n <= 0:
        return ()
    elif n == 1:
        return (start,)
    else:
        step = (stop - start)/(n - 1)
        return tuple(start + step*i for i in range(n))

if __name__ == "__main__":
    # set up figure
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    ax.axis("off")
    ax.set_xlim(-1.5, 1.5)
    ax.set_ylim(-1.25, 1.75)
    # plot
    xs = linspace(-1, 1, 1000)
    ys1, ys2 = zip(*map(heart, xs))
    ax.plot(xs, ys1, color="red")
    ax.plot(xs, ys2, color="red")
    # show figure
    plt.show()
