#pragma once

#include "memref.h"

namespace memref
{

class RandomReference : public Reference
{
public:
    RandomReference(int pid);
};

} // namespace memref
