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

    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const std::string ALGO_NAME_;

    static const int ERR_PAGE_NOT_FOUND_;

    Frame *frame_table_;
    int next_insertion_idx_;
};

} // namespace pager

#endif