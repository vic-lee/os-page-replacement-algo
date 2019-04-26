#include <tuple>
#include <iostream>
#include <algorithm>

#include "driver/driver.h"
#include "pager/pager.h"

namespace demandpaging
{

typedef std::tuple<int, int, int, int, int, pager::AlgoName, bool> UserInput;

static bool debug_status;

bool debug() { return debug_status; }

pager::AlgoName map_to_algoname(std::string raw_algoname)
{
    std::transform(raw_algoname.begin(), raw_algoname.end(), raw_algoname.begin(), ::tolower);
    
    if (raw_algoname == "lru")
        return pager::LRU;
    else if (raw_algoname == "fifo")
        return pager::FIFO;
    else if (raw_algoname == "random")
        return pager::RANDOM;
    else
    {
        std::cout << "The algorithm name entered is not correct. Please double check." << std::endl;
        exit(10);
    }
}

UserInput read_input(int argc, char **argv)
{
    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT = -1;
    pager::AlgoName ALGO_NAME;
    std::string RAW_ALGO_NAME = "";
    bool DEBUG = false;

    if (argc != 7 && argc != 8)
    {
        std::cout << "You did not enter the right number of parameters. Terminating..." << std::endl;
        exit(10);
    }
    else
    {
        try
        {
            MACHINE_SIZE = atoi(argv[1]);
            PAGE_SIZE = atoi(argv[2]);
            PROC_SIZE = atoi(argv[3]);
            JOB_MIX = atoi(argv[4]);
            REF_COUNT = atoi(argv[5]);
            RAW_ALGO_NAME = argv[6];

            if (argc == 8 && (atoi(argv[7]) == 1))
                DEBUG = true;
        }
        catch (const std::exception &e)
        {
            std::cout << "An error has occured while reading user input. Terminating..." << std::endl;
            std::cerr << e.what() << '\n';
            exit(10);
        }

        ALGO_NAME = map_to_algoname(RAW_ALGO_NAME);
    }

    return std::make_tuple(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT, ALGO_NAME, DEBUG);
}

} // namespace demandpaging

int main(int argc, char **argv)
{
    namespace dp = demandpaging;

    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT;
    pager::AlgoName ALGO_NAME;

    demandpaging::UserInput uin = demandpaging::read_input(argc, argv);
    std::tie(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT, ALGO_NAME, dp::debug_status) = uin;

    std::cout << "Machine size is " << MACHINE_SIZE << "\n"
              << "Page size is " << PAGE_SIZE << "\n"
              << "Process size is " << PROC_SIZE << "\n"
              << "Reference count is " << REF_COUNT << "\n"
              << "Name of algorithm is " << ALGO_NAME << "\n"
              << "Debug mode is " << dp::debug_status << "\n"
              << std::endl;

    pager::Pager pager = pager::Pager(MACHINE_SIZE, PAGE_SIZE, ALGO_NAME);
    driver::Driver driver = driver::Driver(PROC_SIZE, JOB_MIX, REF_COUNT, &pager);

    driver.roundrobin();

    return 0;
}