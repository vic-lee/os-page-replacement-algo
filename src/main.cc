#include "io/randintreader.h"
#include "io/uin.h"
#include "driver/driver.h"
#include "pager/pager.h"
#include "debug.h"

namespace demandpaging
{

static bool debug_status;
static bool show_rand;

bool debug() { return debug_status; }
bool showrand() { return show_rand; }

} // namespace demandpaging

int main(int argc, char **argv)
{
    namespace dp = demandpaging;

    io::UserInput uin = io::read_input(argc, argv);

    dp::debug_status = uin.debug;
    dp::show_rand = uin.showrand;

    std::cout << "\nThe machine size is " << uin.machine_size << ".\n"
              << "The page size is " << uin.page_size << ".\n"
              << "The process size is " << uin.proc_size << ".\n"
              << "The job mix number is " << uin.jobmix << ".\n"
              << "The number of references per process is " << uin.ref_count << ".\n"
              << "The replacement algorithm is " << uin.raw_algoname << ".\n"
              << "The level of debugging output is " << dp::debug_status << ".\n"
              << std::endl;

    io::RandIntReader randintreader;

    pager::Pager pager = pager::Pager(uin, randintreader);
    driver::Driver driver = driver::Driver(uin, pager, randintreader);

    driver.execute();

    return 0;
}