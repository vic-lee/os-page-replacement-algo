#include <fstream>
#include <iostream>

#include "randintreader.h"

namespace io
{
RandIntReader::RandIntReader() : line_cursor_(1), MAX_INT_(2147483647) 
{
    infile.open("random-numbers.txt");
    
    if (!infile)
    {
        std::cout << "ERROR: Could not open rand-num file." << std::endl;
        exit(10);
    }
}

RandIntReader::~RandIntReader()
{
    infile.close();
}

double RandIntReader::calc_next_probability()
{
    auto calc_prob = [this](int r) -> double { return r / (MAX_INT_ + 1.0); };
    int randnum = read_next_int();
    return calc_prob(randnum);
}

int RandIntReader::read_next_int()
{
    int nextint;
    infile >> nextint;
    return nextint;
}
} // namespace io