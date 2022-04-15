UnaryPredicate = tuple[int, int, int, int]
BinaryPredicate = tuple[UnaryPredicate, UnaryPredicate, UnaryPredicate, UnaryPredicate]
TernaryPredicate = tuple[BinaryPredicate, BinaryPredicate, BinaryPredicate, BinaryPredicate]

def quantificationalSolver(
    data: TernaryPredicate,
    quants: tuple[int, int, int],
) -> bool:
    return (all if quants[0] else any)(
        (all if quants[1] else any)(
            (all if quants[2] else any)(
                data[i][j][k]
                for k in range(4)
            )
            for j in range(4)
        )
        for i in range(4)
    )

if __name__ == "__main__":
    data_a = (
        ((1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)),
        ((1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)),
        ((1, 1, 1, 0), (1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)),
        ((1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1), (1, 1, 1, 1)),
    )
    quants_a = (1, 1, 1)
    assert not quantificationalSolver(data_a, quants_a)
    data_b = (
        ((0, 1, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0)),
        ((0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 1, 0)),
        ((0, 0, 0, 0), (0, 0, 0, 1), (0, 0, 0, 0), (0, 0, 0, 0)),
        ((0, 0, 0, 0), (0, 0, 0, 0), (0, 0, 0, 0), (0, 1, 0, 0)),
    )
    quants_b = (1, 0, 0)
    assert quantificationalSolver(data_b, quants_b)
