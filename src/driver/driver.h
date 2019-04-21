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
    int determine_next_ref_type();

    const int PROC_SIZE_;
    const int JOB_MIX_DEF_;
    const int REF_COUNT_;
    
    static const int QUANTUM_;

    static const int SEQ_REF_;  /* Sequential memory reference keyword */
    static const int BACK_REF_; /* Backward memory reference keyword */
    static const int JMP_REF_;  /* Jump memory reference keyword */
    static const int RAND_REF_; /* Random memory reference keyword */

    JobMix *JOB_MIX_;

    std::list<Process *> runnable_processes_;
};

} // namespace driver

#endif