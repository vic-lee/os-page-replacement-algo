#pragma once

#include "memref.h"

namespace memref
{

class RandomReference : public Reference
{
public:
    RandomReference(int pid, int randnum);
    int simulate(int ref_input, int proc_size, pager::Pager &pager, int time_accessed) override;

private:
    int randnum_;
};

} // namespace memref
