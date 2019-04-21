#include <iostream>

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