#pragma once

#include "memref.h"

namespace memref
{

class InitialReference : public Reference
{
public:
    InitialReference(int pid, int proc_size);
    void simulate(int prior_refnum, pager::Pager &pager, int time_accessed) override;
};

} // namespace memref
