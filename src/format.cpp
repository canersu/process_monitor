#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hr, min;
    min = seconds/60;
    hr = min/60;
    return std::to_string(hr) + ":" + std::to_string(min%60) + ":" + std::to_string(seconds%60);
}