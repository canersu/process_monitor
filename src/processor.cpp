#include "processor.h"

using std::stol;
using std::vector;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<string> cpu_utils = LinuxParser::CpuUtilization();
    user = cpu_utils[0];
    nice = cpu_utils[1];
    system = cpu_utils[2];
    idle = cpu_utils[3];
    iowait = cpu_utils[4];
    irq = cpu_utils[5];
    softirq = cpu_utils[6];
    steal = cpu_utils[7];

    float PrevIdle = previdle + previowait;
    float Idle = stof(idle) + stof(iowait);
    float PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    float NonIdle = stof(user) + stof(nice) + stof(system) + stof(irq) + stof(softirq) + stof(steal);

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;
    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;
    float CPU_Percentage = (totald - idled) / totald;
    AssignPrev(LinuxParser::CpuUtilization());
    return CPU_Percentage;

}

void Processor::AssignPrev(vector<string> vals){
prevuser = stof(vals[0]);
prevnice = stof(vals[1]);
prevsystem = stof(vals[2]);
previdle = stof(vals[3]);
previowait = stof(vals[4]);
previrq = stof(vals[5]);
prevsoftirq = stof(vals[6]);
prevsteal = stof(vals[7]);
}