import math

m = int(input())

for i in range(m):
    ls = []
    r, n, theta, min, sec = map(int, input().split())
    theta *= 3600
    min *= 60
    to_add = theta + min + sec
    deg = 0
    st = set()
    for j in range(n):
        deg = (deg + to_add) % 1296000
        if st.__contains__(deg):
            break
        ls.append(deg)
        st.add(deg)
    max_range = 0
    ls.sort()
    for j in range(0, len(ls) - 1):
        max_range = max(max_range, ls[j + 1] - ls[j])
    max_range = max(max_range, 1296000 - ls[-1] + ls[0])  # don't forget to wrap around the last distance
    print(math.pi * r ** 2 * max_range / 1296000)
