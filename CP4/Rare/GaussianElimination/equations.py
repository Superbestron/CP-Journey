from fractions import Fraction

# Really tedious question, I don't recommend doing it for practice

N = int(input())
for i in range(N):
    if i > 0:
        input()
    s1 = input().split()
    s2 = input().split()
    s = [s1, s2]
    arr = [[0 for _ in range(3)] for _ in range(2)]
    for i, str in enumerate(s):
        left_equal = True
        is_positive = True
        for term in str:
            if term == "=":
                left_equal = False
                is_positive = True
            elif term == "+":
                is_positive = True
            elif term == "-":
                is_positive = False
            else:
                if term[0] == "-":
                    is_positive = not is_positive
                    term = term[1:]

                multiplier = -1 if left_equal ^ is_positive else 1

                if term[-1] == 'x':
                    term = term[:-1]
                    if not term:
                        term = "1"
                    arr[i][0] += multiplier * int(term)
                elif term[-1] == 'y':
                    term = term[:-1]
                    if not term:
                        term = "1"
                    arr[i][1] += multiplier * int(term)
                else:
                    arr[i][2] += multiplier * int(term)
    denom = (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1])
    if denom:
        xnum = (-arr[0][2] * arr[1][1]) - (-arr[1][2] * arr[0][1])
        ynum = (arr[0][0] * -arr[1][2]) - (arr[1][0] * -arr[0][2])
        print(Fraction(xnum, denom))
        print(Fraction(ynum, denom))
    elif arr[0][2] and not arr[0][0] and not arr[0][1] or arr[1][2] and not arr[1][0] and not arr[1][1]:
        print("don't know\ndon't know")  # if constant non-zero while no vars present
    else:
        if arr[0][0] and not arr[0][1] and not arr[1][0]:
            print(Fraction(-arr[0][2], arr[0][0]))  # x = C1 / a
        elif arr[1][0] and not arr[1][1] and not arr[0][0]:
            print(Fraction(-arr[1][2], arr[1][0]))  # x = C2 / b
        elif arr[1][0] and not arr[1][1] and arr[0][0] \
                and not arr[0][1] and arr[1][0] * arr[0][2] == arr[0][0] * arr[1][2]:
            print(Fraction(-arr[0][2], arr[0][0]))  # x = C1 / a
        else:
            print("don't know")

        if arr[0][1] and not arr[0][0] and not arr[1][1]:
            print(Fraction(-arr[0][2], arr[0][1]))
        elif arr[1][1] and not arr[1][0] and not arr[0][1]:
            print(Fraction(-arr[1][2], arr[1][1]))
        elif arr[1][1] and not arr[1][0] and arr[0][1] \
                and not arr[0][0] and arr[1][1] * arr[0][2] == arr[0][1] * arr[1][2]:
            print(Fraction(-arr[0][2], arr[0][1]))
        else:
            print("don't know")
    print()
