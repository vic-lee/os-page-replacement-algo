#include "memref_seq.h"

#include "../pager/pager.h"

namespace memref
{

SequentialReference::SequentialReference(int pid, int proc_size) : Reference(pid, proc_size, 1) {}

}