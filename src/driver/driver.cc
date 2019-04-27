#include "driver.h"
#include "../debug.h"
#include "jobmix.h"
#include "process.h"
#include "mrefspec.h"
#include "jobmixspec.h"
#include "../pager/pager.h"
#include "../io/randintreader.h"

namespace driver
{
namespace dp = demandpaging;

const int Driver::QUANTUM_ = 3;

Driver::Driver(int proc_size, int job_mix, int ref_count, pager::Pager &pager, io::RandIntReader &randintreader)
    : PROC_SIZE_(proc_size), JOB_MIX_DEF_(job_mix),
      REF_COUNT_(ref_count), runtime_(1), randintreader_(randintreader), pager_(pager)
{
    /* Initialize job mix */

    JOB_MIX_ = driver::jobmixspecs::get_jobmix(JOB_MIX_DEF_);

    if (dp::debug())
    {
        JOB_MIX_->print();
    }

    /* Initialize runnable processes */

    int num_of_processes = JOB_MIX_->process_count();

    for (int id = 1; id < (num_of_processes + 1); id++)
        runnable_processes_.push_back(Process(id, PROC_SIZE_, REF_COUNT_));
}

Driver::~Driver() {}

void Driver::execute()
{
    int quantum_ctr = 0;

    while (!is_all_process_terminated())
    {
        if (quantum_ctr == QUANTUM_)
        {   
            context_switch(quantum_ctr);
        }

        runnable_processes_.front().do_reference(pager_, runtime_);

        runnable_processes_.front().set_next_ref_type(randintreader_, JOB_MIX_);

        quantum_ctr++;

        if (runnable_processes_.front().should_terminate())
        {
            runnable_processes_.pop_front();
            quantum_ctr = 0;
        }
        runtime_++;
    }
}

void Driver::context_switch(int &qtm)
{
    Process front_process = runnable_processes_.front();
    runnable_processes_.push_back(front_process);
    runnable_processes_.pop_front();
    qtm = 0;
}

bool Driver::is_all_process_terminated() const
{
    return runnable_processes_.size() == 0;
}

void Driver::debug_print_runnable_processes() const
{
    for (auto &proc : runnable_processes_)
        std::cout << proc << std::endl;
}

} // namespace driver