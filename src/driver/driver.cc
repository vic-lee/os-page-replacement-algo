#include "driver.h"
#include "jobmix.h"
#include "process.h"
#include "mrefspec.h"
#include "jobmixspec.h"
#include "../pager/pager.h"
#include "../io/randintreader.h"

namespace driver
{
const int Driver::QUANTUM_ = 3;

Driver::Driver(int proc_size, int job_mix, int ref_count, pager::Pager *pager)
    : PROC_SIZE_(proc_size), JOB_MIX_DEF_(job_mix), REF_COUNT_(ref_count), runtime_(0), pager_(pager)
{
    randintreader_ = new io::RandIntReader();

    /* Initialize job mix */

    JOB_MIX_ = driver::jobmixspecs::get_jobmix(JOB_MIX_DEF_);
    // JOB_MIX_->print();

    /* Initialize runnable processes */

    int num_of_processes = JOB_MIX_->process_count();

    for (int id = 1; id < (num_of_processes + 1); id++)
        runnable_processes_.push_back(Process(id, PROC_SIZE_, REF_COUNT_));
}

Driver::~Driver()
{
    delete randintreader_;
}

void Driver::roundrobin()
{
    int quantum_ctr = 0;
    int randref_num = 0;
    RefType next_ref_type = INIT_REF;

    while (!is_all_process_terminated() && runtime_ < 11)
    {
        if (quantum_ctr == QUANTUM_)
        {
            /* Perform context switch */
            Process front_process = runnable_processes_.front();
            runnable_processes_.push_back(front_process);
            runnable_processes_.pop_front();
            quantum_ctr = 0;
        }

        runnable_processes_.front().do_reference_of_type(next_ref_type, randref_num, pager_, runtime_);

        next_ref_type = determine_next_ref_type(runnable_processes_.front().id());

        if (next_ref_type == RAND_REF)
        {
            randref_num = randintreader_->read_next_int();
        }

        quantum_ctr++;

        if (runnable_processes_.front().should_terminate())
        {
            runnable_processes_.pop_front();
            quantum_ctr = 0;
        }
        runtime_++;
    }
}

bool Driver::is_all_process_terminated() const
{
    return runnable_processes_.size() == 0;
}

RefType Driver::determine_next_ref_type(int pid)
{
    double quotient = randintreader_->calc_next_probability();
    RefType reftype = JOB_MIX_->next_ref_type(quotient, pid);
    return reftype;
}

void Driver::debug_print_runnable_processes() const
{
    for (auto &proc : runnable_processes_)
        std::cout << proc << std::endl;
}

} // namespace driver