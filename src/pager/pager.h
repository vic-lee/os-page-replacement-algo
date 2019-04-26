#ifndef H_PAGER
#define H_PAGER

#include <iostream>

namespace pager
{
enum AlgoName
{
    FIFO,
    RANDOM,
    LRU
};

class Frame;

class Pager
{
public:
    Pager(int machine_size, int page_size, AlgoName algo_name);
    ~Pager();
    void reference_by_virtual_addr(int viraddr, int pid, int time_accessed);

private:
    bool can_insert();
    bool insert_front(Frame frame);
    bool write_frame_at_index(int lowest_frame_id, Frame newframe);

    int search_frame(Frame target);
    int search_frame_with_oldest_access_time();

    void swap_frame(Frame newframe);
    void fifo_swap(Frame newframe);
    void random_swap(Frame newframe);
    void lru_swap(Frame newframe);

    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const AlgoName ALGO_NAME_;

    static const int ERR_PAGE_NOT_FOUND_;
    static const int WARN_FRAME_TABLE_EMPTY_;

    Frame *frame_table_;
    int next_insertion_idx_;
};

} // namespace pager

#endif