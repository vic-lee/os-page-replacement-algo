#include <vector>

namespace driver
{
typedef int RefType;

struct JobMixPerProcess
{
    double sequential_ref_dist; /* A */
    double backward_ref_dist;   /* B */
    double jump_ref_dist;       /* C */
    double rand_ref_dist;       /* 1 - A - B - C */

    double sequential_ref_threshold; /* A */
    double backward_ref_threshold;   /* A + B */
    double jump_ref_threshold;       /* A + B + C */
};

class JobMix
{
public:
    JobMix(int id, int proc_count, bool is_uniform, std::vector<JobMixPerProcess> jobmixes);
    JobMix();
    RefType next_ref_type(double quotient, int pid) const;
    int process_count() const;
    void print() const;

private:
    const int ID_;
    const int PROC_COUNT_;
    const bool IS_UNIFORM_;

    std::vector<JobMixPerProcess> JOBMIXES_;
};
} // namespace driver