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

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
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

// TODO: Return the system's kernel identifier (string) : DONE
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization : DONE
float System::MemoryUtilization() {    return LinuxParser::MemoryUtilization();}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system : DONE
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system : DONE
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running : DONE
long int System::UpTime() { return LinuxParser::UpTime(); }