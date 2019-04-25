#ifndef H_DRIVER
#define H_DRIVER

#include <list>

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
typedef int RefType;

class JobMix;
class Driver
{
public:
    Driver(int proc_size, int job_mix, int ref_count, pager::Pager *pager);
    ~Driver();
    void roundrobin();

private:
    bool is_all_process_terminated() const;
    RefType determine_next_ref_type(int pid);

    void debug_print_runnable_processes() const;

    const int PROC_SIZE_;
    const int JOB_MIX_DEF_;
    const int REF_COUNT_;

    static const int QUANTUM_;
    int runtime_;

    io::RandIntReader *randintreader_;
    JobMix *JOB_MIX_;
    pager::Pager *pager_;

    std::list<Process> runnable_processes_;
};

} // namespace driver

#endif