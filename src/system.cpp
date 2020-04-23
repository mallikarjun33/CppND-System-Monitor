#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
    processes_.erase(processes_.begin(), processes_.end());
    vector<int> processIdList = LinuxParser::Pids();
    for(int i:processIdList)
    {
        Process newProcess;
        newProcess.setPid(i);
        processes_.push_back(newProcess);
        std::reverse(processes_.begin(), processes_.end()); //temp to check output
    }

    return processes_;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() {    return LinuxParser::MemoryUtilization();}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }