#include <vector>

namespace driver
{

struct JobMixPerProcess
{
    double sequential_ref_dist;
    double backward_ref_dist;
    double jump_ref_dist;
    double rand_ref_dist;
};

class JobMix
{
public:
    JobMix(int id, int proc_count, bool is_uniform, std::vector<JobMixPerProcess> jobmixes);
    JobMix();
    void print();

private:
    const int PROC_COUNT_;
    const bool IS_UNIFORM_;
    std::vector<JobMixPerProcess> JOBMIXES_;
};
} // namespace driver