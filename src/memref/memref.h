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
    Reference(int pid, int delta);
    virtual void simulate(int prior_refnum, int proc_size, pager::Pager &pager, int time_accessed) = 0;

protected:
    int pid_;
    int delta_;
    const int INIT_FACTOR_;
};
} // namespace memref