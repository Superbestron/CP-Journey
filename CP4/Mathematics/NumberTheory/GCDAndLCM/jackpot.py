def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)


def lcm(a, b):
    return a / gcd(a, b) * b


n = int(input())
for i in range(n):
    w = int(input())
    ls = list(map(int, input().split()))
    curr = ls[0]
    printed = False
    for j in range(1, len(ls)):
        curr = lcm(curr, ls[j])
        if curr > 1000000000:
            printed = True
            break
    curr = int(curr)
    if printed:
        print("More than a billion.")
    else:
        print(curr)
