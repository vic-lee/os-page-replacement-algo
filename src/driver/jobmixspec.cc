#include "jobmix.h"

namespace driver
{
namespace jobmixspecs
{

const bool SAME_JOBMIX_PER_PROCESS = true;
const bool DIFF_JOBMIX_PER_PROCESS = false;

JobMix jobmix1 = JobMix(1, 1, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{1, 0, 0}});
JobMix jobmix2 = JobMix(2, 4, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{1, 0, 0}});
JobMix jobmix3 = JobMix(3, 4, SAME_JOBMIX_PER_PROCESS, {JobMixPerProcess{0, 0, 0}});
JobMix jobmix4 = JobMix(4, 4, DIFF_JOBMIX_PER_PROCESS, {
                                                           JobMixPerProcess{0.75, 0.25, 0},
                                                           JobMixPerProcess{0.75, 0, 0.25},
                                                           JobMixPerProcess{0.75, 0.125, 0.125},
                                                           JobMixPerProcess{0.5, 0.125, 0.125},
                                                       });

} // namespace jobmixspecs
} // namespace driver