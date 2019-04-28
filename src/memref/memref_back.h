#pragma once

#include "memref.h"

namespace memref
{

class BackwardReference : public Reference
{
public:
    BackwardReference(int pid);
};

} // namespace memref
