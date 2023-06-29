s = input()

min_x, max_x = 0, 2 ** len(s)
min_y, max_y = 0, 2 ** len(s)

for char in s:
    if char == '0':
        max_x = (min_x + max_x) / 2
        max_y = (min_y + max_y) / 2
    elif char == '1':
        max_x = (min_x + max_x) / 2
        min_y = (min_y + max_y) / 2
    elif char == '2':
        min_x = (min_x + max_x) / 2
        max_y = (min_y + max_y) / 2
    else:
        min_x = (min_x + max_x) / 2
        min_y = (min_y + max_y) / 2

print(len(s), int(min_y), int(min_x))
