import sys
from fractions import Fraction


def points(x1, x2):
    if (x1, x2) == (1, 2) or (x1, x2) == (2, 1):
        return 10000
    if x1 == x2:
        return 1000 * x1
    if x1 < x2:
        temp = x1
        x1 = x2
        x2 = temp
    return x1 * 10 + x2


for line in sys.stdin:
    s0, s1, r0, r1 = line.split()
    ans = 0
    if s0 == "0" and s1 == "0" and r0 == "0" and r1 == "0":
        break
    st1 = set()
    st2 = set()
    for i in range(1, 7):
        curr_s0 = i
        if s0 != "*":
            curr_s0 = int(s0)
        for j in range(1, 7):
            curr_s1 = j
            if s1 != "*":
                curr_s1 = int(s1)
            st1.add((curr_s0, curr_s1))

    for k in range(1, 7):
        curr_r0 = k
        if r0 != "*":
            curr_r0 = int(r0)
        for l in range(1, 7):
            curr_r1 = l
            if r1 != "*":
                curr_r1 = int(r1)
            st2.add((curr_r0, curr_r1))

    ans = 0
    total = len(st1) * len(st2)

    for (curr_s0, curr_s1) in st1:
        points1 = points(curr_s0, curr_s1)
        for (curr_r0, curr_r1) in st2:
            points2 = points(curr_r0, curr_r1)
            if points1 > points2:
                ans += 1
    print(Fraction(ans, total))
