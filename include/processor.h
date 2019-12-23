#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <linux_parser.h>
#include <vector>

using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void AssignPrev(std::vector<string> vals);

  // TODO: Declare any necessary private members
 private:
  string user, nice, system, idle, iowait, irq, softirq, steal;
  float prevuser, prevnice, prevsystem, previdle, previowait, previrq, prevsoftirq, prevsteal;
};

#endif