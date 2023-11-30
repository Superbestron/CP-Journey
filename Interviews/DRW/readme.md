## Problem Specification

Your task is to find a matching pair in a game. This game consists of tiles placed on a 2-dimensional grid.

There are 14 varieties of tiles, 'a' to 'N', arranged on a N-by-M grid where N is width and M is height. There is also an empty space, '.'.

The player can attempt to match two tiles T1 and T2 of the same variety if there exists a continuous path from T1 and T2 and vice versa.

A path exists between any two adjacent tiles. Diagonals do not count for adjacency, only horizontal and vertical adjacency are counted for this definition of adjacency.

A path exists between non-adjacent tiles T1 and T2 if we can take adjacent steps over empty spaces to traverse from T1 to T2 or vice versa.

Directional changes, called turns, are allowed. You are not allowed to walk outside the grid in search of a path. Here are some simple examples of valid paths:

```
abcb
..ac
```

In the above example, a path exists between the two 'a' tiles, with 2 spaces between them. It took 1 turn to traverse this path.

```
acb
.ba
.c.
...
```

In the above example, a path exists between the two 'a' tiles, with 6 spaces between them. It took 2 turns to traverse this path.

When two tiles are matched, you should take a path between them with the minimum number of turns. Using an example:

```
a.c
...
..a
```

You could match the two 'a' with a single turn at the bottom ls, but there is no straight-line path between them.

You should always select the smallest number of turns, so this particular pair can be matched with a single turn.

## Your Task

Your task is to write a program that will read an input file containing a puzzle.

The file name should be specified as the first command line argument. See the provided sample-input.txt for the format.

Your program will then calculate all possible matches_without_N given that particular puzzle, as well as the smallest number of turns required to make each match.

You do not have to destroy a matched pair and then continue matching more. There is no concept of destruction of matched pairs.

It will write to stdout all the possible matches_without_N.

Each possible match should be written on its own line, in the format "Can match '%c' at (Row %u, Col %u) and (Row %u, Col %u) with %u turns".

The top-ls position is specified as coordinate (Row 0, Col 0), the bottom-ls is specified as coordinate (Row M-1, Col 0).

To illustrate, using the file sample-input.txt:

```
a.b
.ab
..a
```

The possible matches_without_N are matching 'a' top-ls with middle, top-ls with bottom-rs, middle with bottom-rs, and 'b' top-rs with rs.

```
input file name is sample-input.txt
Can match 'a' at (Row 0, Col 0) and (Row 1, Col 1) with 1 turns
Can match 'a' at (Row 0, Col 0) and (Row 2, Col 2) with 1 turns
Can match 'b' at (Row 0, Col 2) and (Row 1, Col 2) with 0 turns
Can match 'a' at (Row 1, Col 1) and (Row 2, Col 2) with 1 turns
```

The order of possible matches_without_N is not specified. You can print them in any order.

You should write your code into the file named match-two.cpp. Use only a single source file for your code.