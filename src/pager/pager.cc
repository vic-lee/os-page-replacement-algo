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

    int frame_loc = search_frame(pid, to_visit_pageid);

    if (frame_loc == ERR_PAGE_NOT_FOUND_) /* Page Fault */
    {
        std::cout
            << pid << " Page Fault:\tframe for word " << viraddr
            << " at time " << time_accessed << " not found"
            << std::endl;

        Frame new_frame = Frame(to_visit_pageid, pid, time_accessed);

        bool is_insert_sucessful = insert_front(new_frame);

        if (!is_insert_sucessful) /* No free frame(s) remaining */
        {
            swap_frame(new_frame);
        }
    }
    else
    {
        std::cout << "Frame located at " << frame_loc << std::endl;
        frame_table_[frame_loc].set_latest_access_time(time_accessed);
    }
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
    int lowest_frame_id = search_frame_with_oldest_access_time();

    if (lowest_frame_id == WARN_FRAME_TABLE_EMPTY_)
    {
        insert_front(newframe);
    }
    else
    {
        write_frame_at_index(lowest_frame_id, newframe);
    }
}

int Pager::search_frame_with_oldest_access_time()
{
    /**
     * Locate frame with the oldest (least recent) access time. 
     * Returns the location (index) of that frame.
     * If the frame table is empty, a warning is raised.
     */

    int lowest_idx = FRAME_COUNT_ - 1;
    int oldest_access_time = -1;

    if (frame_table_[lowest_idx].page_id() == -10)
    {
        return WARN_FRAME_TABLE_EMPTY_;
    }
    else
    {
        oldest_access_time = frame_table_[lowest_idx].latest_access_time();
    }

    for (int i = lowest_idx; i >= 0; i--)
    {
        if (frame_table_[i].latest_access_time() < oldest_access_time)
        {
            lowest_idx = i;
            oldest_access_time = frame_table_[i].latest_access_time();
        }
    }

    return lowest_idx;
}

bool Pager::write_frame_at_index(int lowest_frame_id, Frame newframe)
{
    return false;
}

int Pager::search_frame(int pid, int pageid)
{
    /**
     * Attempts to find a frame by process ID and page ID. 
     * Returns the frame's location if found; PageNotFound error if not found.
     */

    for (int i = 0; i < FRAME_COUNT_; i++)
    {
        if (frame_table_[i].pid() == pid && frame_table_[i].page_id() == pageid)
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