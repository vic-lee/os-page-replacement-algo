#include "uin.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace io
{

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

io::UserInput read_predefined_input(int argc, char **argv)
{
    io::UserInput uin = io::UserInput();
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

io::UserInput read_custom_input(int argc, char **argv)
{
    io::UserInput uin = io::UserInput();
    std::string raw_algoname = "";

    try
    {
        uin.machine_size = atoi(argv[1]);
        uin.page_size = atoi(argv[2]);
        uin.proc_size = atoi(argv[3]);
        uin.jobmix = atoi(argv[4]);
        uin.ref_count = atoi(argv[5]);
        raw_algoname = argv[6];
        uin.algoname = map_to_algoname(raw_algoname);

        if (argc >= 8 && (atoi(argv[7]) == 1))
            uin.debug = true;

        if (argc >= 9 && (atoi(argv[8]) == 1))
            uin.showrand = true;
    }
    catch (const std::exception &e)
    {
        std::cout << "An error has occured while reading user input. Terminating..." << std::endl;
        std::cerr << e.what() << '\n';
        exit(10);
    }

    return uin;
}

io::UserInput read_input(const int &argc, char **argv)
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

}