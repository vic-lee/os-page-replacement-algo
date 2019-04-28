#pragma once

#include "memref.h"

namespace memref
{

class InitialReference : public Reference
{
public:
    InitialReference(int pid);
    void simulate(int prior_refnum, int proc_size, pager::Pager &pager, int time_accessed) override;
};

} // namespace memref
