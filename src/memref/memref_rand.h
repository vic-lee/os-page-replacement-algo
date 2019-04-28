#pragma once

#include "memref.h"

namespace memref
{

class RandomReference : public Reference
{
public:
    RandomReference(int pid, int proc_size);
};

} // namespace memref
