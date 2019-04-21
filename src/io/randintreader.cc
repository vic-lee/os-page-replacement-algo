#include "randintreader.h"

namespace io
{
RandIntReader::RandIntReader() : line_cursor_(1), MAX_INT_(2147483647) {}

double RandIntReader::calc_next_probability()
{
    auto calc_prob = [this](int r) -> double { return r / (MAX_INT_ + 1.0); };
    int randnum = read_next_int();
    return calc_prob(randnum);
}

}