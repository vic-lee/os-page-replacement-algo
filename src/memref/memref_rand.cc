#include "memref_rand.h"

#include "../pager/pager.h"

namespace memref
{

RandomReference::RandomReference(int pid) : Reference(pid, 0) {}

void RandomReference::simulate(int prior_refnum, int proc_size, pager::Pager &pager, int time_accessed)
{
    int viraddr = (prior_refnum + proc_size) % proc_size;

    pager.reference_by_virtual_addr(viraddr, pid_, time_accessed);
}

} // namespace memref