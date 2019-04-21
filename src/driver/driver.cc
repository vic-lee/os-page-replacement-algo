#include "driver.h"
#include "jobmix.h"
#include "jobmixspec.h"
#include "../pager/pager.h"

namespace driver
{
Driver::Driver(int proc_size, int job_mix, int ref_count)
    : PROC_SIZE_(proc_size), JOB_MIX_DEF_(job_mix), REF_COUNT_(ref_count), QUANTUM_(3)
{

    JOB_MIX_ = driver::jobmixspecs::get_jobmix(JOB_MIX_DEF_);
    JOB_MIX_->print();
}

void Driver::roundrobin()
{
    while (is_all_process_terminated())
    {
        /* Do process */
    }
}

bool Driver::is_all_process_terminated()
{
    return runnable_processes_.size() == 0;
}

} // namespace driver