#ifndef H_DRIVER
#define H_DRIVER

#include <list>

namespace driver
{
class JobMix;
class Process;
class Driver
{
public:
    Driver(int proc_size, int job_mix, int ref_count);

private:
    void roundrobin();
    bool is_all_process_terminated() const;

    const int PROC_SIZE_;
    const int JOB_MIX_DEF_;
    const int REF_COUNT_;
    const int QUANTUM_;

    JobMix *JOB_MIX_;

    std::list<Process *> runnable_processes_;

};

} // namespace driver

#endif