#include "process.h"

namespace driver
{
const int Process::INIT_CONST_ = 111;

Process::Process(int id, int proc_size, int ref_count)
    : ID_(id), SIZE_(proc_size), TOTAL_REF_COUNT_(ref_count),
      current_ref_addr_(-1), remaining_ref_count_(ref_count) {}

void Process::do_next_sequential_reference()
{
    int delta = 1;
    do_next_reference(delta);
}

void Process::do_next_backward_reference()
{
    int delta = -5;
    do_next_reference(delta);
}

void Process::do_next_jump_reference()
{
    int delta = 4;
    do_next_reference(delta);
}

void Process::do_next_reference(int delta)
{
    auto calc_new_ref = [this](int delta) -> int { return (current_ref_addr_ + delta + SIZE_) % SIZE_; };

    current_ref_addr_ = calc_new_ref(delta);

    remaining_ref_count_ = (remaining_ref_count_ == 0) ? 0 : remaining_ref_count_--;
}

void Process::do_initial_reference()
{
    auto init_ref = [this]() -> int { return INIT_CONST_ * ID_ % SIZE_; };

    current_ref_addr_ = init_ref();

    remaining_ref_count_ = (remaining_ref_count_ == 0) ? 0 : remaining_ref_count_--;
}

bool Process::should_terminate() const
{
    return remaining_ref_count_ == 0;
}

int Process::id() const
{
    return ID_;
}

} // namespace driver