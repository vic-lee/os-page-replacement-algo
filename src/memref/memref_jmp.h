#pragma once

#include "memref.h"

namespace memref
{

class JumpReference : public Reference
{
public:
    JumpReference(int pid, int proc_size);
};

} // namespace memref
