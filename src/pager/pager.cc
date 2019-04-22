#include "pager.h"

namespace pager
{
Pager::Pager(int machine_size, int page_size, std::string algo_name)
    : MACHINE_SIZE_(machine_size), PAGE_SIZE_(page_size),
      FRAME_COUNT_(MACHINE_SIZE_ / PAGE_SIZE_), ALGO_NAME_(algo_name) 
{
    frame_table_ = new Frame[FRAME_COUNT_];
    next_insertion_idx_ = FRAME_COUNT_ - 1;
}

Pager::~Pager()
{
    delete frame_table_;
}

bool Pager::push_new_frame(Frame frame)
{
    if (next_insertion_idx_-- < 0)
    {
        return false;
    }
    else
    {
        frame_table_[next_insertion_idx_] = frame;
        next_insertion_idx_--;
        return true;
    }
    
}

} // namespace pager