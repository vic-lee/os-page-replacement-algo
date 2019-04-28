#pragma once

#include "memref.h"

namespace memref
{

class SequentialReference : public Reference
{
public:
    SequentialReference(int pid, int proc_size);
};

} // namespace memref
