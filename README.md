# OS Lab 4: Page Replacement Algorithms

## Getting started

In the root directory:

```
make                                          // compile


// enter `1` to enable optional debug and show-random modes; they're off by default
./exec [M] [P] [S] [J] [N] [R] [optional debug flag] [optional show random flag]


./exec [input-number]                         // custom way to test the sample input (1-16) provided, e.g. ./exec 12
./exec --debug --show-random [input-number]   // enable debug and show-random mode
./exec -d -b [input-number]                   // short-hand syntax


make clean                                    // remove binary files
```