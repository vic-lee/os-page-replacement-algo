#include "memref.h"

#include "../pager/pager.h"

namespace memref
{

Reference::Reference(int pid, int delta) : pid_(pid), delta_(delta), INIT_FACTOR_(111) {}

void Reference::simulate(int prior_refnum, int proc_size, pager::Pager &pager, int time_accessed)
{
    int viradddr = (prior_refnum + delta_ + proc_size) % proc_size;

    pager.reference_by_virtual_addr(viradddr, pid_, time_accessed);
}


} // namespace memref