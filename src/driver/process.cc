#include "process.h"

#include <memory>

#include "jobmix.h"
#include "memref.h"
#include "../pager/pager.h"
#include "../memref/memref.h"
#include "../memref/memref_init.h"
#include "../memref/memref_rand.h"
#include "../io/randintreader.h"

namespace driver
{
const int Process::RANDREF_UNDEF_ = 0;
const int Process::DELTA_UNDEF_ = 0;
const int Process::REF_ADDR_UNDEF_ = -1;

Process::Process(int id, int proc_size, int ref_count)
    : ID_(id), SIZE_(proc_size), TOTAL_REF_COUNT_(ref_count),
      current_ref_addr_(REF_ADDR_UNDEF_),
      next_randref_num_(RANDREF_UNDEF_),
      remaining_ref_count_(ref_count)
{
    nextref_ = std::unique_ptr<memref::Reference>{new memref::InitialReference(ID_)};
}

void Process::do_reference(pager::Pager &pager, int access_time)
{
    if (remaining_ref_count_ == 0)
        return;

    current_ref_addr_ = nextref_->simulate(current_ref_addr_, SIZE_, pager, access_time);

    remaining_ref_count_--;
}

void Process::read_next_randnum(io::RandIntReader &randintreader)
{
    next_randref_num_ = randintreader.read_next_int();
}

void Process::set_next_ref_type(io::RandIntReader &randintreader, driver::JobMix *jobmix)
{
    double quotient = randintreader.calc_next_probability();
    nextref_ = jobmix->next_ref_type(quotient, ID_);

    std::string reftype = typeid(nextref_).name();
    if (reftype == "RandomReference")
        read_next_randnum(randintreader);
}

bool Process::should_terminate() const
{
    return remaining_ref_count_ == 0;
}

int Process::id() const
{
    return ID_;
}

std::ostream &operator<<(std::ostream &stream, const Process &p)
{
    stream << "Process " << p.ID_ << ":\t"
           << " size " << p.SIZE_ << ", total reference count " << p.TOTAL_REF_COUNT_
           << ", remaining reference count: " << p.remaining_ref_count_;
    return stream;
}

} // namespace driver
