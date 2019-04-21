#ifndef H_PROCESS
#define H_PROCESS

namespace driver
{
class Process
{
public:
    Process(int id, int proc_size, int ref_count);
    void do_next_sequential_reference();
    void do_next_backward_reference();
    void do_next_jump_reference();
    bool should_terminate() const;
    int id() const;

private:
    void do_next_reference(int delta);

    const int ID_;
    const int SIZE_;
    const int TOTAL_REF_COUNT_;
    const int INIT_CONST_;

    int current_ref_addr_;
    int remaining_ref_count_;
};
} // namespace driverß

#endif