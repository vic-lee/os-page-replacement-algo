#include <tuple>
#include <iostream>

namespace demandpaging
{

typedef std::tuple<int, int, int, int, int, std::string, bool> UserInput;

UserInput read_input(int argc, char **argv)
{
    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT = -1;
    std::string ALGO_NAME = "";
    bool DEBUG = false;

    if (argc != 7 && argc != 8)
    {
        std::cout
            << "You did not enter the right number of parameters. Terminating..."
            << std::endl;
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
            ALGO_NAME = argv[6];

            if (argc == 8 && (atoi(argv[7]) == 1))
                DEBUG = true;
        }
        catch (const std::exception &e)
        {
            std::cout << "An error has occured while reading user input." << std::endl;
            std::cerr << e.what() << '\n';
        }
    }

    return std::make_tuple(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT, ALGO_NAME, DEBUG);
}

} // namespace demandpaging

int main(int argc, char **argv)
{
    int MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT;
    std::string ALGO_NAME;
    bool DEBUG;

    demandpaging::UserInput uin = demandpaging::read_input(argc, argv);
    std::tie(MACHINE_SIZE, PAGE_SIZE, PROC_SIZE, JOB_MIX, REF_COUNT, ALGO_NAME, DEBUG) = uin;

    std::cout << "Machine size is " << MACHINE_SIZE << "\n"
              << "Page size is " << PAGE_SIZE << "\n"
              << "Process size is " << PROC_SIZE << "\n"
              << "Reference count is " << REF_COUNT << "\n"
              << "Name of algorithm is " << ALGO_NAME << "\n"
              << "Debug mode is " << DEBUG << "\n"
              << std::endl;

    return 0;
}