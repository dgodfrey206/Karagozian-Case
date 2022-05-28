Build
===

The executables are already present in the `solutions/` folder, so to execute you would simply type `./nearest` and `./wordsearch [file]` on the terminal. However, if you would like to rebuild then simply type `cmake --build build/` (note that to rebuild you would need a C++17-compliant compiler). The `src/` folder contains the example input for both of the programs. `src/words1.txt` and `src/words2.txt` are meant to be run with `./wordsearch`, but you are free to make another file and use it instead.


Challenge 1 – Super Word Search
=====

Introduction
----

In a typical word search puzzle (http://en.wikipedia.org/wiki/Word_search), you are given an `NxM` grid of
seemingly random letters and a list of `P` words that are in the grid. The words can be found going in any of the
8 directions in a two-dimensional grid:

- top to bottom
- bottom to top
- left to right
- right to left
- bottom left to top right
- bottom right to top left
- top left to bottom right
- top right to bottom left

You're a college professor (for English and Topology, of all things), and your students have become very good
at traditional Word Search. Since you want them to continue spending time on academic games, you created a
variant of Word Search (inventively) called Super Word Search.

Description
----

As with the standard word search, you get an `NxM` grid of letters, and `P` words that are to be found in the grid.
You also get a "mode" `flag` with one of the following values: `WRAP`, `NO_WRAP`. The `flag` value indicates
whether words can wrap-around after they hit a boundary of the grid.

Row numbers start at `0` (top row) and go to `N-1` (bottom row). Column numbers start at `0` (leftmost column) and
go to `M-1` (rightmost column). Grid coordinates are specified as `(row_num, column_num)`.

Here is an example to illustrate the difference between WRAP and NO_WRAP:

|  | 0 | 1 | 2 |
| ----------- | ----------- | ----------- | ----------- |
| 0 | A | B | C |
| 1 | D | E | F |
| 2 | G | H | I |

"FED" is a word that starts at (1,2) and ends at (1,0).If we are in WRAP mode:
- "CAB" is a word that starts at (0,2) and ends at (0,1).
- "GAD" is a word that starts at (2,0) and ends at (1,0).
- "BID" is a word that starts at (0,1) and ends at (1,0).
- 
If we are in `NO_WRAP` mode:
- "FED" is a word that starts at (1,2) and ends at (1,0).
- "CAB" is not a word since it requires wrapping in the horizontal direction.
- "GAD" is not a word since it requires wrapping in the vertical direction.
- "BID" is not a word since it requires wrapping in the horizontal and vertical directions.

A letter in the grid is not allowed to be in a word more than once. So, while technically "HIGH" can be found in
the above grid in `WRAP` mode, we will not allow it because it uses the H at (2,1) twice.

Input Format
-----

    N M
    N rows of M letters
    "WRAP" or "NO_WRAP"
    P
    P words with 1 word per lines

Output Format
-----

Your program should accept the name of an input file which will contain data in the above format.
For each of the `P` words, you are to output the start and end coordinates of that word in the format "`(row_start,
column_start) (row_end, column_end)`". If the word cannot be found in the grid, output `"NOT FOUND"`.
You are guaranteed that each word will occur at most once in the grid, so a word's start and end coordinates
will always be unique (if the word is in the grid), and will never be ambiguous.
Your program can write its output to the screen/console.


Challenge 2 – Nearest-Neighbors Algorithm
====

Description
----

For this challenge, please write a program that takes as input:

1. A floating point radius `r`,
2. The number of points `N`,
3. A series of lines of 3D points with each coordinate separated by a space

The ID for each point is generated sequentially starting from 0 and incrementing by 1. Your program should
print to the screen for each node the node id, followed by a colon, followed by a comma separated list the id of
each neighbor to that node. A neighbor of a node `n` is another node n<sub>i</sub> whose distance from n is less than r.
Formally, the neighbors of a node nn is the set of nodes {n<sub>i</sub> | ||n − n<sub>i</sub>|| < r}. See the example output below.
Please discuss the time and space complexity of your solution and any implementation decisions that you feel
were important when writing your program.

Input Format
---

r (input radius)\
N (number of points)\
x<sub>1</sub> y<sub>1</sub> z<sub>1</sub>\
...\
x<sub>N</sub> y<sub>N</sub> z<sub>N</sub>
    
Output Format
----

0: n<sub>0</sub><sup>0</sup>... , n<sup>N-1</sup><sub>m<sub>0</sub></sub>
...
N-1: n<sup>N-1</sup><sub>0</sub> ,..., n<sup>N-1</sup><sub>M<sub>N-1</sub></sub>
    
Where n<sub>j</sub><sup>i</sup> denotes node i’s jth neighbor.

Constraints
----

- `1 ≤ n ≤ 105`, where `n` is the number of nodes.
- {`(x, y, z)` ∈ R<sup>3</sup>: −107 ≤ `x`,`y`, `z` ≤ 107}
- The node IDs are enumerated from 1 to `n`.
- There are no other constraints on the input. You may format the input however you wish.
