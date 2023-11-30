t = int(input())

for i in range(t):
    n = int(input())
    dict = {}
    for j in range(n):
        name, category = input().split()
        if category not in dict:
            dict[category] = 1
        else:
            dict[category] += 1
    ans = 1
    for k, v in dict.items():
        ans *= (v + 1)
    print(ans - 1)
