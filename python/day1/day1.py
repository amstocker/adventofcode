"""
Advent of Code: Day 1
"""

# input data
with open('input.txt') as f:
    data = f.read()


"""
Part 1
"""
def floor(directions):
    return directions.count('(') - directions.count(')')


if __name__ == "__main__":
    print floor(data)


"""
Part 2
"""
def search(data, start=None, end=None):
    if not start:
        start = 0
    if not end:
        end = len(data)
    i = (start + end) // 2
    current_floor = floor(data[:i])
    if current_floor < -1:
        return search(data, start, i)
    elif current_floor > -1:
        return search(data, i, end)
    else:
        return i


if __name__ == "__main__":
    print search(data)
