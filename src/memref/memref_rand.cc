#include "memref_rand.h"

#include "../pager/pager.h"

namespace memref
{

RandomReference::RandomReference(int pid, int randnum) : Reference(pid, 0), randnum_(randnum) {}

int RandomReference::simulate(int ref_input, int proc_size, pager::Pager &pager, int time_accessed)
{
    int viraddr = (randnum_ + proc_size) % proc_size;

    pager.reference_by_virtual_addr(viraddr, pid_, time_accessed);

    return viraddr;
}

} // namespace memref