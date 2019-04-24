#ifndef H_PAGER
#define H_PAGER

#include <iostream>

namespace pager
{
struct Frame
{
    Frame() : pageid(-10), pid(-10), latest_access_time(-10){};
    Frame(int pageid, int pid) : pageid(), pid(), latest_access_time(-10){};
    Frame(int pageid, int pid, int access_time) : pageid(), pid(), latest_access_time(access_time){};
    int pageid;
    int pid;
    int latest_access_time;
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
    bool write_frame_at_index(int lowest_frame_id, Frame newframe);

    int search_frame(int pid, int pageid);
    int search_frame_with_oldest_access_time();

    void swap_frame(Frame newframe);
    void fifo_swap(Frame newframe);
    void random_swap(Frame newframe);
    void lru_swap(Frame newframe);

    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const std::string ALGO_NAME_;

    static const int ERR_PAGE_NOT_FOUND_;
    static const int WARN_FRAME_TABLE_EMPTY_;

    static const AlgoName FIFO_;
    static const AlgoName RANDOM_;
    static const AlgoName LRU_;

    Frame *frame_table_;
    int next_insertion_idx_;
};

} // namespace pager

#endif