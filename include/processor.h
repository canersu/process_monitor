#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <linux_parser.h>

using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  string user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  string key, line;
  float total;
};

#endif