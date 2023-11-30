import sys

for line in sys.stdin:
    b0, b1, b2, b3 = map(float, line.split())
    t0, t1, t2, t3 = map(float, input().split())

    p0, p1, p2, p3 = t0 - b0, t1 - b1, t2 - b2, t3 - b3
    d0, d1, d2 = p1, 2 * p2, 3 * p3

    r1 = (-d1 + (d1 ** 2 - 4 * d2 * d0) ** 0.5) / (2 * d2)
    r2 = (-d1 - (d1 ** 2 - 4 * d2 * d0) ** 0.5) / (2 * d2)

    ls = [float(0), r1, r2, float(1)]
    min_y = 100000
    max_y = -100000
    for x in ls:
        if type(x) != float:
            continue
        if x < float(0) or x > float(1):
            continue
        poly = p0 + x * p1 + x ** 2 * p2 + x ** 3 * p3
        min_y = min(min_y, poly)
        max_y = max(max_y, poly)
    print(max_y - min_y)
