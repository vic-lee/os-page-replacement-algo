#include "memref_back.h"

#include "../pager/pager.h"

namespace memref
{

BackwardReference::BackwardReference(int pid, int proc_size) : Reference(pid, proc_size, -5) {}

}