#include "memref.h"

#include "../pager/pager.h"

namespace memref
{

Reference::Reference(int pid, int proc_size, int delta)
    : pid_(pid), proc_size_(proc_size), delta_(delta), INIT_FACTOR_(111) {}

void Reference::simulate(int prior_refnum, pager::Pager &pager, int time_accessed)
{
    int viradddr = (prior_refnum + delta_ + proc_size_) % proc_size_;

    pager.reference_by_virtual_addr(viradddr, pid_, time_accessed);
}


} // namespace memref