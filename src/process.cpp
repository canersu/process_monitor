#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include<linux_parser.h>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() {
  return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
 string line, key, val;
  vector<string> words;
  long utime, stime, cutime, cstime, starttime, total_time, uptime;
  float secs, cpu_usage;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> val) {words.push_back(val);}
  }
  utime = std::stol(words[13]);
  stime = std::stol(words[14]);
  cutime = std::stol(words[15]);
  cstime = std::stol(words[16]);
  starttime = std::stol(words[21]);
  total_time = (utime + stime + cutime + cstime);
  uptime = LinuxParser::UpTime();
  secs = uptime - (starttime/sysconf(_SC_CLK_TCK));
  cpu_usage = (total_time/sysconf(_SC_CLK_TCK))/secs;
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() {
  return LinuxParser::Command(Pid());
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  return LinuxParser::Ram(Pid());
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(Pid());
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime(Pid());
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(const Process& a) const {
  return this->cpu_util_ > a.cpu_util_;
}