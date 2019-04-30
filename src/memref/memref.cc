#include "memref.h"

#include "../pager/pager.h"

namespace memref
{
const int Reference::INIT_FACTOR_ = 111;

Reference::Reference(int pid, int delta) : pid_(pid), delta_(delta) {}

Reference::~Reference() {}

Reference &Reference::operator=(Reference &rhs)
{
    pid_ = rhs.pid_;
    delta_ = rhs.delta_;
    return *this;
}

int Reference::simulate(int ref_input, int proc_size, pager::Pager &pager, int time_accessed)
{
    int viraddr = (ref_input + delta_ + proc_size) % proc_size;

    pager.reference_by_virtual_addr(viraddr, pid_, time_accessed);

    return viraddr;
}

} // namespace memref