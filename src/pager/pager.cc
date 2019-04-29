#include "pager.h"
#include "frame.h"
#include "../debug.h"
#include "../io/randintreader.h"

namespace pager
{
const int Pager::ERR_PAGE_NOT_FOUND_ = -10;
const int Pager::WARN_FRAME_TABLE_EMPTY_ = -11;

namespace dp = demandpaging;

Pager::Pager(int machine_size, int page_size, AlgoName algo_name, io::RandIntReader &randintreader)
    : MACHINE_SIZE_(machine_size), PAGE_SIZE_(page_size),
      FRAME_COUNT_(MACHINE_SIZE_ / PAGE_SIZE_), ALGO_NAME_(algo_name), randintreader_(randintreader)
{
    frame_table_ = new Frame[FRAME_COUNT_];
    next_insertion_idx_ = FRAME_COUNT_ - 1;

    std::cout << "Frame count is " << FRAME_COUNT_ << std::endl;
}

Pager::~Pager()
{
    print_process_stats_map();
    delete[] frame_table_;
}

void Pager::reference_by_virtual_addr(int viraddr, int pid, int time_accessed)
{
    int to_visit_pageid = viraddr / PAGE_SIZE_;

    if (dp::debug())
    {
        std::cout << "Process " << pid
                  << " references word " << viraddr
                  << " (page " << to_visit_pageid << ") at time " << time_accessed << ": ";
    }

    Frame target_frame = Frame(to_visit_pageid, pid, time_accessed);

    int frame_loc = search_frame(target_frame);

    if (frame_loc == ERR_PAGE_NOT_FOUND_) /* Page Fault */
    {
        if (dp::debug())
            std::cout << "Fault, ";

        bool is_insert_sucessful = insert_front(target_frame);

        if (!is_insert_sucessful) /* No free frame(s) remaining */
        {
            swap_frame(target_frame);
        }
    }
    else
    {
        if (dp::debug())
            std::cout << "Hit in frame " << frame_loc;

        frame_table_[frame_loc].set_latest_access_time(time_accessed);
    }

    if (dp::debug())
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
    int i_oldest_frame = search_oldest_frame();

    write_frame_at_index(i_oldest_frame, newframe);
}

void Pager::random_swap(Frame newframe)
{
    auto calc_evict_frame = [this](int randnum) -> int { return (randnum % FRAME_COUNT_); };

    int randnum = randintreader_.read_next_int();

    int evict_frame_idx = calc_evict_frame(randnum);

    write_frame_at_index(evict_frame_idx, newframe);
}

void Pager::lru_swap(Frame newframe)
{
    int lru_frame_idx = search_least_recently_used_frame();

    write_frame_at_index(lru_frame_idx, newframe);
}

int Pager::search_least_recently_used_frame() const
{
    /**
     * Locate frame with the oldest (least recent) access time. 
     * Returns the location (index) of that frame.
     * If the frame table is empty, a warning is raised.
     */

    int i_lru = FRAME_COUNT_ - 1;

    if (!frame_table_[i_lru].is_initialized())
    {
        if (dp::debug())
            std::cout << "WARNING: encounter empty frame table when searching LRU frame";

        return WARN_FRAME_TABLE_EMPTY_;
    }

    for (int i = i_lru; i >= 0; i--)
    {
        if (frame_table_[i].is_less_recently_used_than(frame_table_[i_lru]))
            i_lru = i;
    }

    return i_lru;
}

int Pager::search_oldest_frame() const
{
    int i_oldest = FRAME_COUNT_ - 1;

    if (!frame_table_[i_oldest].is_initialized())
    {
        if (dp::debug())
            std::cout << "WARNING: encounter empty frame table when searching LRU frame";

        return WARN_FRAME_TABLE_EMPTY_;
    }

    for (int i = i_oldest; i >= 0; i--)
    {
        if (frame_table_[i].is_older_than(frame_table_[i_oldest]))
            i_oldest = i;
    }

    return i_oldest;
}

bool Pager::write_frame_at_index(int idx, Frame newframe)
{
    Frame &oldframe = frame_table_[idx];

    record_process_stats_before_eviction(oldframe, newframe);

    if (dp::debug())
    {
        std::cout << "evicting page " << oldframe.page_id()
                  << " of process " << oldframe.pid() << " from frame " << idx;
    }

    frame_table_[idx] = newframe;

    return true;
}

void Pager::record_process_stats_before_eviction(Frame &leaving_frame, Frame &incoming_frame)
{
    int old_pid = leaving_frame.pid();
    int new_pid = incoming_frame.pid();

    int eviction_time = incoming_frame.latest_access_time();
    int residency_time = leaving_frame.residency_time(eviction_time);

    auto leaving_process_stats = process_stats_map_.find(old_pid);

    if (leaving_process_stats == process_stats_map_.end())
    {
        ProcessStats ps = ProcessStats(residency_time);
        process_stats_map_.insert(std::pair<pid, ProcessStats>(old_pid, ps));
    }
    else
    {
        leaving_process_stats->second.sum_residency_time += residency_time;
    }
    // std::cout << "Incr process " << old_pid << "'s restime by " << residency_time << "; ";

    auto incoming_process_stats = process_stats_map_.find(new_pid);

    if (incoming_process_stats == process_stats_map_.end())
    {
        ProcessStats ps = ProcessStats();
        ps.incr_page_fault_count();
        process_stats_map_.insert(std::pair<pid, ProcessStats>(new_pid, ps));
    }
    else
    {
        incoming_process_stats->second.incr_page_fault_count();
    }
    // std::cout << "Incr process " << new_pid << "'s page fault; ";
}

int Pager::search_frame(Frame target) const
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

bool Pager::can_insert() const
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
        if (dp::debug())
            std::cout << "using free frame " << next_insertion_idx_;

        init_process_stats(frame);

        frame_table_[next_insertion_idx_] = frame;
        next_insertion_idx_--;

        return true;
    }
}

void Pager::init_process_stats(Frame &frame)
{
    int target_pid = frame.pid();
    ProcessStats ps = ProcessStats();
    ps.incr_fault_count();
    process_stats_map_.insert(std::pair<pid, ProcessStats>(target_pid, ps));
}

void Pager::print_process_stats_map() const
{
    printf("\n");

    for (auto pstat : process_stats_map_)
    {
        std::cout << "Process " << pstat.first << " had " << pstat.second << std::endl;
    }
}

std::ostream &operator<<(std::ostream &stream, const ProcessStats &p)
{
    stream << p.fault_count << " faults";

    if (p.page_fault_count == 0)
        stream << "\n\tWith no evictions, the average residence is undefined.";
    else
        stream << " and "
               << (p.sum_residency_time / (float)(p.page_fault_count))
               << " average residency.";

    return stream;
}

} // namespace pager