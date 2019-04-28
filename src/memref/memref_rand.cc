#include "memref_rand.h"

#include "../pager/pager.h"

namespace memref
{

RandomReference::RandomReference(int pid, int proc_size) : Reference(pid, proc_size, 0) {}

void RandomReference::simulate(int prior_refnum, pager::Pager &pager, int time_accessed)
{
    int viraddr = (prior_refnum + proc_size_) % proc_size_;

    pager.reference_by_virtual_addr(viraddr, pid_, time_accessed);
}

} // namespace memref