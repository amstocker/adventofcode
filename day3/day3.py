"""
Advent of Code: Day 3
"""
from collections import defaultdict


# input data
if __name__ == "__main__":
    with open('input.txt') as f:
        data = f.read()


"""
Part 1
"""
def count_houses(directions):
    counter = defaultdict(int)
    counter[(0, 0)] += 1
    curx = 0
    cury = 0
    
    for char in directions:
        if   char == "<": curx -= 1
        elif char == "^": cury += 1
        elif char == ">": curx += 1
        elif char == "v": cury -= 1
        else:
            continue
        counter[(curx, cury)] += 1

    return len(counter.keys())


if __name__ == "__main__":
    print count_houses(data)


"""
Part 2
"""
