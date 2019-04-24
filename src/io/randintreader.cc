#include <fstream>
#include <iostream>

#include "randintreader.h"

namespace io
{
const int RandIntReader::MAX_INT_ = 2147483647;

RandIntReader::RandIntReader()
{
    infile_.open("random-numbers.txt");

    if (!infile_)
    {
        std::cout << "ERROR: Could not open rand-num file." << std::endl;
        exit(10);
    }
}

RandIntReader::~RandIntReader()
{
    infile_.close();
}

double RandIntReader::calc_next_probability()
{
    auto calc_prob = [](int r) -> double { return r / (MAX_INT_ + 1.0); };
    int randnum = read_next_int();
    return calc_prob(randnum);
}

int RandIntReader::read_next_int()
{
    int nextint;
    infile_ >> nextint;
    return nextint;
}
} // namespace io