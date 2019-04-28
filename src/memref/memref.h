#pragma once

namespace pager
{
class Pager;
}

namespace memref
{

class Reference
{
public:
    Reference(int pid, int proc_size, int delta);
    virtual void simulate(int prior_refnum, pager::Pager &pager, int time_accessed) = 0;

protected:
    int pid_;
    int proc_size_;
    int delta_;
    const int INIT_FACTOR_;
};
} // namespace memref