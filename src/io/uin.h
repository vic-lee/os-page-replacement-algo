#pragma once

#include "../pager/pager.h"

namespace io
{

struct UserInput
{
    int machine_size;
    int page_size;
    int proc_size;
    int jobmix;
    int ref_count;
    std::string raw_algoname;
    pager::AlgoName algoname;
    bool debug;
    bool showrand;

    UserInput()
        : machine_size(-1), page_size(-1), proc_size(-1),
          jobmix(-1), ref_count(-1), debug(false), showrand(false){};
};

io::UserInput read_input(const int &argc, char **argv);

} // namespace io