q = int(input())
arr = [1]

for i in range(5000):
    arr.append(arr[i] * (4 * i + 2) // (i + 2))

for i in range(q):
    x = int(input())
    print(arr[x])
