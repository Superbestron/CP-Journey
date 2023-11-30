from math import hypot


def inside(x, y, w, h, r, x1, y1):
    if x + w - r <= x1 <= x + w and y <= y1 <= y + r:  # Top right
        return hypot((x + w - r) - x1, (y + r) - y1) <= r
    elif x + w - r <= x1 <= x + w and y + h - r <= y1 <= y + h:  # Bottom right
        return hypot((x + w - r) - x1, (y + h - r) - y1) <= r
    elif x <= x1 <= x + r and y <= y1 <= y + r:  # Top left
        return hypot((x + r) - x1, (y + r) - y1) <= r
    elif x <= x1 <= x + r and y + h - r <= y1 <= y + h:  # Bottom left
        return hypot((x + r) - x1, (y + h - r) - y1) <= r
    else:
        return x <= x1 <= x + w and y <= y1 <= y + h


n = int(input())
for i in range(n):
    ls = [*map(float, input().split())]
    x = ls[0]
    y = ls[1]
    w = ls[2]
    h = ls[3]
    r = ls[4]
    m = int(ls[5])
    ls = ls[6:]
    for j in range(0, 2 * m, 2):
        x1 = ls[j]
        y1 = ls[j + 1]
        if inside(x, y, w, h, r, x1, y1):
            print("inside")
        else:
            print("outside")
    print()
