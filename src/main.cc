#include <tuple>
#include <chrono>
#include <iostream>
#include <algorithm>

#include "io/randintreader.h"
#include "driver/driver.h"
#include "pager/pager.h"
#include "debug.h"

namespace demandpaging
{

typedef std::tuple<int, int, int, int, int, pager::AlgoName, bool, bool> UserInput;

static bool debug_status;
static bool show_rand;

bool debug() { return debug_status; }
bool showrand() { return show_rand; }

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << "\nProgram execution time " << ms << "ms\n";
    }
};

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
    bool SHOWRAND = false;

    if (argc < 7 || argc > 9)
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

            if (argc >= 8 && (atoi(argv[7]) == 1))
                DEBUG = true;

            if (argc >= 9 && (atoi(argv[8]) == 1))
                SHOWRAND = true;
        }
        catch (const std::exception &e)
        {
            std::cout << "An error has occured while reading user input. Terminating..." << std::endl;
            std::cerr << e.what() << '\n';
            exit(10);
        }

        ALGO_NAME = map_to_algoname(RAW_ALGO_NAME);
    }

    return std::make_tuple(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE,
                           JOB_MIX, REF_COUNT, ALGO_NAME,
                           DEBUG, SHOWRAND);
}

} // namespace demandpaging

int main(int argc, char **argv)
{
    namespace dp = demandpaging;

    dp::Timer timer;

    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT;
    pager::AlgoName ALGO_NAME;

    demandpaging::UserInput uin = demandpaging::read_input(argc, argv);

    std::tie(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE,
             JOB_MIX, REF_COUNT, ALGO_NAME,
             dp::debug_status, dp::show_rand) = uin;

    std::cout << "\nMachine size is " << MACHINE_SIZE << "\n"
              << "Page size is " << PAGE_SIZE << "\n"
              << "Process size is " << PROC_SIZE << "\n"
              << "Reference count is " << REF_COUNT << "\n"
              << "Name of algorithm is " << ALGO_NAME << "\n"
              << "Debug mode is " << dp::debug_status << "\n"
              << std::endl;

    io::RandIntReader randintreader;

    pager::Pager pager = pager::Pager(MACHINE_SIZE, PAGE_SIZE, ALGO_NAME, randintreader);
    driver::Driver driver = driver::Driver(PROC_SIZE, JOB_MIX, REF_COUNT, pager, randintreader);

    driver.execute();

    return 0;
}