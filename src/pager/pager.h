#ifndef H_PAGER
#define H_PAGER

#include <iostream>

namespace pager
{
struct Frame 
{
    int pageid;
    int pid;

    int latest_access_time = -10;
};

typedef std::string AlgoName;

class Pager
{
public:
    Pager(int machine_size, int page_size, std::string algo_name);
    ~Pager();
    void reference_by_virtual_addr(int viraddr, int pid, int time_accessed);

private:
    bool can_insert();
    bool insert_front(Frame frame);
    int search_frame(int pid, int pageid);
    void swap_frame();
    void fifo_swap();
    void random_swap();
    void lru_swap();

    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const std::string ALGO_NAME_;

    static const int ERR_PAGE_NOT_FOUND_;

    static const AlgoName FIFO_;
    static const AlgoName RANDOM_;
    static const AlgoName LRU_;

    Frame *frame_table_;
    int next_insertion_idx_;
};

} // namespace pager

#endif