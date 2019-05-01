# OS Lab 4: Page Replacement Algorithms

## Getting started

### Compile

In the project root folder, run `make`. Type `clean` to delete all binary files.

### Run

#### Standard command

In the project root folder, enter command in the following format:

`./exec [M] [P] [S] [J] [N] [R] [optional debug flag] [optional show random flag]`

Note:

- `R` supports FIFO, LRU, and Random (upper- and lower-case are both accepted)
- Debug & show random flag: type `1` to turn on and `0` to turn off. They are off by default.

Sample command: `./exec 10 10 20 1 10 lru 0 0           // debug mode off, show random mode off`

#### Custom command

To test the 16 sample inputs from the requirement, simply run `./exec [input number]`.

For instance, to test input 1, run `./exec 1`. This is equivalent to running `./exec 10 10 20 1 10 lru 0`.

To run with debug and show random flags, type:

`./exec --debug --show-random [input number]` or `./exec -d -s [input number]`

Note that the program does not support specifying random flag but not debug flag (i.e. `./exec -s [input number]` would fail to turn on show random mode).

(see `src/io/sample-in.txt` for their specifications.)
