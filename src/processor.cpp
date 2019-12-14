#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    //return 0.0; 
    std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
                if(key == "processes")
                {
                    total = std::stoi(user) + std::stoi(nice) + std::stoi(system) + std::stoi(idle) + std::stoi(iowait) + std::stoi(irq) + std::stoi(softirq)
                                            + std::stoi(steal) + std::stoi(guest) + std::stoi(guest_nice);
                    return total/10.0;
                }
            }
        }
    }
    return total/10.0;
}