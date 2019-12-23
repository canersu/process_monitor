#include <string>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    string s_hr, s_min, s_sec;
    int hr, min, sec;
    min = seconds/60;
    hr = min/60;
    sec = seconds%60;
    if(hr<10){s_hr = "0"+std::to_string(hr);}
    if(hr>=10){s_hr = std::to_string(hr);}
    if(min<10){s_min = "0"+std::to_string(min);}
    if(min>=10){s_min = std::to_string(min%60);}
    if(sec<10){s_sec = "0"+std::to_string(sec);}
    if(sec>=10){s_sec = std::to_string(sec);}

    return s_hr + ":" + s_min + ":" + s_sec;
}