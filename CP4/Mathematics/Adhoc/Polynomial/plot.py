from math import comb

a = list(map(int, input().split()))
n = a[0]
a.pop(0)
a.reverse()

def compute_poly(x):
    global a
    y = 0
    for i in range(n + 1):
        y += a[i] * x ** i
    return y


for i in range(n + 1):
    t = 0
    for j in range(i + 1):
        t += (-1) ** j * comb(i, j) * compute_poly(i - j)

    print(t, end=' ')
