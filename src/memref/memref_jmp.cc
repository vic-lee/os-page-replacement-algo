#include "memref_jmp.h"

namespace memref
{

JumpReference::JumpReference(int pid, int proc_size) : Reference(pid, proc_size, 1) {}

}