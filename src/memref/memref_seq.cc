#include "memref_seq.h"

namespace memref
{

SequentialReference::SequentialReference(int pid) : Reference(pid, 1) {}

}