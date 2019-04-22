#ifndef H_PAGER
#define H_PAGER

#include <iostream>
#include <vector>

namespace pager
{
struct Frame 
{
    int pageid;
    int pid;
};

class Pager
{
public:
    Pager(int machine_size, int page_size, std::string algo_name);
    ~Pager();
    bool push_new_frame(Frame frame);

private:
    const int MACHINE_SIZE_;
    const int PAGE_SIZE_;
    const int FRAME_COUNT_;
    const std::string ALGO_NAME_;

    Frame *frame_table_;
    int next_insertion_idx_;
};

} // namespace pager

#endif