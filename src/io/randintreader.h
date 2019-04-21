#ifndef H_RANDINTREADER
#define H_RANDINTREADER

#include <iostream>
#include <fstream>

namespace io
{
class RandIntReader
{
public:
    RandIntReader();
    ~RandIntReader();
    double calc_next_probability();

private:
    int read_next_int();
    int line_cursor_;
    const int MAX_INT_;
    std::ifstream infile;
};
}

#endif