#ifndef H_PROCESS
#define H_PROCESS

namespace pager
{
class Pager;
}

namespace driver
{
typedef int RefType;

class Process
{
public:
    Process(int id, int proc_size, int ref_count);
    void do_reference_of_type(RefType ref_type, int randref_num, pager::Pager pager);

    bool should_terminate() const;
    int id() const;

private:
    void do_next_reference(int delta, int randref_num);

    const int ID_;
    const int SIZE_;
    const int TOTAL_REF_COUNT_;
    static const int INIT_CONST_;

    static const int DELTA_SEQ_;
    static const int DELTA_BACK_;
    static const int DELTA_JMP_;
    static const int DELTA_UNDEF_;
    static const int RANDREF_UNDEF_;

    int current_ref_addr_;
    int remaining_ref_count_;
};
} // namespace driver

#endif