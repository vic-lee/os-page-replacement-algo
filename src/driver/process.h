#ifndef H_PROCESS
#define H_PROCESS

#include <iostream>
#include <memory>

#include "memref.h"
#include "../memref/memref.h"

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
class JobMix;
}

namespace driver
{
class Process
{
public:
    Process(int id, int proc_size, int ref_count);
    void do_reference(pager::Pager &pager, int access_time);
    void set_next_ref_type(io::RandIntReader &randintreader, driver::JobMix *jobmix);

    bool should_terminate() const;
    int id() const;

    friend std::ostream &operator<<(std::ostream &stream, const Process &p);

private:
    const int ID_;
    const int SIZE_;
    const int TOTAL_REF_COUNT_;

    static const int REF_ADDR_UNDEF_; /* Current reference address undefined (uninitialized) */

    int current_ref_addr_;
    std::shared_ptr<memref::Reference> nextref_;
    int remaining_ref_count_;
};
} // namespace driver

#endif