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

    dp::Timer timer;

    io::UserInput uin = io::read_input(argc, argv);

    dp::debug_status = uin.debug;
    dp::show_rand = uin.showrand;

    std::cout << "\nMachine size is " << uin.machine_size << "\n"
              << "Page size is " << uin.page_size << "\n"
              << "Process size is " << uin.proc_size << "\n"
              << "Reference count is " << uin.ref_count << "\n"
              << "Name of algorithm is " << uin.algoname << "\n"
              << "Debug mode is " << dp::debug_status << "\n"
              << std::endl;

    io::RandIntReader randintreader;

    pager::Pager pager = pager::Pager(uin, randintreader);
    driver::Driver driver = driver::Driver(uin, pager, randintreader);

    driver.execute();

    return 0;
}