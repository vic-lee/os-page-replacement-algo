#pragma once

#include "memref.h"

namespace memref
{

class BackwardReference : public Reference
{
public:
    BackwardReference(int pid, int proc_size);
};

} // namespace memref
