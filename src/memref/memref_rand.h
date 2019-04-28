#pragma once

#include "memref.h"

namespace memref
{

class RandomReference : public Reference
{
public:
    RandomReference(int pid, int proc_size);
    void simulate(int prior_refnum, pager::Pager &pager, int time_accessed) override;
};

} // namespace memref
