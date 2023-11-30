N = int(input())
ls = list(map(int, input().split()))
ls.sort()
for i in range(N - 2):
    if ls[i + 2] < ls[i] + ls[i + 1]:
        print("possible")
        exit(0)
print("impossible")
