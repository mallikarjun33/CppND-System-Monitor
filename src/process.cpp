#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <linux_parser.h>

#include "process.h"


using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }


// TODO: set this process's ID
void Process::setPid(int id) {pid_=id;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    /*
    string cpu;
    int user, nice, system, idle, iowait, irq, softirq;
    string line;
    std::ifstream stream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    }

    float totalTime = user + nice + system + idle + iowait + irq + softirq;
    float idleTimePercent = idle/totalTime;
    float cpuUtilisationPercent = 1.0 - idleTimePercent;

    return cpuUtilisationPercent;
     */
    return LinuxParser::CpuUsage(pid_);
    }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() {
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    //first return just i.d then replace it with a call to get user name for linux parser
    return LinuxParser::Uid(pid_);
    //return string("arjun");
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }