# OS Lab 4: Page Replacement Algorithms

## Getting started

### Compile

In the project root folder, run `make`. Type `clean` to delete all binary files.

### Run

In the project root folder, enter command in the following format:

`./exec [M] [P] [S] [J] [N] [R] [debug mode] [show random mode]`

in which:
- `M`, `P`, `S`, `N` are positive integers
- `J` supports 1 to 4
- `R` supports FIFO, LRU, and Random (upper- and lower-case are both accepted)
- Debug & show random mode: type `1` to turn on and `0` to turn off. They are `0` if user does not specify. 


## Project architecture
```
.
├── debug.h
├── driver
│   ├── driver.cc
│   ├── driver.h
│   ├── jobmix.cc
│   ├── jobmix.h
│   ├── jobmixspec.cc
│   ├── jobmixspec.h
│   ├── mrefspec.h
│   ├── mrefspec.o
│   ├── process.cc
│   └── process.h
├── io
│   ├── randintreader.cc
│   ├── randintreader.h
│   └── random-numbers.txt
├── main.cc
└── pager
    ├── frame.cc
    ├── frame.h
    ├── pager.cc
    └── pager.h
```