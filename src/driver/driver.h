#ifndef H_DRIVER
#define H_DRIVER

#include <deque>

#include "process.h"

namespace io
{
class RandIntReader;
}

namespace pager
{
class Pager;
}

namespace driver
{
class JobMix;
class Driver
{
public:
    Driver(int proc_size, int job_mix, int ref_count, pager::Pager &pager, io::RandIntReader &randintreader);
    ~Driver();
    void execute();

private:
    void context_switch(int &qtm);
    bool is_all_process_terminated() const;

    void debug_print_runnable_processes() const;

    const int PROC_SIZE_;
    const int JOB_MIX_DEF_;
    const int REF_COUNT_;

    static const int MAX_QUANTUM_;
    int runtime_;

    io::RandIntReader &randintreader_;
    JobMix *JOB_MIX_;
    pager::Pager &pager_;

    std::deque<Process> runnable_processes_;
};

} // namespace driver

#endif