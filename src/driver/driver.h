#ifndef H_DRIVER
#define H_DRIVER

namespace driver
{
class JobMix;
class Driver
{
public:
    Driver(int proc_size, int job_mix, int ref_count);

private:
    void roundrobin();
    const int PROC_SIZE_;
    const int JOB_MIX_;
    const int REF_COUNT_;
    const int QUANTUM_;
};

} // namespace driver

#endif