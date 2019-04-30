#include "memref_rand.h"

#include "../pager/pager.h"

namespace memref
{

RandomReference::RandomReference(int pid) : Reference(pid, 0) {}

} // namespace memref