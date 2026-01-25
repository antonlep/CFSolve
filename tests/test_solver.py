from src.gui.solver_helpers import solve_from_raw


def test_simple_bar():
    nodes = [
        [0, 0],
        [0, 10],
        [10, 10],
        [10, 0],
        [20, 0],
        [20, 10],
    ]
    elements = [[0, 2, 1], [0, 3, 2], [2, 3, 5], [3, 4, 5]]
    fixed = [0, 1, 2, 3]
    displacements = [0, 0, 0, 0]
    forces = [
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        100000,
        0,
        100000,
        0,
    ]
    result = solve_from_raw(nodes, elements, fixed, displacements, forces)

    assert len(result.disp) == 6
    assert result.disp[4][0] > 0
    assert result.disp[5][0] > 0
