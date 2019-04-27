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
      current_ref_addr_(REF_ADDR_UNDEF_),
      next_randref_num_(RANDREF_UNDEF_),
      next_ref_type_(INIT_REF),
      remaining_ref_count_(ref_count) {}

void Process::do_reference(pager::Pager &pager, int access_time)
{
    switch (next_ref_type_)
    {
    case INIT_REF:
        do_reference(DELTA_UNDEF_, pager, access_time);
        break;

    case SEQ_REF:
        do_reference(DELTA_SEQ_, pager, access_time);
        break;

    case BACK_REF:
        do_reference(DELTA_BACK_, pager, access_time);
        break;

    case JMP_REF:
        do_reference(DELTA_JMP_, pager, access_time);
        break;

    case RAND_REF:
        do_reference(DELTA_UNDEF_, pager, access_time);
        break;

    default:
        break;
    }
}

void Process::do_reference(int delta, pager::Pager &pager, int access_time)
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

void Process::set_next_reftype(RefType nextref)
{
    next_ref_type_ = nextref;
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
