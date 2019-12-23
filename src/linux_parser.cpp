#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
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

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, key, value;
  float mem_total, mem_free, buffers, cached, SReclaimable, Shmem;
  float green, blue, yellow, total;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> value)
      {
        if(key == "MemTotal:"){mem_total = std::stof(value);}
        if(key == "MemFree:"){mem_free = std::stof(value);}
        if(key == "Buffers:"){buffers = std::stof(value);}
        if(key == "Cached:"){cached = std::stof(value);}
        if(key == "SReclaimable:"){SReclaimable = std::stof(value);}
        if(key == "Shmem:"){Shmem = std::stof(value);}
      }
    }
  }
  total = mem_total - mem_free;
  green = total - (buffers + cached);
  blue = buffers;
  yellow = cached + SReclaimable - Shmem; 
  
  return ((green+blue+yellow)/mem_total);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    string line, total_time, second_time;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    if(stream.is_open())
    {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> total_time >> second_time;
      return stol(total_time);
    }
    return stol(total_time);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  string user, nice, system, idle, iowait, irq, softirq, steal;
  string key, line;
  long j_total = 0;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if(stream.is_open())
  {
     std::istringstream linestream(line);
    while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal)
    {
      if(key == "cpu")
      {
        j_total = stol(user) + stol(nice) + stol(system) + stol(idle) + stol(iowait) + 
                stol(irq) + stol(softirq) + stol(steal);
      }
    }
  }
  return j_total;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line, key, val;
  vector<string> words;
  long utime, stime, cutime, cstime, starttime, active_jiffies;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> val) {
      words.push_back(val);
    }
  }
  utime = stol(words[13]);
  stime = stol(words[14]);
  cutime = stol(words[15]);
  cstime = stol(words[16]);
  starttime = stol(words[21]);
  active_jiffies = (utime + stime + cutime + cstime) - starttime;
  return active_jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  string user, nice, system, idle, iowait, irq, softirq, steal;
  string key, line;
  long j_active = 0;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if(stream.is_open())
  {
     std::istringstream linestream(line);
    while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal)
    {
      if(key == "cpu")
      {
        j_active = stol(user) + stol(nice) + stol(system) + stol(irq) + stol(softirq) + stol(steal);
      }
    }
  }
  return j_active;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string user, nice, system, idle, iowait, irq, softirq, steal;
  string key, line;
  long j_idle = 0;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if(stream.is_open())
  {
     std::istringstream linestream(line);
    while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal)
    {
      if(key == "cpu"){j_idle = stol(idle) + stol(iowait);}
    }
  }
  return j_idle;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line, val, key, lineofline, valofline;
  vector<string> cpu_utils;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if(stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> val) {
      val.erase(remove_if(val.begin(), val.end(), isspace), val.end());
      cpu_utils.push_back(val);
    }
  }
  cpu_utils.erase(cpu_utils.begin());
  return cpu_utils;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  int val = 0;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if(key == "procs_running") {val = std::stoi(value);}
      }
    }  
  }
  return val;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  int val = 0;
  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if(key == "processes"){val = std::stoi(value);}
      }
    }  
  }
  return val;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, command;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kCmdlineFilename);
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> command;
    return command;
  }
  return command;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, val, ram;
  long ram_val;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> val)
      {
        if(key == "VmSize:")
        {
          ram = val;
          ram_val = stol(ram)/1024;
        }
      }
    }
  }
  return to_string(ram_val);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, val;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  if(filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> val)
      {
        if(key == "Uid:"){return val;}
      }
    }
  }
  return val;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, user, x, uid;
  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> x >> uid) {
        if(Uid(pid) == uid){return user;}
      }
    }
  }
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, key, val;
  vector<string> words;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> val) {words.push_back(val);}
  }
  return UpTime() - stol(words[21])/sysconf(_SC_CLK_TCK);
}