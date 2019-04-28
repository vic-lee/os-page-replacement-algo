#ifndef H_DEBUG
#define H_DEBUG

#include <chrono>
#include <iostream>

namespace demandpaging
{

static bool debug_status;
static bool show_rand;

bool debug();
bool showrand();

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

} // namespace demandpaging

#endif