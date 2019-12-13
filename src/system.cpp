#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include<iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    //return string(); }
    string os, version, kernel, line;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    if(stream.is_open())
    {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}
// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
  string line, key, value;
  float mem_total, mem_free;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> value)
      {
        if(key == "MemTotal:")
        {
          mem_total = std::stof(value);
        }
        if(key == "MemFree:")
        {
          mem_free = std::stof(value);
        }
      }
    }
  }
  return (mem_free/mem_total);
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  string line, key, value;
  std::ifstream filestream(LinuxParser::kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
  string line, key, value;
  int val = 0;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if(key == "processes")
        {
          val = std::stoi(value);
          return val;
        }
      }
    }  
  }
  return val;
}


// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
  string line, key, value;
  int val = 0;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if(key == "procs_running")
        {
          val = std::stoi(value);
          return val;
        }
      }
    }  
  }
  return val;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    string line, total_time, second_time;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    if(stream.is_open())
    {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> total_time >> second_time;
      return std::stol(total_time);
    }
    return std::stol(total_time);
}