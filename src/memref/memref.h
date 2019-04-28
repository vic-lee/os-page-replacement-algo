#pragma once

namespace memref
{

class Reference
{
public:
    Reference(int delta);

private:
    int delta_;
    const int INIT_FACTOR_;
};
} // namespace memref