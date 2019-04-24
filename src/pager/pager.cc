#include "pager.h"

namespace pager
{
const int Pager::ERR_PAGE_NOT_FOUND_ = -10;
const AlgoName Pager::LRU_ = "LRU";
const AlgoName Pager::FIFO_ = "FIFO";
const AlgoName Pager::RANDOM_ = "RANDOM";

Pager::Pager(int machine_size, int page_size, std::string algo_name)
    : MACHINE_SIZE_(machine_size), PAGE_SIZE_(page_size),
      FRAME_COUNT_(MACHINE_SIZE_ / PAGE_SIZE_), ALGO_NAME_(algo_name)
{
    frame_table_ = new Frame[FRAME_COUNT_];
    next_insertion_idx_ = FRAME_COUNT_ - 1;
}

Pager::~Pager()
{
    delete[] frame_table_;
}

void Pager::reference_by_virtual_addr(int viraddr, int pid, int time_accessed)
{
    int to_visit_pageid = viraddr / PAGE_SIZE_;

    int frame_loc = search_frame(pid, to_visit_pageid);

    if (frame_loc == ERR_PAGE_NOT_FOUND_) /* Page Fault */
    {
        Frame new_frame = Frame{to_visit_pageid, pid};

        bool is_insert_sucessful = insert_front(new_frame);

        if (!is_insert_sucessful) /* No free frame(s) remaining */
        {
            swap_frame();
        }
    }
    else
    {
        frame_table_[frame_loc].latest_access_time = time_accessed;
    }
}

void Pager::swap_frame()
{
    if (ALGO_NAME_ == LRU_)
        lru_swap();

    else if (ALGO_NAME_ == FIFO_)
        fifo_swap();

    else if (ALGO_NAME_ == RANDOM_)
        random_swap();
}

void Pager::fifo_swap()
{
}

void Pager::random_swap()
{
}

void Pager::lru_swap()
{
}

int Pager::search_frame_with_oldest_access_time()
{
    /**
     * Locate frame with the oldest (least recent) access time. 
     * Returns the location (index) of that frame.
     */

    int lowest_idx = FRAME_COUNT_ - 1;
    /* What if the array is empty? */

    for (int i = lowest_idx; i >= 0; i--)
    {
    }

    return lowest_idx;
}

int Pager::search_frame(int pid, int pageid)
{
    /**
     * Attempts to find a frame by process ID and page ID. 
     * Returns the frame's location if found; PageNotFound error if not found.
     */

    for (int i = 0; i < FRAME_COUNT_; i++)
    {
        if (frame_table_[i].pid == pid && frame_table_[i].pageid == pageid)
            return i;
    }
    return ERR_PAGE_NOT_FOUND_;
}

bool Pager::can_insert()
{
    return next_insertion_idx_ >= 0;
}

bool Pager::insert_front(Frame frame)
{
    if (!can_insert())
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