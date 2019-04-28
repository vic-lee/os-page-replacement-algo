#include "memref_seq.h"

namespace memref
{

SequentialReference::SequentialReference(int pid, int proc_size) : Reference(pid, proc_size, 1) {}

}