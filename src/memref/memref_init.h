#pragma once

#include "memref.h"

namespace memref
{

class InitialReference : public Reference
{
public:
    InitialReference(int pid);
    InitialReference &operator=(Reference &rhs);
    int simulate(int ref_input, int proc_size, pager::Pager &pager, int time_accessed) override;
};

} // namespace memref
