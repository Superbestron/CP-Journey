n = int(input())
for i in range(n):
    str = input()
    for j in range(1, len(str) + 1):
        new_str = str
        rem = len(str) % j
        if rem != 0:
            new_str += str[rem:j]
        base = str[:j]
        if base * (len(new_str) // len(base)) == new_str:
            print(len(base))
            break

