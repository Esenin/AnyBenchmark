#pragma once

#include <iostream>
#include <vector>

namespace benchmark
{

//! @brief MeasureType choose what kind of system timers will be used
enum class MeasureType
{
    realTime //< measures real time elapsed
    , cpuTime //< measures cpu-used time
    , hybrid //< to decrease devation (based on context-switching for e.g.) it measures 2/3 * cpu + 1/3 real time
};

//! @brief pair of N -- param and average time in [ms] that consumes testing subject
typedef std::vector<std::tuple<int, long double>>  ResultsQueue;

//! @brief selects way file formatting or restricts output to file at all
enum class FileOutput
{
    none = 0
    , humanReadable = 1
    , csv = 2
};


#ifndef NDEBUG
    #define DEBUG(x) do { std::cerr << "DEBUG:" << x << "\n"; } while (false)
    #define DEBUG2(x) do { std::cerr << "DEBUG:" << __func__ << ":" << #x << ": " << x << "\n"; } while (false)
    #define WARNING(x) do { std::cerr << "WARN:" << __FILE__ << " > " << __func__ << ": " << x << "\n"; } while (false)
#else
    #define DEBUG(x) do {} while (false)
    #define DEBUG2(x) do {} while(false)
    #define WARNING(x) do {} while(false)
#endif

}