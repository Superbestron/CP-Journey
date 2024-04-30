import sys

stmts = []
dict = {}
idx = 0


def parseIf(eval):
    # confirm this idx is of the form "is A>B"
    global idx
    filler, condition = stmts[idx].split()
    idx += 1
    isYes = True
    if ">" in condition:
        a, b = condition.split(">")
        if dict[a] <= dict[b]:
            isYes = False
    elif "<" in condition:
        a, b = condition.split("<")
        if dict[a] >= dict[b]:
            isYes = False
    elif "==" in condition:
        a, b = condition.split("==")
        if dict[a] != dict[b]:
            isYes = False
    else:
        a, b = condition.split("!=")
        if dict[a] == dict[b]:
            isYes = False

    # Yes
    idx += 1  # skip "yes"
    # evaluate clauses
    line = stmts[idx].split()
    while line[0] != "No" and line[0] != "si":
        if line[0] == "print":
            parsePrint(eval and isYes)
        else:
            parseIf(eval)
        line = stmts[idx].split()

    # No
    if stmts[idx] == "No":
        idx += 1  # skip "no"
        line = stmts[idx].split()
        while line[0] != "si":
            if line[0] == "print":
                parsePrint(eval and not isYes)
            else:
                parseIf(eval)
            line = stmts[idx].split()
    idx += 1  # skip "si"


def parsePrint(toPrint):
    global idx
    line = stmts[idx].split()
    idx += 1
    if toPrint:
        print(dict[line[1]])


for line in sys.stdin:
    stmts.append(line.strip())

vars = stmts[-2].split()
values = list(map(int, stmts[-1].split()))

stmts = stmts[:-2]
for i in range(len(vars)):
    dict[vars[i]] = values[i]

while idx < len(stmts):
    line = stmts[idx].split()
    if line[0] == "print":
        parsePrint(True)
    else:
        parseIf(True)
