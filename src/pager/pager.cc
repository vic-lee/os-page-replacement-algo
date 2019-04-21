#include "pager.h"

namespace pager
{
Pager::Pager(int machine_size, int page_size, std::string algo_name)
    : MACHINE_SIZE_(machine_size), PAGE_SIZE_(page_size), ALGO_NAME_(algo_name) { }
} // namespace pager