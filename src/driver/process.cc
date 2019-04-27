#include "process.h"
#include "mrefspec.h"
#include "../pager/pager.h"
#include "../io/randintreader.h"

namespace driver
{
const int Process::INIT_CONST_ = 111;
const int Process::RANDREF_UNDEF_ = 0;
const int Process::DELTA_UNDEF_ = 0;
const int Process::REF_ADDR_UNDEF_ = -1;
const int Process::DELTA_SEQ_ = 1;
const int Process::DELTA_BACK_ = -5;
const int Process::DELTA_JMP_ = 4;

Process::Process(int id, int proc_size, int ref_count)
    : ID_(id), SIZE_(proc_size), TOTAL_REF_COUNT_(ref_count),
      current_ref_addr_(REF_ADDR_UNDEF_), next_randref_num_(RANDREF_UNDEF_), remaining_ref_count_(ref_count) {}

void Process::do_reference_of_type(RefType ref_type, pager::Pager &pager, int access_time)
{
    if (ref_type == INIT_REF)
        do_next_reference(DELTA_UNDEF_, pager, access_time);

    else if (ref_type == SEQ_REF)
        do_next_reference(DELTA_SEQ_, pager, access_time);

    else if (ref_type == BACK_REF)
        do_next_reference(DELTA_BACK_, pager, access_time);

    else if (ref_type == JMP_REF)
        do_next_reference(DELTA_JMP_, pager, access_time);

    else if (ref_type == RAND_REF)
        do_next_reference(DELTA_UNDEF_, pager, access_time);
}

void Process::do_next_reference(int delta, pager::Pager &pager, int access_time)
{
    if (remaining_ref_count_ == 0)
        return;

    auto init_ref = [this]() -> int { return (INIT_CONST_ * ID_) % SIZE_; };
    auto calc_rand_ref = [this](int rand) -> int { return (rand + SIZE_) % SIZE_; };
    auto calc_new_ref = [this](int delta) -> int { return (current_ref_addr_ + delta + SIZE_) % SIZE_; };

    if (current_ref_addr_ == REF_ADDR_UNDEF_)
        current_ref_addr_ = init_ref();

    else if (next_randref_num_ > RANDREF_UNDEF_)
        current_ref_addr_ = calc_rand_ref(next_randref_num_);

    else
        current_ref_addr_ = calc_new_ref(delta);

    pager.reference_by_virtual_addr(current_ref_addr_, ID_, access_time);

    remaining_ref_count_--;
}

void Process::read_next_randnum(io::RandIntReader &randintreader)
{
    next_randref_num_ = randintreader.read_next_int();
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
