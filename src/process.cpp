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

int Process::Pid() { return pid_; }

void Process::setPid(int id) {pid_=id;}

float Process::CpuUtilization() {
  return LinuxParser::CpuUsage(pid_);
 }

string Process::Command() { return LinuxParser::Command(pid_); }

string Process::Ram() {
    return LinuxParser::Ram(pid_);
}

string Process::User() {
    //first return just i.d then replace it with a call to get user name for linux parser
    return LinuxParser::Uid(pid_);
    //return string("arjun");
}

long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }