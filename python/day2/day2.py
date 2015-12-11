"""
Advent of Code: Day 2
"""
from operator import mul
from itertools import combinations


# input data
if __name__ == "__main__":
    with open('input.txt') as f:
        sizes = [map(int, t.split('x')) for t in f.readlines()]


"""
Part 1
"""
def wrapping_needed(dims):
    areas = [reduce(mul, c, 1) for c in combinations(dims, len(dims)-1)]
    return 2*sum(areas) + min(areas)

if __name__ == "__main__":
    print sum(map(wrapping_needed, sizes))


"""
Part 2
"""
def ribbon_needed(dims):
    ribbon = 2*sum(sorted(dims)[:-1])
    bow = reduce(mul, dims, 1)
    return ribbon + bow

if __name__ == "__main__":
    print sum(map(ribbon_needed, sizes))
