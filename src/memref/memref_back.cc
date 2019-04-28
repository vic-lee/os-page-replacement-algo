#include "memref_back.h"

namespace memref
{

BackwardReference::BackwardReference(int pid) : Reference(pid, -5) {}

}