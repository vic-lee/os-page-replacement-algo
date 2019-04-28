#pragma once

namespace memref
{

class Reference
{
public:
    Reference(int pid, int delta);
    virtual void simulate() = 0;

private:
    int pid_;
    int delta_;
    const int INIT_FACTOR_;
};
} // namespace memref