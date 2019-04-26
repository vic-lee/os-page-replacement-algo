#ifndef H_PAGER
#define H_PAGER

#include <iostream>
#include <map>

namespace pager
{

enum AlgoName
{
    FIFO,
    RANDOM,
    LRU
};

struct ProcessStats
{
    int sum_residency_time;
    int page_fault_count;

    ProcessStats(int sum_residency_time) : sum_residency_time(), page_fault_count(1){};
    friend std::ostream &operator<<(std::ostream &stream, const ProcessStats &p);
};

typedef int pid;

class Frame;

class Pager
{
public:
    Pager(int machine_size, int page_size, AlgoName algo_name);
    ~Pager();
    void reference_by_virtual_addr(int viraddr, int pid, int time_accessed);

private:
    bool can_insert() const;
    bool insert_front(Frame frame);

    void record_process_stats_before_eviction(Frame &oldframe, Frame &newframe);
    bool write_frame_at_index(int idx, Frame newframe);

    int search_frame(Frame target) const;
    int search_least_recently_used_frame() const;

    void swap_frame(Frame newframe);
    void fifo_swap(Frame newframe);
    void random_swap(Frame newframe);
    void lru_swap(Frame newframe);

    void print_process_stats_map() const;

    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const AlgoName ALGO_NAME_;

    static const int ERR_PAGE_NOT_FOUND_;
    static const int WARN_FRAME_TABLE_EMPTY_;

    Frame *frame_table_;
    int next_insertion_idx_;

    std::map<pid, ProcessStats> process_stats_map_;
};

} // namespace pager

#endif