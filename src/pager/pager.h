#ifndef H_PAGER
#define H_PAGER

#include <iostream>

namespace pager
{

class Pager
{
public:
    Pager(int machine_size, int page_size, std::string algo_name);

private:
    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const std::string ALGO_NAME_;
};

} // namespace pager

#endif