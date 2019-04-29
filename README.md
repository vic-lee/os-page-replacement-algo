# OS Lab 4: Page Replacement Algorithms

## Getting started

### Compile

In the project root folder, run `make`. Type `clean` to delete all binary files.

### Run

#### Standard command

In the project root folder, enter command in the following format:

`./exec [M] [P] [S] [J] [N] [R] [optional debug mode] [optional show random mode]`

in which:
- `M`, `P`, `S`, `N` are positive integers
- `J` supports 1 to 4
- `R` supports FIFO, LRU, and Random (upper- and lower-case are both accepted)
- Debug & show random mode: type `1` to turn on and `0` to turn off. They are off by default.

Sample command: `./exec 10 10 20 1 10 lru 0 0           // debug mode off, show random mode off`

#### Custom command

To test the 16 sample inputs from the requirement, the program supports a simpler syntax. Simply run:

`./exec [input number]`

For instance, `./exec 1` is equivalent to running `./exec 10 10 20 1 10 lru 0`.

To run with debug and show random mode, type:

`./exec --debug --show-random [input number]` or `./exec -d -s [input number]` 

Note that the program does not support specifying random mode but not debug mode (i.e. `./exec -s [input number]` would fail to turn on show random mode).


(see `src/io/sample-in.txt` for their specifications.)
