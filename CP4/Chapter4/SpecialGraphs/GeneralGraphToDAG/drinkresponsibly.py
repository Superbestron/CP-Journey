from collections import Counter
from functools import lru_cache
from math import isclose

# Credits to Brandon Tang for his pythonic way of doing this question

m, u, d = map(float, input().split())
d = int(d)

names = ['' for i in range(d)]
alcohol = [0] * d
price = [0] * d
path = []


@lru_cache(maxsize=None)
def dp(drink_left, money_left, index):
    if index == d:
        if isclose(drink_left, 0, abs_tol=1e-9) and isclose(money_left, 0, abs_tol=1e-9):
            return True
        else:
            return False
    if drink_left < -1e-9 or money_left < -1e-9:
        return False
    return dp(drink_left - alcohol[index], money_left - price[index], index) | dp(drink_left, money_left, index + 1)


def fill_path(drink_left, money_left, index):
    if index == d:
        return
    # This is impt, you would rather choose a shorter path to shorten execution time
    if dp(drink_left, money_left, index + 1):
        fill_path(drink_left, money_left, index + 1)
    elif dp(drink_left - alcohol[index], money_left - price[index], index):
        path.append(index)
        fill_path(drink_left - alcohol[index], money_left - price[index], index)


for i in range(d):
    name, strength, size, cost = input().split()
    names[i] = name
    size = eval(size)
    alcohol[i] = size * int(strength)
    price[i] = float(cost)

fill_path(u, m, 0)
path = Counter(path)
if path:
    for k, v in path.items():
        print(names[k], v)
else:
    print("IMPOSSIBLE")
