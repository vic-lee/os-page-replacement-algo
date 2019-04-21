#include "driver.h"
#include "../pager/pager.h"
#include "jobmix.h"

namespace driver
{
Driver::Driver(int proc_size, int job_mix, int ref_count)
    : PROC_SIZE_(proc_size), JOB_MIX_(job_mix), REF_COUNT_(ref_count), QUANTUM_(3) { }
} // namespace driver