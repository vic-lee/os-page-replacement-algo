#ifndef H_DRIVER
#define H_DRIVER

#include <list>

// #include "../io/randintreader.h"
#include "process.h"

namespace io
{
class RandIntReader;
}

namespace driver
{
typedef int RefType;

class JobMix;
class Driver
{
public:
    Driver(int proc_size, int job_mix, int ref_count);
    ~Driver();

private:
    void roundrobin();
    bool is_all_process_terminated() const;
    RefType determine_next_ref_type(int pid);
    void do_reference(Process &p, RefType ref_type);

    const int PROC_SIZE_;
    const int JOB_MIX_DEF_;
    const int REF_COUNT_;

    static const int QUANTUM_;

    io::RandIntReader *randintreader_;
    JobMix *JOB_MIX_;

    std::list<Process> runnable_processes_;
};

} // namespace driver

#endif