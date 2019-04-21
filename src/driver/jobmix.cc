#include <iostream>

#include "jobmix.h"

namespace driver
{
JobMix::JobMix(int id, int proc_count, bool is_uniform, std::vector<JobMixPerProcess> jobmixes)
    : PROC_COUNT_(proc_count), IS_UNIFORM_(is_uniform), JOBMIXES_(jobmixes)
{
    auto calc_rand_ref_dist = [](double a, double b, double c, int s) -> double { return (1 - a - b - c) / (double)s; };

    for (auto &jobmix : JOBMIXES_)
    {
        jobmix.rand_ref_dist = calc_rand_ref_dist(jobmix.sequential_ref_dist,
                                                  jobmix.backward_ref_dist,
                                                  jobmix.jump_ref_dist,
                                                  PROC_COUNT_);
    }
}

void JobMix::print()
{
    for (auto &jobmix : JOBMIXES_)
    {
        std::cout << "JobMix sequential ref dist (A): " << jobmix.sequential_ref_dist << "\n"
                  << "JobMix backward ref dist (B): " << jobmix.backward_ref_dist << "\n"
                  << "JobMix jump ref dist (C): " << jobmix.jump_ref_dist << "\n"
                  << "JobMix rand ref dist (D): " << jobmix.rand_ref_dist << "\n" << std::endl;
    }
}
} // namespace driver