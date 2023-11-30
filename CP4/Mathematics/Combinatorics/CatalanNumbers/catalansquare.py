arr = [1]

for i in range(5000):
    arr.append(arr[i] * (4 * i + 2) // (i + 2))

x = int(input())
sum = 0
for i in range(x + 1):
    sum += arr[i] * arr[x - i]
print(sum)
