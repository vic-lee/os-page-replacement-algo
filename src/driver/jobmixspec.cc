#include "jobmix.h"
#include "jobmixspec.h"

namespace driver
{
namespace jobmixspecs
{

const bool SAME_JOBMIX_PER_PROCESS = true;
const bool DIFF_JOBMIX_PER_PROCESS = false;

JobMix jobmix_1 = JobMix(1, 1, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{1, 0, 0}});
JobMix jobmix_2 = JobMix(2, 4, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{1, 0, 0}});
JobMix jobmix_3 = JobMix(3, 4, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{0, 0, 0}});
JobMix jobmix_4 = JobMix(4, 4, DIFF_JOBMIX_PER_PROCESS, {
                                                            JobMixPerProcess{0.75, 0.25, 0},
                                                            JobMixPerProcess{0.75, 0, 0.25},
                                                            JobMixPerProcess{0.75, 0.125, 0.125},
                                                            JobMixPerProcess{0.5, 0.125, 0.125},
                                                        });

JobMix *get_jobmix(int id)
{
    switch (id)
    {
    case 1:
        return &jobmix_1;
        break;
    case 2:
        return &jobmix_2;
        break;
    case 3:
        return &jobmix_3;
        break;
    case 4:
        return &jobmix_4;
        break;
    default:
        return nullptr;
        break;
    }
}

} // namespace jobmixspecs
} // namespace driver