n, d = map(int, input().split())
dict = {}
sum = 0
ls = list(map(int, input().split()))
for i in range(n):
    div = ls[i] // d
    if div not in dict:
        dict[div] = 1
    else:
        sum += dict[div]
        dict[div] += 1
print(sum)
