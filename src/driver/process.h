#ifndef H_PROCESS
#define H_PROCESS

namespace driver
{
typedef int RefType;

class Process
{
public:
    Process(int id, int proc_size, int ref_count);
    void do_reference_of_type(RefType ref_type, int randref_num);

    bool should_terminate() const;
    int id() const;

private:
    void do_next_sequential_reference();
    void do_next_backward_reference();
    void do_next_jump_reference();
    void do_next_random_reference(int randref_num);
    void do_initial_reference();
    void do_next_reference(int delta);

    const int ID_;
    const int SIZE_;
    const int TOTAL_REF_COUNT_;
    static const int INIT_CONST_;

    int current_ref_addr_;
    int remaining_ref_count_;
};
} // namespace driver

#endif