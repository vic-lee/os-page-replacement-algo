#include <tuple>
#include <string.h>
#include <sstream>
#include <algorithm>

#include "io/randintreader.h"
#include "driver/driver.h"
#include "pager/pager.h"
#include "debug.h"

namespace demandpaging
{

static bool debug_status;
static bool show_rand;

bool debug() { return debug_status; }
bool showrand() { return show_rand; }

struct UserInput
{
    int machine_size;
    int page_size;
    int proc_size;
    int jobmix;
    int ref_count;
    pager::AlgoName algoname;
    bool debug;
    bool showrand;

    UserInput()
        : machine_size(-1), page_size(-1), proc_size(-1),
          jobmix(-1), ref_count(-1), debug(false), showrand(false){};
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

UserInput read_predefined_input(int argc, char **argv)
{
    UserInput uin = UserInput();
    std::string raw_algoname;

    int input_id;

    if (argc == 4)
    {
        std::string arg = argv[2];

        if (arg == "--showrand" || arg == "-s")
            uin.showrand = true;

        else
            std::cout
                << "Warning: You may have entered `--showrand` or `-s` incorrectly."
                << std::endl;

        input_id = atoi(argv[3]);
    }

    if (argc == 3)
    {
        std::string arg = argv[1];

        if (arg == "--debug" || arg == "-d")
            uin.debug = true;

        else
            std::cout
                << "Warning: You may have entered `--debug` or `-d` incorrectly."
                << std::endl;

        input_id = atoi(argv[2]);
    }

    if (argc == 2)
        input_id = atoi(argv[1]);

    if (input_id < 1 || input_id > 16)
    {
        std::cout << "Input must be between 1 and 16. Terminating..." << std::endl;
        exit(10);
    }

    int line_ctr = 0;

    std::fstream infile("src/io/sample-in.txt");

    if (infile)
    {
        std::string line;

        while (std::getline(infile, line))
        {
            if (line_ctr != (input_id - 1))
            {
                line_ctr++;
                continue;
            }

            std::istringstream iss(line);

            if (!(iss >> uin.machine_size >> uin.page_size >> uin.proc_size >> uin.jobmix >> uin.ref_count >> raw_algoname))
            {
                std::cout << "Text file corrupted. Terminating..." << std::endl;
                exit(10);
            }

            uin.algoname = map_to_algoname(raw_algoname);
            break;
        }

        infile.close();
    }
    else
    {
        std::cout << "An error occured opening the text file. Terminating..." << std::endl;
        exit(10);
    }

    return uin;
}

UserInput read_custom_input(int argc, char **argv)
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

UserInput read_input(int argc, char **argv)
{
    if (argc >= 2 && argc <= 4)
    {
        return read_predefined_input(argc, argv);
    }
    else if (argc >= 7 && argc <= 9)
    {
        return read_custom_input(argc, argv);
    }
    else
    {
        std::cout
            << "You did not enter the right number of parameters. Terminating..."
            << std::endl;

        exit(10);
    }
}

} // namespace demandpaging

int main(int argc, char **argv)
{
    namespace dp = demandpaging;

    dp::Timer timer;

    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT;
    pager::AlgoName ALGO_NAME;

    demandpaging::UserInput uin = demandpaging::read_input(argc, argv);

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