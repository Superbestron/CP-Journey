s = input()
for i in range(1, len(s) + 1):
    if len(s) % i != 0:
        continue
    can = True
    for j in range(i, len(s), i):
        curr = s[j:j + i]
        shifted = s[j + 1:j + i] + s[j:j + 1]
        prev = s[j - i:j]
        if shifted != prev:
            can = False
            break
    if can:
        print(i)
        break
