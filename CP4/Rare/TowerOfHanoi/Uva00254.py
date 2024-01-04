import sys

A = [0]
B = [0]
C = [0]


def solve(count, src, dest, inter, n):
    mid = 2 ** (n - 1)
    if count == 0:
        return
    if count < mid:
        return solve(count, src, inter, dest, n - 1)
    src[0] -= n - 1
    inter[0] += n - 1
    dest[0] += 1
    src[0] -= 1
    solve(count - mid, inter, dest, src, n - 1)


for line in sys.stdin:
    n, m = map(int, line.split())
    if n == 0 and m == 0:
        break
    A[0] = n
    B[0] = 0
    C[0] = 0
    solve(m, A, C, B, n)
    print(A[0], B[0], C[0])
