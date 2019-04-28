#pragma once

#include "memref.h"

namespace memref
{

class RandomReference : public Reference
{
public:
    RandomReference(int pid);
    void simulate(int prior_refnum, int proc_size, pager::Pager &pager, int time_accessed) override;
};

} // namespace memref
