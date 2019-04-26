#include "pager.h"
#include "frame.h"

namespace pager
{
const int Pager::ERR_PAGE_NOT_FOUND_ = -10;
const int Pager::WARN_FRAME_TABLE_EMPTY_ = -11;

Pager::Pager(int machine_size, int page_size, AlgoName algo_name)
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

    std::cout << "Process " << pid
              << " references word " << viraddr
              << " (page " << to_visit_pageid << ") at time " << time_accessed << ": ";

    Frame target_frame = Frame(to_visit_pageid, pid, time_accessed);

    int frame_loc = search_frame(target_frame);

    if (frame_loc == ERR_PAGE_NOT_FOUND_) /* Page Fault */
    {
        std::cout << "Fault, ";

        bool is_insert_sucessful = insert_front(target_frame);

        if (!is_insert_sucessful) /* No free frame(s) remaining */
        {
            swap_frame(target_frame);
        }
    }
    else
    {
        std::cout << "Hit in frame " << frame_loc;
        frame_table_[frame_loc].set_latest_access_time(time_accessed);
    }

    std::cout << std::endl;
}

void Pager::swap_frame(Frame newframe)
{
    if (ALGO_NAME_ == LRU)
        lru_swap(newframe);

    else if (ALGO_NAME_ == FIFO)
        fifo_swap(newframe);

    else if (ALGO_NAME_ == RANDOM)
        random_swap(newframe);
}

void Pager::fifo_swap(Frame newframe)
{
}

void Pager::random_swap(Frame newframe)
{
}

void Pager::lru_swap(Frame newframe)
{
    int lru_frame_idx = search_least_recently_used_frame();

    write_frame_at_index(lru_frame_idx, newframe);
}

int Pager::search_least_recently_used_frame()
{
    /**
     * Locate frame with the oldest (least recent) access time. 
     * Returns the location (index) of that frame.
     * If the frame table is empty, a warning is raised.
     */

    int oldest_idx = FRAME_COUNT_ - 1;

    if (!frame_table_[oldest_idx].is_initialized())
    {
        return WARN_FRAME_TABLE_EMPTY_;
    }

    for (int i = oldest_idx; i >= 0; i--)
    {
        if (frame_table_[i].is_older_than(frame_table_[oldest_idx]))
            oldest_idx = i;
    }

    return oldest_idx;
}

bool Pager::write_frame_at_index(int lowest_frame_id, Frame newframe)
{
    return false;
}

int Pager::search_frame(Frame target)
{
    /**
     * Attempts to find a frame by process ID and page ID. 
     * Returns the frame's location if found; PageNotFound error if not found.
     */

    for (int i = 0; i < FRAME_COUNT_; i++)
    {
        if (frame_table_[i] == target)
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
        std::cout << "using free frame " << next_insertion_idx_;
        frame_table_[next_insertion_idx_] = frame;
        next_insertion_idx_--;
        return true;
    }
}

} // namespace pager