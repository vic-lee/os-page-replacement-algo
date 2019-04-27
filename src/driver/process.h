#ifndef H_PROCESS
#define H_PROCESS

#include <iostream>
#include "mrefspec.h"

namespace pager
{
class Pager;
}

namespace io
{
class RandIntReader;
}

namespace driver
{
class Process
{
public:
    Process(int id, int proc_size, int ref_count);
    void do_reference_of_type(RefType ref_type, pager::Pager &pager, int access_time);
    void read_next_randnum(io::RandIntReader &randintreader);
    void set_next_reftype(RefType nextref);

    bool should_terminate() const;
    int id() const;

    friend std::ostream &operator<<(std::ostream &stream, const Process &p);

private:
    void do_next_reference(int delta, pager::Pager &pager, int access_time);

    const int ID_;
    const int SIZE_;
    const int TOTAL_REF_COUNT_;

    static const int INIT_CONST_; /* Constant factor for initializing reference address */

    static const int DELTA_SEQ_;  /* Change in memory reference when in sequential reference mode */
    static const int DELTA_BACK_; /* Change in memory reference when in backward reference mode */
    static const int DELTA_JMP_;  /* Change in memory reference when in jump reference mode */

    static const int DELTA_UNDEF_;    /* Special status code signifying Delta is undefined */
    static const int RANDREF_UNDEF_;  /* Special status code signifying random reference number is undefined */
    static const int REF_ADDR_UNDEF_; /* Current reference address undefined (uninitialized) */

    int current_ref_addr_;
    int next_randref_num_;
    RefType next_ref_type_;
    int remaining_ref_count_;
};
} // namespace driver

#endif