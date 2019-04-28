#include "memref_init.h"

#include "../pager/pager.h"

namespace memref
{

InitialReference::InitialReference(int pid, int proc_size) : Reference(pid, proc_size, 1) {}

void InitialReference::simulate(int prior_refnum, pager::Pager &pager, int time_accessed)
{
    int viraddr = (INIT_FACTOR_ * pid_) % proc_size_;

    pager.reference_by_virtual_addr(viraddr, pid_, time_accessed);
}

} // namespace memref