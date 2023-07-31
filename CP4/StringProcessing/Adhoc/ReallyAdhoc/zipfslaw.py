import re
first = True
while True:
    try:
        n = int(input())
    except EOFError:
        break

    big_dict = {}
    while 1:
        s = input()
        if s == "EndOfText":
            break

        x = re.findall("[a-zA-Z]+", s)
        x = [i.lower() for i in x]

        for i in x:
            if i not in big_dict:
                big_dict[i] = 1
            else:
                big_dict[i] += 1

    ans = []
    for i in big_dict:
        if big_dict[i] == n:
            ans.append(i)

    ans.sort()
    for i in ans:
        print(i)

    if len(ans) == 0:
        print("There is no such word.")
    print()
