#include "memref_rand.h"

#include "../pager/pager.h"

namespace memref
{

RandomReference::RandomReference(int pid, int proc_size) : Reference(pid, proc_size, 0) {}

}